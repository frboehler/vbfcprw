/*
|-------------------------------------
| Wrapper to calculate events weights and optimal observable. Using Fortran routines written by M. Schumacher (markus.schumacher@cern.ch).
| 2017/01/25
| Felix Bührer (felix.buehrer@cern.ch)
|-------------------------------------
*/

#ifndef __HLEPTONSCPRW__
#define __HLEPTONSCPRW__
#include<utility>
#include<iostream>

namespace HLeptonsCPRW {
  double getReweight(double ecm, double mH, int ipara, double rsmin, 
  double din, double dbin, double dtin, double dtbin, double lambdahvvin, 
  double a1hwwin, double a2hwwin, double a3hwwin, double a1haain, double a2haain, double a3haain, 
  double a1hazin,  double a2hazin, double a3hazin, double a1hzzin, double a2hzzin, double a3hzzin, 
  int npafin, int iflin1, int iflin2, int iflout1, int iflout2, int iflout3, 
  double x1, double x2, double *pjet1, double *pjet2, double *pjet3, double *phiggs);
  std::pair<double,double> getWeightsDtilde(double ecm, double mH,int npafin, int ifl1in,int ifl2in,int ifl1out, int ifl2out, int ifl3out, double x1, double x2, double* pjet1, double *pjet2, double *pjet3, double *phiggs);
  std::pair<double,double> getOptObs(double ecm,double mH,double x1,double x2,double* pdf1,double* pdf2, double* pjet1, double* pjet2, double* phiggs);

}

#endif
