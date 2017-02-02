#ifndef __OPTOBSEVENTSTORE__
#define __OPTOBSEVENTSTORE__
#include "HLeptonsCPRW/WeightAndOptObsWrapper.h"
#include "TString.h"

class OptObsEventStore {
  private:
    std::pair<double,int> m_rw = std::make_pair(-1234,-1);
    std::pair< std::pair<double,double> , int > m_wdt = std::make_pair(std::make_pair(-1234,-1234) , -1);
    std::pair< std::pair<double,double> , int > m_oo = std::make_pair(std::make_pair(-1234,-1234) , -1);
    std::vector<double> getLHAPDF(double Q, double x);
    bool m_isInitialized = false;
  public:
    OptObsEventStore() {};
    virtual ~OptObsEventStore() {};
  double getReweight( int EventNumber, double ecm, double mH, int ipara, double rsmin, 
                      double din, double dbin, double dtin, double dtbin, double lambdahvvin, 
                      double a1hwwin, double a2hwwin, double a3hwwin, double a1haain, double a2haain, double a3haain, 
                      double a1hazin,  double a2hazin, double a3hazin, double a1hzzin, double a2hzzin, double a3hzzin, 
                      int npafin, int iflin1, int iflin2, int iflout1, int iflout2, int iflout3, 
                      double x1, double x2, double *pjet1, double *pjet2, double *pjet3, double *phiggs)
  {
    if (EventNumber != m_rw.second) 
    {
      m_rw = std::make_pair(
                        HLeptonsCPRW::getReweight(ecm,mH,ipara,rsmin,din,dbin,dtin,dtbin,lambdahvvin, a1hwwin,  a2hwwin,  a3hwwin,  a1haain,  a2haain,  a3haain, a1hazin,   a2hazin,  a3hazin,  a1hzzin,  a2hzzin,  a3hzzin, npafin,  iflin1,  iflin2,  iflout1,  iflout2,  iflout3, x1,  x2,  pjet1,  pjet2,  pjet3,  phiggs)
                        ,EventNumber);
    }
    return m_rw.first;
  }
  double getWeightsDtilde(int entry, int EventNumber, double ecm, double mH,int npafin, int ifl1in,int ifl2in,int ifl1out, int ifl2out, int ifl3out, double x1, double x2, double* pjet1, double *pjet2, double *pjet3, double *phiggs)
  {
    if (EventNumber != m_wdt.second) 
    {
      m_wdt = std::make_pair(
                        HLeptonsCPRW::getWeightsDtilde( ecm,  mH, npafin,  ifl1in, ifl2in, ifl1out,  ifl2out,  ifl3out,  x1,  x2, pjet1,  pjet2,  pjet3,  phiggs)
                        ,EventNumber);

    }
    if (entry == 0)
      return m_wdt.first.first;
    else if (entry == 1)
      return m_wdt.first.second;
    else
    {
      std::cout << "Error, entry must be 0/1. Returning -1234! ";
      return -1234;
    }
  }
  double getOptObs(int entry, int EventNumber, double ecm,double mH,double x1,double x2,double Q, double* pjet1, double* pjet2, double* phiggs)
  {
    double a_pdf1[13];
    double a_pdf2[13];
    if (EventNumber != m_oo.second) 
    {
      std::vector<double> pdf1 = getLHAPDF(Q,x1);
      std::vector<double> pdf2 = getLHAPDF(Q,x2);
      for (unsigned int i=0; i<pdf1.size(); ++i)
      {
        a_pdf1[i] = pdf1.at(i);
        a_pdf2[i] = pdf2.at(i);
      }
      m_oo = std::make_pair(
                        HLeptonsCPRW::getOptObs( ecm, mH, x1, x2, a_pdf1, a_pdf2, pjet1, pjet2, phiggs)
                        ,EventNumber);

    }
    if (entry == 0)
      return m_oo.first.first;
    else if (entry == 1)
      return m_oo.first.second;
    else
    {
      std::cout << "Error, entry must be 0/1. Returning -1234! ";
      return -1234;
    }
  }

  void initPDFSet(std::string,int,double);
};
/*};*/
/*{*/
    /*      */
/*};*/

#endif

