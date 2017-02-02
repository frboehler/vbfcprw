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
