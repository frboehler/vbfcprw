#include "HLeptonsCPRW/OptObsEventStore.h"
#include <LHAPDF/LHAPDF.h>

void OptObsEventStore::initPDFSet(std::string NAME, int SUBSET, double mZ)
{
  LHAPDF::initPDFSet(NAME, LHAPDF::LHGRID, SUBSET);
    std::cout << "alphas(mZ) = " << LHAPDF::alphasPDF(mZ) << std::endl;
    std::cout << "qcdlam4    = " << LHAPDF::getLam4(SUBSET) << std::endl;
    std::cout << "qcdlam5    = " << LHAPDF::getLam5(SUBSET) << std::endl;
    std::cout << "orderPDF   = " << LHAPDF::getOrderPDF() << std::endl;
    std::cout << "xmin       = " << LHAPDF::getXmin(SUBSET) << std::endl;
    std::cout << "xmax       = " << LHAPDF::getXmax(SUBSET) << std::endl;
    std::cout << "q2min      = " << LHAPDF::getQ2min(SUBSET) << std::endl;
    std::cout << "q2max      = " << LHAPDF::getQ2max(SUBSET) << std::endl;
    std::cout << "orderalfas = " << LHAPDF::getOrderAlphaS() << std::endl;
    std::cout << "num flav   = " << LHAPDF::getNf() << std::endl;
    std::cout << "name       = " << NAME << std::endl;
    std::cout << "number     = " << LHAPDF::numberPDF() << std::endl;
    std::cout << std::endl;
    m_isInitialized = true;
}

std::vector<double> OptObsEventStore::getLHAPDF(double Q, double x){

  std::vector<double> val;
  val.clear();
  if (!m_isInitialized)
  {
    std::cout<<"ERROR in getLHAPDF! OptObsEventStore not initialized with a pdf set. Call initPDFSet first!"<<std::endl;
    return val;
  }

  for (int f = -6; f <= 6; ++f) {
    double v;
    v = LHAPDF::xfx(x, Q, f);
    val.push_back(v);
  }
  return val;

}


double OptObsEventStore::getOptObs(int entry, int EventNumber, double ecm,double mH,double x1,double x2,double Q, double* pjet1, double* pjet2, double* phiggs)
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


double OptObsEventStore::getWeightsDtilde(int entry, int EventNumber, double ecm, double mH,int npafin, int ifl1in,int ifl2in,int ifl1out, int ifl2out, int ifl3out, double x1, double x2, double* pjet1, double *pjet2, double *pjet3, double *phiggs)
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
