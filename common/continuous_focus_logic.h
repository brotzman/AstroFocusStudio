#pragma once

// Small dependency-free helpers shared by the engine and native regression tests.
static inline int AfsCfClampInt(int value,int minimum,int maximum){return value<minimum?minimum:(value>maximum?maximum:value);}
static inline double AfsCfAbs(double value){return value<0.0?-value:value;}
static inline double AfsCfMedian(const double* values,int count){
    if(!values||count<=0)return 0.0;
    if(count>16)count=16;
    double sorted[16];
    for(int i=0;i<count;i++){
        double v=values[i];int j=i;
        while(j>0&&sorted[j-1]>v){sorted[j]=sorted[j-1];j--;}
        sorted[j]=v;
    }
    return (count&1)?sorted[count/2]:(sorted[count/2-1]+sorted[count/2])*0.5;
}
static inline double AfsCfMetric(double fwhm,double hfr){
    if(!(fwhm>0.0)||!(hfr>0.0)||fwhm>1000.0||hfr>1000.0)return 0.0;
    // FWHM is the primary focus indicator; HFR stabilises the estimate in sparse fields.
    return fwhm*0.72+hfr*0.56;
}
static inline double AfsCfDegradationPercent(double reference,double current){
    if(!(reference>0.0)||!(current>0.0))return 0.0;
    return (current/reference-1.0)*100.0;
}
static inline double AfsCfImprovementPercent(double before,double after){
    if(!(before>0.0)||!(after>0.0))return 0.0;
    return (before-after)/before*100.0;
}
static inline int AfsCfConfidence(int usedStars,int minimumStars,double stability,double stabilityLimit,double snr){
    if(minimumStars<1)minimumStars=1;
    double starScore=(double)usedStars/(double)(minimumStars*3);
    if(starScore>1.0)starScore=1.0;if(starScore<0.0)starScore=0.0;
    double stabilityScore=1.0;
    if(stabilityLimit>0.0){stabilityScore=1.0-stability/(stabilityLimit*2.0);if(stabilityScore<0.0)stabilityScore=0.0;if(stabilityScore>1.0)stabilityScore=1.0;}
    double snrScore=snr/35.0;if(snrScore<0.0)snrScore=0.0;if(snrScore>1.0)snrScore=1.0;
    double score=(starScore*0.45+stabilityScore*0.40+snrScore*0.15)*100.0;
    if(score<0.0)score=0.0;if(score>100.0)score=100.0;
    return (int)(score+0.5);
}
static inline int AfsCfStepFromDegradation(double degradationPercent,int deadband,int maximumStep){
    if(deadband<1)deadband=1;if(maximumStep<deadband)maximumStep=deadband;
    double magnitude=degradationPercent<0.0?-degradationPercent:degradationPercent;
    int step=deadband+(int)(magnitude*0.55+0.5);
    return AfsCfClampInt(step,deadband,maximumStep);
}
