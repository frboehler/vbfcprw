#ifndef __OPTOBSEVENTSTORE__
#define __OPTOBSEVENTSTORE__
#include "HLeptonsCPRW/WeightAndOptObsWrapper.h"
#include <vector>
#include <string>

class OptObsEventStore {
  private:
    std::pair< std::pair<double,double> , unsigned long long int > m_wdt = std::make_pair(std::make_pair(-1234,-1234) , 0);
    std::pair< std::pair<double,double> , unsigned long long int > m_oo  = std::make_pair(std::make_pair(-1234,-1234) , 0);
    std::vector<double> getLHAPDF(double Q, double x);
    bool m_isInitialized = false;
  public:
    OptObsEventStore() {};
    virtual ~OptObsEventStore() {};
    double getReweight( double ecm, double mH, int ipara, double rsmin, 
                      double din, double dbin, double dtin, double dtbin, double lambdahvvin, 
                      double a1hwwin, double a2hwwin, double a3hwwin, double a1haain, double a2haain, double a3haain, 
                      double a1hazin,  double a2hazin, double a3hazin, double a1hzzin, double a2hzzin, double a3hzzin, 
                      int npafin, int iflin1, int iflin2, int iflout1, int iflout2, int iflout3, 
                      double x1, double x2, double *pjet1, double *pjet2, double *pjet3, double *phiggs)
    {
      return HLeptonsCPRW::getReweight(ecm,mH,ipara,rsmin,din,dbin,dtin,dtbin,lambdahvvin, a1hwwin,  a2hwwin,  a3hwwin,  a1haain,  a2haain,  a3haain, a1hazin,   a2hazin,  a3hazin,  a1hzzin,  a2hzzin,  a3hzzin, npafin,  iflin1,  iflin2,  iflout1,  iflout2,  iflout3, x1,  x2,  pjet1,  pjet2,  pjet3,  phiggs);
    }

    double getWeightsDtilde(int entry, unsigned long long int EventNumber, double ecm, double mH,int npafin, int ifl1in,int ifl2in,int ifl1out, int ifl2out, int ifl3out, double x1, double x2, double* pjet1, double *pjet2, double *pjet3, double *phiggs);
    double getOptObs(int entry, unsigned long long int EventNumber, double ecm,double mH,double x1,double x2,double Q, double* pjet1, double* pjet2, double* phiggs);

    void initPDFSet(std::string,int,double);
};
/*};*/
/*{*/
    /*      */
/*};*/

#endif

