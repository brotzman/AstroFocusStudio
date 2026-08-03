#include <cstdio>
#include "../common/continuous_focus_logic.h"
static int passed=0,total=0;
static void check(bool ok,const char* name){total++;std::printf("%s: %s\n",name,ok?"PASS":"FAIL");if(ok)passed++;}
int main(){
    double odd[5]={5,1,4,2,3};double even[4]={8,2,6,4};
    check(AfsCfMedian(odd,5)==3.0,"median odd");
    check(AfsCfMedian(even,4)==5.0,"median even");
    check(AfsCfMetric(3.0,1.5)>0.0,"valid composite metric");
    check(AfsCfMetric(0.0,1.5)==0.0,"invalid metric rejected");
    check(AfsCfDegradationPercent(2.0,2.2)>9.9,"degradation percent");
    check(AfsCfImprovementPercent(2.2,2.0)>9.0,"improvement percent");
    check(AfsCfConfidence(12,4,0.1,0.45,30.0)>=75,"high confidence");
    check(AfsCfConfidence(1,4,2.0,0.45,3.0)<40,"low confidence");
    check(AfsCfStepFromDegradation(2.0,3,12)==4,"small correction");
    check(AfsCfStepFromDegradation(80.0,3,12)==12,"correction clamped");
    std::printf("SUMMARY %d/%d\n",passed,total);return passed==total?0:1;
}
