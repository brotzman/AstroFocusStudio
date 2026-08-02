#ifndef ASTROFOCUS_AUTOFOCUS_CHART_MATH_INC
#define ASTROFOCUS_AUTOFOCUS_CHART_MATH_INC

struct AfChartLayout {
    int plotLeft,plotTop,plotRight,plotBottom;
    int axisTop,axisBottom;
    int residualTop,residualBottom;
    int detailed;
};

static double AfChartAbs(double x){return x<0.0?-x:x;}
static double AfChartSqrt(double x){
    if(x<=0.0)return 0.0;
    double r=x>1.0?x:1.0;
    for(int i=0;i<20;i++)r=0.5*(r+x/r);
    return r;
}
static int AfChartClampInt(int v,int lo,int hi){return v<lo?lo:(v>hi?hi:v);}
static double AfChartEvalModel(int model,const double* p,double pos,double center,double scale,double qa,double qb,double qc){
    double x=scale>0.0?(pos-center)/scale:0.0;
    if(model==2||model==3){
        double width=AfChartAbs(p[3]);if(width<0.000001)width=0.000001;
        double dx=x-p[2],base=AfChartSqrt(dx*dx+width*width)-width;
        if(model==3)base+=p[4]*dx;
        return p[0]+p[1]*base;
    }
    if(model==1)return p[0]*x*x+p[1]*x+p[2];
    return qa*x*x+qb*x+qc;
}
static int AfChartDisplayedErrorHalfHeight(double sigma,double ymin,double ymax,int plotHeight,int markerRadius){
    if(!(sigma>0.0)||!(ymax>ymin)||plotHeight<=0)return 0;
    int sy=(int)(sigma*(double)plotHeight/(ymax-ymin)+0.5);
    int minimum=markerRadius+3;
    if(sy<minimum)sy=minimum;
    int maximum=plotHeight/3;if(maximum<minimum)maximum=minimum;
    if(sy>maximum)sy=maximum;
    return sy;
}
static int AfChartComputeLayout(int outerL,int outerT,int outerR,int outerB,AfChartLayout* out){
    if(!out)return 0;
    int w=outerR-outerL,h=outerB-outerT;
    if(w<280||h<120)return 0;
    const int detailed=h>=210;
    const int axisH=detailed?20:18;
    const int residualH=detailed?48:0;
    const int topGap=4,sectionGap=6,bottomPad=10;
    if(detailed){
        out->residualBottom=outerB-bottomPad;
        out->residualTop=out->residualBottom-residualH;
        out->axisBottom=out->residualTop-sectionGap;
    }else{
        out->residualTop=out->residualBottom=outerB-bottomPad;
        out->axisBottom=outerB-bottomPad;
    }
    out->axisTop=out->axisBottom-axisH;
    out->plotLeft=outerL+52;out->plotRight=outerR-10;
    out->plotTop=outerT+topGap;
    out->plotBottom=out->axisTop-sectionGap;
    out->detailed=detailed;
    if(out->plotRight-out->plotLeft<210||out->plotBottom-out->plotTop<70)return 0;
    if(!(out->plotTop<out->plotBottom&&out->plotBottom<=out->axisTop&&out->axisBottom<=out->residualTop&&out->residualBottom<=outerB))return 0;
    return 1;
}

#endif
