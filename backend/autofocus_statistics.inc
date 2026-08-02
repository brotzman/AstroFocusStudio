// AstroFocus Studio 3.6.10 autofocus statistics and bounded curve models.
// Included by backend.cpp after the autofocus state globals and core math helpers.

enum AfCurveModel { AF_CURVE_NONE=0, AF_CURVE_QUADRATIC=1, AF_CURVE_HYPERBOLA=2, AF_CURVE_TILTED_HYPERBOLA=3 };

static double AfNaturalLog(double x){
    if(x<=0.0)return -1e300;int exponent=0;while(x>2.0){x*=0.5;exponent++;}while(x<0.5){x*=2.0;exponent--;}
    double z=(x-1.0)/(x+1.0),z2=z*z,term=z,sum=0.0;for(int k=1;k<=19;k+=2){sum+=term/(double)k;term*=z2;}
    return 2.0*sum+(double)exponent*0.69314718055994530942;
}

struct AfModelCandidate {
    BOOL valid;
    int model,paramCount,inliers;
    double p[5],cov[25];
    double r2,reducedChi2,aicc,focusX,focusSigma,looSigma,depth,residualRms,selectionScore;
    BOOL include[MAX_AF_POINTS],outlier[MAX_AF_POINTS];
    double residual[MAX_AF_POINTS],standardResidual[MAX_AF_POINTS];
};

static double AfSigmaFloor(double value,int stars){
    int s=stars>0?stars:1;
    double relative=0.012+0.085/sqrt((double)s);
    double floor=value*relative;
    if(floor<0.012)floor=0.012;
    return floor;
}

static double AfRobustStandardError(const double* values,int n,double medianValue,int stars){
    double floor=AfSigmaFloor(medianValue,stars);
    if(n<2)return floor;
    double deviations[MAX_AF_SAMPLES];
    for(int i=0;i<n;i++)deviations[i]=fabs(values[i]-medianValue);
    double mad=Median(deviations,n);
    double sigma=1.4826*mad/sqrt((double)n);
    if(!FiniteD(sigma)||sigma<floor)sigma=floor;
    return sigma;
}

static BOOL AfSolveLinear(double matrix[5][6],int n,double* solution){
    for(int i=0;i<n;i++){
        int pivot=i;
        for(int r=i+1;r<n;r++)if(fabs(matrix[r][i])>fabs(matrix[pivot][i]))pivot=r;
        if(fabs(matrix[pivot][i])<1e-12)return FALSE;
        if(pivot!=i)for(int c=i;c<=n;c++){double v=matrix[i][c];matrix[i][c]=matrix[pivot][c];matrix[pivot][c]=v;}
        double d=matrix[i][i];for(int c=i;c<=n;c++)matrix[i][c]/=d;
        for(int r=0;r<n;r++)if(r!=i){double f=matrix[r][i];for(int c=i;c<=n;c++)matrix[r][c]-=f*matrix[i][c];}
    }
    for(int i=0;i<n;i++)solution[i]=matrix[i][n];
    return TRUE;
}

static BOOL AfInvertMatrix(const double* source,int n,double* inverse){
    double aug[5][10];memset(aug,0,sizeof(aug));
    for(int r=0;r<n;r++)for(int c=0;c<n;c++){aug[r][c]=source[r*n+c];aug[r][n+c]=(r==c)?1.0:0.0;}
    for(int i=0;i<n;i++){
        int pivot=i;for(int r=i+1;r<n;r++)if(fabs(aug[r][i])>fabs(aug[pivot][i]))pivot=r;
        if(fabs(aug[pivot][i])<1e-12)return FALSE;
        if(pivot!=i)for(int c=0;c<2*n;c++){double v=aug[i][c];aug[i][c]=aug[pivot][c];aug[pivot][c]=v;}
        double d=aug[i][i];for(int c=0;c<2*n;c++)aug[i][c]/=d;
        for(int r=0;r<n;r++)if(r!=i){double f=aug[r][i];for(int c=0;c<2*n;c++)aug[r][c]-=f*aug[i][c];}
    }
    for(int r=0;r<n;r++)for(int c=0;c<n;c++)inverse[r*n+c]=aug[r][n+c];
    return TRUE;
}

static double AfEvalModel(int model,const double* p,double x){
    if(model==AF_CURVE_QUADRATIC)return p[0]*x*x+p[1]*x+p[2];
    if(model==AF_CURVE_HYPERBOLA||model==AF_CURVE_TILTED_HYPERBOLA){
        double d=x-p[2],width=p[3];if(width<0.02)width=0.02;
        double base=sqrt(d*d+width*width)-width;
        double tilt=model==AF_CURVE_TILTED_HYPERBOLA?p[4]*d:0.0;
        return p[0]+p[1]*(base+tilt);
    }
    return 0.0;
}

static LPCWSTR AfModelName(int model){
    if(model==AF_CURVE_QUADRATIC)return L"gewichtete robuste Parabel";
    if(model==AF_CURVE_HYPERBOLA)return L"symmetrische Hyperbel";
    if(model==AF_CURVE_TILTED_HYPERBOLA)return L"geneigte Hyperbel";
    return L"–";
}

static double AfFocusPositionFromParams(int model,const double* p){
    if(model==AF_CURVE_QUADRATIC){
        if(fabs(p[0])<1e-12)return p[2];
        return -p[1]/(2.0*p[0]);
    }
    if(model==AF_CURVE_HYPERBOLA)return p[2];
    if(model==AF_CURVE_TILTED_HYPERBOLA){
        double tilt=p[4];
        if(tilt<=-0.999999||tilt>=0.999999)return p[2];
        double width=p[3];if(width<0.02)width=0.02;
        double denom=sqrt(1.0-tilt*tilt);
        if(denom<1e-9)return p[2];
        return p[2]-(tilt*width)/denom;
    }
    return p[2];
}

static double AfFocusSigmaFromCovariance(int model,const double* p,const double* cov,int paramCount){
    if(!cov||paramCount<=0)return 0.0;
    if(model==AF_CURVE_QUADRATIC){
        double a=p[0],b=p[1];
        if(fabs(a)<1e-12)return 0.0;
        double da=b/(2.0*a*a),db=-1.0/(2.0*a);
        double v=da*da*cov[0]+2.0*da*db*cov[1]+db*db*cov[4];
        return v>0.0?sqrt(v):0.0;
    }
    double grad[5]={0};
    for(int a=0;a<paramCount;a++){
        double plus[5],minus[5];
        for(int z=0;z<5;z++){plus[z]=p[z];minus[z]=p[z];}
        double step=1e-5*(fabs(p[a])+1.0);
        plus[a]+=step;minus[a]-=step;
        double denom=plus[a]-minus[a];
        if(fabs(denom)<=1e-14)continue;
        grad[a]=(AfFocusPositionFromParams(model,plus)-AfFocusPositionFromParams(model,minus))/denom;
    }
    double v=0.0;
    for(int r=0;r<paramCount;r++)for(int c=0;c<paramCount;c++)v+=grad[r]*cov[r*paramCount+c]*grad[c];
    return v>0.0?sqrt(v):0.0;
}

static BOOL AfDirectWeightedQuadratic(const double* values,const double* sigmas,const BOOL* include,int n,double center,double scale,AfModelCandidate* out,BOOL computeCovariance){
    memset(out,0,sizeof(*out));out->model=AF_CURVE_QUADRATIC;out->paramCount=3;
    double normal[9]={0},rhs[3]={0};int count=0;
    for(int i=0;i<n;i++)if(include[i]&&values[i]>0){
        double x=((double)g_afPositions[i]-center)/scale,y=values[i];double sigma=sigmas[i]>1e-9?sigmas[i]:AfSigmaFloor(y,g_afUsedMetrics[i]);double w=1.0/(sigma*sigma);double basis[3]={x*x,x,1.0};
        for(int r=0;r<3;r++){rhs[r]+=w*basis[r]*y;for(int c=0;c<3;c++)normal[r*3+c]+=w*basis[r]*basis[c];}count++;
    }
    if(count<3)return FALSE;double matrix[5][6];memset(matrix,0,sizeof(matrix));for(int r=0;r<3;r++){for(int c=0;c<3;c++)matrix[r][c]=normal[r*3+c];matrix[r][3]=rhs[r];}double sol[5]={0};if(!AfSolveLinear(matrix,3,sol)||sol[0]<=1e-9)return FALSE;
    double focus=-sol[1]/(2.0*sol[0]);if(!FiniteD(focus))return FALSE;
    out->valid=TRUE;out->inliers=count;out->p[0]=sol[0];out->p[1]=sol[1];out->p[2]=sol[2];out->focusX=focus;
    double mean=0.0;for(int i=0;i<n;i++)if(include[i])mean+=values[i];mean/=count;double ssTot=0.0,ssRes=0.0,chi2=0.0,resSq=0.0;
    for(int i=0;i<n;i++){
        out->include[i]=include[i];if(!include[i])continue;double x=((double)g_afPositions[i]-center)/scale,p=AfEvalModel(out->model,out->p,x),e=values[i]-p,sigma=sigmas[i]>1e-9?sigmas[i]:AfSigmaFloor(values[i],g_afUsedMetrics[i]);
        out->residual[i]=e;out->standardResidual[i]=e/sigma;ssTot+=(values[i]-mean)*(values[i]-mean);ssRes+=e*e;chi2+=(e/sigma)*(e/sigma);resSq+=e*e;
    }
    out->r2=ssTot>1e-12?1.0-ssRes/ssTot:0.0;int dof=count-3;out->reducedChi2=dof>0?chi2/dof:chi2;out->residualRms=sqrt(resSq/count);
    double safe=chi2/count;if(safe<1e-12)safe=1e-12;out->aicc=count*AfNaturalLog(safe)+6.0;if(count>4)out->aicc+=24.0/(count-4);else out->aicc+=1000.0;
    double minPred=AfEvalModel(out->model,out->p,focus);double minX=1e30,maxX=-1e30;for(int i=0;i<n;i++)if(include[i]){double x=((double)g_afPositions[i]-center)/scale;if(x<minX)minX=x;if(x>maxX)maxX=x;}
    double edge=(AfEvalModel(out->model,out->p,minX)+AfEvalModel(out->model,out->p,maxX))*0.5;out->depth=minPred>0?edge/minPred:0.0;
    if(computeCovariance){double inv[25]={0};if(AfInvertMatrix(normal,3,inv)){double variance=out->reducedChi2;if(variance<0.25)variance=0.25;for(int i=0;i<9;i++)out->cov[i]=inv[i]*variance;double da=sol[1]/(2.0*sol[0]*sol[0]),db=-1.0/(2.0*sol[0]);double v=da*da*out->cov[0]+2.0*da*db*out->cov[1]+db*db*out->cov[4];out->focusSigma=v>0?sqrt(v):0.0;}}
    return TRUE;
}

static BOOL AfRobustQuadratic(const double* values,const double* sigmas,int n,double center,double scale,AfModelCandidate* out){
    BOOL valid[MAX_AF_POINTS];int indices[MAX_AF_POINTS],vn=0;double ys[MAX_AF_POINTS];int minStars=g_afRunUsesSelectedStar?1:3;
    for(int i=0;i<n;i++){valid[i]=values[i]>0&&g_afUsedMetrics[i]>=minStars;if(valid[i]){indices[vn]=i;ys[vn]=values[i];vn++;}}
    if(vn<5)return FALSE;double medianY=Median(ys,vn);if(medianY<=0)return FALSE;
    double minX=((double)g_afPositions[indices[0]]-center)/scale,maxX=((double)g_afPositions[indices[vn-1]]-center)/scale,bestScore=1e300,bestP[3]={0},bestMed=0;
    for(int aa=0;aa<vn-2;aa++)for(int bb=aa+1;bb<vn-1;bb++)for(int cc=bb+1;cc<vn;cc++){
        BOOL tri[MAX_AF_POINTS];memset(tri,0,sizeof(tri));tri[indices[aa]]=tri[indices[bb]]=tri[indices[cc]]=TRUE;AfModelCandidate seed;if(!AfDirectWeightedQuadratic(values,sigmas,tri,n,center,scale,&seed,FALSE))continue;double vx=seed.focusX;if(vx<minX-0.5||vx>maxX+0.5)continue;
        double residuals[MAX_AF_POINTS];int rn=0;for(int k=0;k<vn;k++){int i=indices[k];double x=((double)g_afPositions[i]-center)/scale;residuals[rn++]=fabs(values[i]-AfEvalModel(AF_CURVE_QUADRATIC,seed.p,x));}double med=Median(residuals,rn),score=med/medianY;if(score<bestScore){bestScore=score;bestP[0]=seed.p[0];bestP[1]=seed.p[1];bestP[2]=seed.p[2];bestMed=med;}
    }
    if(bestScore>=1e299)return FALSE;double limit=bestMed*3.5,floorLimit=medianY*0.10;if(limit<floorLimit)limit=floorLimit;BOOL include[MAX_AF_POINTS];memset(include,0,sizeof(include));int inliers=0;
    for(int k=0;k<vn;k++){int i=indices[k];double x=((double)g_afPositions[i]-center)/scale,res=fabs(values[i]-AfEvalModel(AF_CURVE_QUADRATIC,bestP,x));if(res<=limit){include[i]=TRUE;inliers++;}}
    if(inliers<5||!AfDirectWeightedQuadratic(values,sigmas,include,n,center,scale,out,TRUE))return FALSE;if(out->focusX<minX-0.35||out->focusX>maxX+0.35)return FALSE;
    for(int i=0;i<n;i++)out->outlier[i]=valid[i]&&!include[i];
    return TRUE;
}

static void AfClampHyperParameters(int model,double* p,double minX,double maxX,double maxY){
    p[0]=ClampD(p[0],0.02,maxY*2.5+1.0);p[1]=ClampD(p[1],0.0001,maxY*12.0+1.0);p[2]=ClampD(p[2],minX-0.30,maxX+0.30);p[3]=ClampD(p[3],0.04,6.0);if(model==AF_CURVE_TILTED_HYPERBOLA)p[4]=ClampD(p[4],-0.80,0.80);else p[4]=0.0;
}

static double AfNonlinearSse(int model,const double* p,const double* values,const double* sigmas,const BOOL* include,int n,double center,double scale){
    double sse=0.0;for(int i=0;i<n;i++)if(include[i]){double x=((double)g_afPositions[i]-center)/scale,sigma=sigmas[i]>1e-9?sigmas[i]:AfSigmaFloor(values[i],g_afUsedMetrics[i]);double e=values[i]-AfEvalModel(model,p,x);sse+=(e/sigma)*(e/sigma);}return sse;
}

static BOOL AfFitBoundedHyperbola(int model,const double* values,const double* sigmas,const BOOL* include,int n,double center,double scale,const AfModelCandidate* quadratic,AfModelCandidate* out,int maxIterations){
    memset(out,0,sizeof(*out));int k=model==AF_CURVE_TILTED_HYPERBOLA?5:4,count=0;double minX=1e30,maxX=-1e30,maxY=0.0;
    for(int i=0;i<n;i++)if(include[i]){double x=((double)g_afPositions[i]-center)/scale;if(x<minX)minX=x;if(x>maxX)maxX=x;if(values[i]>maxY)maxY=values[i];count++;}
    if(count<k+2||!quadratic||!quadratic->valid)return FALSE;double qmin=AfEvalModel(AF_CURVE_QUADRATIC,quadratic->p,quadratic->focusX);if(qmin<=0)return FALSE;
    double width=0.75,edgeBase=0.0,edgeRise=0.0;for(int i=0;i<n;i++)if(include[i]){double x=((double)g_afPositions[i]-center)/scale,d=x-quadratic->focusX,base=sqrt(d*d+width*width)-width;if(base>edgeBase){edgeBase=base;edgeRise=values[i]-qmin;}}
    double p[5]={qmin,edgeBase>1e-6?edgeRise/edgeBase:1.0,quadratic->focusX,width,0.0};if(p[1]<=0)p[1]=maxY*0.2;AfClampHyperParameters(model,p,minX,maxX,maxY);double lambda=0.01,best=AfNonlinearSse(model,p,values,sigmas,include,n,center,scale);if(!FiniteD(best))return FALSE;
    for(int iter=0;iter<maxIterations;iter++){
        double normal[25]={0},rhs[5]={0};
        for(int i=0;i<n;i++)if(include[i]){
            double x=((double)g_afPositions[i]-center)/scale,y=values[i],sigma=sigmas[i]>1e-9?sigmas[i]:AfSigmaFloor(y,g_afUsedMetrics[i]),w=1.0/(sigma*sigma),pred=AfEvalModel(model,p,x),res=y-pred,jac[5]={0};
            for(int a=0;a<k;a++){double step=1e-5*(fabs(p[a])+1.0);double plus[5],minus[5];for(int z=0;z<5;z++){plus[z]=p[z];minus[z]=p[z];}plus[a]+=step;minus[a]-=step;AfClampHyperParameters(model,plus,minX,maxX,maxY);AfClampHyperParameters(model,minus,minX,maxX,maxY);double denom=plus[a]-minus[a];jac[a]=fabs(denom)>1e-14?(AfEvalModel(model,plus,x)-AfEvalModel(model,minus,x))/denom:0.0;}
            for(int a=0;a<k;a++){rhs[a]+=w*jac[a]*res;for(int b=0;b<k;b++)normal[a*k+b]+=w*jac[a]*jac[b];}
        }
        double matrix[5][6];memset(matrix,0,sizeof(matrix));for(int a=0;a<k;a++){for(int b=0;b<k;b++)matrix[a][b]=normal[a*k+b];matrix[a][a]+=lambda*(normal[a*k+a]+1e-6);matrix[a][k]=rhs[a];}double delta[5]={0};if(!AfSolveLinear(matrix,k,delta)){lambda*=10.0;if(lambda>1e12)break;continue;}
        double trial[5];for(int a=0;a<5;a++)trial[a]=p[a]+(a<k?delta[a]:0.0);AfClampHyperParameters(model,trial,minX,maxX,maxY);double score=AfNonlinearSse(model,trial,values,sigmas,include,n,center,scale);
        if(FiniteD(score)&&score<best){double improvement=best-score;for(int a=0;a<5;a++)p[a]=trial[a];best=score;lambda*=0.35;if(lambda<1e-9)lambda=1e-9;if(improvement<1e-8*(1.0+best))break;}else{lambda*=5.0;if(lambda>1e12)break;}
    }
    if(!FiniteD(best))return FALSE;out->valid=TRUE;out->model=model;out->paramCount=k;out->inliers=count;for(int a=0;a<5;a++)out->p[a]=p[a];out->focusX=AfFocusPositionFromParams(model,p);
    double mean=0;for(int i=0;i<n;i++)if(include[i])mean+=values[i];mean/=count;double ssTot=0,ssRes=0,resSq=0;for(int i=0;i<n;i++){out->include[i]=include[i];if(!include[i])continue;double x=((double)g_afPositions[i]-center)/scale,e=values[i]-AfEvalModel(model,p,x),sigma=sigmas[i]>1e-9?sigmas[i]:AfSigmaFloor(values[i],g_afUsedMetrics[i]);out->residual[i]=e;out->standardResidual[i]=e/sigma;ssTot+=(values[i]-mean)*(values[i]-mean);ssRes+=e*e;resSq+=e*e;}
    out->r2=ssTot>1e-12?1.0-ssRes/ssTot:0.0;int dof=count-k;out->reducedChi2=dof>0?best/dof:best;out->residualRms=sqrt(resSq/count);double safe=best/count;if(safe<1e-12)safe=1e-12;out->aicc=count*AfNaturalLog(safe)+2.0*k;if(count>k+1)out->aicc+=2.0*k*(k+1)/(double)(count-k-1);else out->aicc+=1000.0;
    double minPred=AfEvalModel(model,p,out->focusX),edge=(AfEvalModel(model,p,minX)+AfEvalModel(model,p,maxX))*0.5;out->depth=minPred>0?edge/minPred:0.0;
    double jtj[25]={0};for(int i=0;i<n;i++)if(include[i]){double x=((double)g_afPositions[i]-center)/scale,sigma=sigmas[i]>1e-9?sigmas[i]:AfSigmaFloor(values[i],g_afUsedMetrics[i]),w=1.0/(sigma*sigma),jac[5]={0};for(int a=0;a<k;a++){double step=1e-5*(fabs(p[a])+1.0);double plus[5],minus[5];for(int z=0;z<5;z++){plus[z]=p[z];minus[z]=p[z];}plus[a]+=step;minus[a]-=step;AfClampHyperParameters(model,plus,minX,maxX,maxY);AfClampHyperParameters(model,minus,minX,maxX,maxY);double denom=plus[a]-minus[a];jac[a]=fabs(denom)>1e-14?(AfEvalModel(model,plus,x)-AfEvalModel(model,minus,x))/denom:0.0;}for(int a=0;a<k;a++)for(int b=0;b<k;b++)jtj[a*k+b]+=w*jac[a]*jac[b];}
    double inv[25]={0};if(AfInvertMatrix(jtj,k,inv)){double variance=out->reducedChi2;if(variance<0.25)variance=0.25;for(int i=0;i<k*k;i++)out->cov[i]=inv[i]*variance;out->focusSigma=AfFocusSigmaFromCovariance(model,p,out->cov,k);}
    for(int i=0;i<n;i++)out->outlier[i]=quadratic->outlier[i];
    return out->p[0]>0&&out->p[1]>0&&FiniteD(out->focusX)&&out->focusX>=minX-0.30&&out->focusX<=maxX+0.30&&out->depth>1.02;
}

static double AfStdDev(const double* values,int n){if(n<2)return 0.0;double mean=0;for(int i=0;i<n;i++)mean+=values[i];mean/=n;double s=0;for(int i=0;i<n;i++){double d=values[i]-mean;s+=d*d;}return sqrt(s/(n-1));}

static double AfLeaveOneOut(const AfModelCandidate* base,const double* values,const double* sigmas,int n,double center,double scale){
    if(!base||!base->valid)return 0.0;double positions[MAX_AF_POINTS];int pn=0;
    for(int omit=0;omit<n;omit++)if(base->include[omit]){
        BOOL mask[MAX_AF_POINTS];for(int i=0;i<n;i++)mask[i]=base->include[i]&&i!=omit;AfModelCandidate trial;BOOL ok=FALSE;
        if(base->model==AF_CURVE_QUADRATIC)ok=AfDirectWeightedQuadratic(values,sigmas,mask,n,center,scale,&trial,TRUE);
        else{AfModelCandidate q;if(AfDirectWeightedQuadratic(values,sigmas,mask,n,center,scale,&q,TRUE))ok=AfFitBoundedHyperbola(base->model,values,sigmas,mask,n,center,scale,&q,&trial,35);}
        if(ok&&FiniteD(trial.focusX))positions[pn++]=trial.focusX;
    }
    if(pn<base->inliers-2)return 9.0;return AfStdDev(positions,pn);
}

static BOOL AfRefitSelectedModel(const AfModelCandidate* base,const double* values,const double* sigmas,const BOOL* include,int n,double center,double scale,AfModelCandidate* out){
    if(base->model==AF_CURVE_QUADRATIC)return AfDirectWeightedQuadratic(values,sigmas,include,n,center,scale,out,TRUE);
    AfModelCandidate seed;if(!AfDirectWeightedQuadratic(values,sigmas,include,n,center,scale,&seed,TRUE))return FALSE;
    return AfFitBoundedHyperbola(base->model,values,sigmas,include,n,center,scale,&seed,out,80);
}
static void AfRestoreModelCompatibleHyperbolaPoints(const double* values,const double* sigmas,int n,double center,double scale,AfModelCandidate* selected){
    if(!selected||!selected->valid||selected->model==AF_CURVE_QUADRATIC)return;
    double validValues[MAX_AF_POINTS];int validCount=0,minStars=g_afRunUsesSelectedStar?1:3;
    for(int i=0;i<n;i++)if(values[i]>0&&g_afUsedMetrics[i]>=minStars)validValues[validCount++]=values[i];
    if(validCount<5)return;double medianY=Median(validValues,validCount);BOOL include[MAX_AF_POINTS];int restored=0;
    for(int i=0;i<n;i++)include[i]=selected->include[i];
    for(int i=0;i<n;i++)if(!include[i]&&values[i]>0&&g_afUsedMetrics[i]>=minStars){
        double x=((double)g_afPositions[i]-center)/scale,pred=AfEvalModel(selected->model,selected->p,x),res=fabs(values[i]-pred),sigma=sigmas[i]>1e-9?sigmas[i]:AfSigmaFloor(values[i],g_afUsedMetrics[i]);
        double limit=medianY*0.06,sigmaLimit=4.0*sigma;if(limit<sigmaLimit)limit=sigmaLimit;
        if(res<=limit){include[i]=TRUE;restored++;}
    }
    if(restored<=0)return;AfModelCandidate trial;if(!AfRefitSelectedModel(selected,values,sigmas,include,n,center,scale,&trial))return;
    for(int i=0;i<n;i++){BOOL valid=values[i]>0&&g_afUsedMetrics[i]>=minStars;trial.outlier[i]=valid&&!trial.include[i];}
    *selected=trial;
}


static void AfRefineSelectedOutliers(const double* values,const double* sigmas,int n,double center,double scale,AfModelCandidate* selected){
    if(!selected||!selected->valid)return;
    const int minStars=g_afRunUsesSelectedStar?1:3;
    for(int pass=0;pass<2;pass++){
        double validValues[MAX_AF_POINTS];int validCount=0;
        for(int i=0;i<n;i++)if(values[i]>0&&g_afUsedMetrics[i]>=minStars)validValues[validCount++]=values[i];
        if(validCount<5||selected->inliers<=selected->paramCount+1)return;
        double medianY=Median(validValues,validCount),worstScore=0.0;int worst=-1;
        for(int i=0;i<n;i++)if(selected->include[i]&&values[i]>0&&g_afUsedMetrics[i]>=minStars){
            double x=((double)g_afPositions[i]-center)/scale,pred=AfEvalModel(selected->model,selected->p,x),res=fabs(values[i]-pred);
            double sigma=sigmas[i]>1e-9?sigmas[i]:AfSigmaFloor(values[i],g_afUsedMetrics[i]);
            double standardized=sigma>1e-12?res/sigma:0.0;
            double absoluteLimit=medianY*0.035,sigmaLimit=3.5*sigma;if(absoluteLimit<sigmaLimit)absoluteLimit=sigmaLimit;
            if(standardized>3.75&&res>absoluteLimit&&standardized>worstScore){worstScore=standardized;worst=i;}
        }
        if(worst<0)return;
        BOOL include[MAX_AF_POINTS];for(int i=0;i<n;i++)include[i]=selected->include[i];include[worst]=FALSE;
        AfModelCandidate trial;if(!AfRefitSelectedModel(selected,values,sigmas,include,n,center,scale,&trial))return;
        for(int i=0;i<n;i++){BOOL valid=values[i]>0&&g_afUsedMetrics[i]>=minStars;trial.outlier[i]=valid&&!trial.include[i];}
        *selected=trial;
    }
}

static BOOL AfSelectModel(const double* values,const double* sigmas,int n,double center,double scale,AfModelCandidate* selected){
    AfModelCandidate q;if(!AfRobustQuadratic(values,sigmas,n,center,scale,&q))return FALSE;q.looSigma=AfLeaveOneOut(&q,values,sigmas,n,center,scale);q.selectionScore=q.aicc+2.0*ClampD(q.focusSigma,0,5)+ClampD(q.looSigma,0,5);
    *selected=q;AfModelCandidate h;if(AfFitBoundedHyperbola(AF_CURVE_HYPERBOLA,values,sigmas,q.include,n,center,scale,&q,&h,80)){h.looSigma=AfLeaveOneOut(&h,values,sigmas,n,center,scale);h.selectionScore=h.aicc+2.0*ClampD(h.focusSigma,0,5)+ClampD(h.looSigma,0,5);if(h.selectionScore<selected->selectionScore-2.0&&h.focusSigma<=selected->focusSigma*1.35+0.10)*selected=h;}
    AfModelCandidate t;if(AfFitBoundedHyperbola(AF_CURVE_TILTED_HYPERBOLA,values,sigmas,q.include,n,center,scale,&q,&t,100)){t.looSigma=AfLeaveOneOut(&t,values,sigmas,n,center,scale);t.selectionScore=t.aicc+2.0*ClampD(t.focusSigma,0,5)+ClampD(t.looSigma,0,5);if(t.selectionScore<selected->selectionScore-2.5&&t.focusSigma<=selected->focusSigma*1.30+0.10)*selected=t;}
    AfRestoreModelCompatibleHyperbolaPoints(values,sigmas,n,center,scale,selected);AfRefineSelectedOutliers(values,sigmas,n,center,scale,selected);selected->looSigma=AfLeaveOneOut(selected,values,sigmas,n,center,scale);selected->selectionScore=selected->aicc+2.0*ClampD(selected->focusSigma,0,5)+ClampD(selected->looSigma,0,5);
    return selected->valid;
}

static BOOL FitAutofocus(){
    WriteSimulatorStage("50 fitting autofocus curve");int n=g_afPointCount;if(n<5)return FALSE;double center=(double)g_afPositions[n/2],scale=(double)g_afStep;if(scale<1)scale=1;g_fitCenterPosition=center;g_fitScale=scale;
    AfModelCandidate hfr,fwhm;BOOL hOk=AfSelectModel(g_afMetrics,g_afMetricSigma,n,center,scale,&hfr);BOOL fOk=AfSelectModel(g_afFwhmMetrics,g_afFwhmSigma,n,center,scale,&fwhm);if(!hOk||!fOk)return FALSE;
    double hPos=center+hfr.focusX*scale,fPos=center+fwhm.focusX*scale,agreement=fabs(hPos-fPos)/scale;if(agreement>1.25)return FALSE;double bestPos=hPos*0.65+fPos*0.35;
    int nearest=0;double nearestD=1e300;for(int i=0;i<n;i++){double d=fabs((double)g_afPositions[i]-bestPos);if(d<nearestD){nearestD=d;nearest=i;}}if(nearest<2||nearest>n-3)return FALSE;
    double xBest=(bestPos-center)/scale,minH=AfEvalModel(hfr.model,hfr.p,xBest);if(minH<=0)return FALSE;double localLeft=AfEvalModel(hfr.model,hfr.p,xBest-1.0),localRight=AfEvalModel(hfr.model,hfr.p,xBest+1.0),localRise=((localLeft<localRight?localLeft:localRight)-minH)/minH;if(localRise<0.015||hfr.depth<1.06)return FALSE;
    g_fitModel=hfr.model;g_fitFwhmModel=fwhm.model;for(int i=0;i<5;i++){g_fitParams[i]=hfr.p[i];g_fitFwhmParams[i]=fwhm.p[i];}
    // Preserve the legacy quadratic fields for older API consumers and reports.
    AfModelCandidate qh,qf;BOOL qhOk=AfRobustQuadratic(g_afMetrics,g_afMetricSigma,n,center,scale,&qh),qfOk=AfRobustQuadratic(g_afFwhmMetrics,g_afFwhmSigma,n,center,scale,&qf);
    if(qhOk){g_fitA=qh.p[0];g_fitB=qh.p[1];g_fitC=qh.p[2];}else g_fitA=g_fitB=g_fitC=0.0;
    if(qfOk){g_fitFwhmA=qf.p[0];g_fitFwhmB=qf.p[1];g_fitFwhmC=qf.p[2];}else g_fitFwhmA=g_fitFwhmB=g_fitFwhmC=0.0;
    g_fitR2=hfr.r2;g_fitFwhmR2=fwhm.r2;g_fitFwhmValid=TRUE;int fitMax=FocuserMaxStep();bestPos=ClampD(bestPos,0.0,(double)fitMax);fPos=ClampD(fPos,0.0,(double)fitMax);g_afBestPosition=(int)(bestPos+0.5);g_vBestPosition=(int)(fPos+0.5);
    double actualX=((double)g_afBestPosition-center)/scale;g_afExpectedHfr=AfEvalModel(hfr.model,hfr.p,actualX);g_afExpectedFwhm=AfEvalModel(fwhm.model,fwhm.p,actualX);
    g_fitFocusSigma=scale*sqrt((0.65*hfr.focusSigma)*(0.65*hfr.focusSigma)+(0.35*fwhm.focusSigma)*(0.35*fwhm.focusSigma));g_fitFocusSigmaLoo=scale*sqrt((0.65*hfr.looSigma)*(0.65*hfr.looSigma)+(0.35*fwhm.looSigma)*(0.35*fwhm.looSigma));
    g_fitReducedChi2=(hfr.reducedChi2+fwhm.reducedChi2)*0.5;g_fitResidualRms=hfr.residualRms;g_fitAicc=hfr.aicc;g_fitInliers=0;g_fitOutliers=0;
    for(int i=0;i<n;i++){
        g_afResiduals[i]=hfr.standardResidual[i];g_afFwhmResiduals[i]=fwhm.standardResidual[i];
        BOOL validPoint=(g_afMetrics[i]>0.0&&g_afUsedMetrics[i]>=(g_afRunUsesSelectedStar?1:3))||(g_afFwhmMetrics[i]>0.0&&g_afUsedMetrics[i]>=(g_afRunUsesSelectedStar?1:3));
        g_afOutliers[i]=(hfr.outlier[i]||fwhm.outlier[i])?TRUE:FALSE;
        if(validPoint){if(g_afOutliers[i])g_fitOutliers++;else g_fitInliers++;}
    }
    double hR2=ClampD(hfr.r2,0,1),fR2=ClampD(fwhm.r2,0,1),depthScore=ClampD((hfr.depth-1.04)/0.60,0,1),agreeScore=ClampD(1.0-agreement/1.25,0,1),inlierScore=ClampD((double)hfr.inliers/(double)n,0,1),uncertaintyScore=ClampD(1.0-g_fitFocusSigma/(scale*1.10),0,1),looScore=ClampD(1.0-g_fitFocusSigmaLoo/(scale*1.35),0,1),chiScore=1.0/(1.0+fabs(g_fitReducedChi2-1.0));
    g_fitConfidence=ClampD(0.20*hR2+0.12*fR2+0.16*depthScore+0.12*agreeScore+0.08*inlierScore+0.16*uncertaintyScore+0.10*looScore+0.06*chiScore,0,1);
    wchar_t hm[48],fm[48];CopyWBounded(hm,48,AfModelName(hfr.model));CopyWBounded(fm,48,AfModelName(fwhm.model));if(hfr.model==fwhm.model)CopyWBounded(g_fitMethod,128,hm);else wsprintfW(g_fitMethod,L"Hybrid: HFR %s / FWHM %s",hm,fm);
    return g_fitConfidence>=0.45&&g_fitFocusSigma<=scale*1.50&&g_fitFocusSigmaLoo<=scale*1.80;
}
