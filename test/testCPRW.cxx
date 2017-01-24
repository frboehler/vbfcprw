#include "HLeptonsCPRW/WeightAndOptObsWrapper.h"
#include<iostream>

int main()
{
  std::pair<double,double> oo, weights;
  double pjet1[] = {123,12,4,123};
  double pjet2[] = {123,12,4,123};
  double pjet3[] = {123,12,4,123};
  double phiggs[] = {123,12,4,123};
  double ecm = 13000;
  double mH = 125;

  weights = HLeptonsCPRW::getWeightsDtilde(ecm, mH , 2,1,2,3,2,1,0.1,0.5,pjet1,pjet2,pjet3,phiggs);
  std::cout<<weights.first<<" , "<<weights.second<<std::endl;

  oo = HLeptonsCPRW::getOptObs(ecm, mH ,0.1,0.5,1,2,pjet1,pjet2,phiggs);
  std::cout<<oo.first<<" , "<<oo.second<<std::endl;

  std::cout<<HLeptonsCPRW::getReweight(ecm, mH, 1 , 0.5, 
  0.5, 0.5, 0.5, 0.5, 0.5,
  0.5, 0.5, 0.5, 0.5, 0.5, 0.5,
  0.5, 0.5, 0.5, 0.5, 0.5, 0.5,
  2,1,1,1,1,1,
  0.5,0.5,pjet1,pjet2,pjet3,phiggs)
  <<std::endl;
  return 1;
}
