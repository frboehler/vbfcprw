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

  //LHAPDF::initPDF(0);
  for (int f = -6; f <= 6; ++f) {
    if(f==0){
      double v = LHAPDF::xfx(x, Q, 0);
      //double v2 = LHAPDF::xfx(x, Q, 21);
      //      cout << "x=" << x << ", Q=" << Q << ", f=" <<f<<":"<< v << " " << v2 <<endl;
      val.push_back(v);
    }
    else{
      double v = LHAPDF::xfx(x, Q, f);
      //      cout << "x=" << x << ", Q=" << Q << ", f=" <<f<<":"<< v << endl;
      val.push_back(v);
    }
  }
  //  cout << endl;
  /* for (int n = 0; n < NUMBER + 1; ++n) { */
  /*   cout << "Set number: " << n << endl; */
  /*   LHAPDF::initPDF(n); */
  /*   for (int ix = 1; ix < 11; ++ix) { */
  /*     const double x = (ix - 0.5) / 10.0; */
  /*     cout << "x=" << x << ", Q=" << Q << ": "; */
  /*     vector<double> result = LHAPDF::xfx(x, Q); */
  /*     std::copy(result.begin(), result.end(), ostream_iterator<double>(cout,"\t")); */
  /*     cout << endl; */
  /*   } */
  /*   cout << endl; */
  /* } */


  /* cout << string().insert(0, 40, '-') << endl << endl; */
  /* cout << "Checking LHAPDF with package " << endl; */
  /* cout << NAME << " set number " << SUBSET << "/" << LHAPDF::numberPDF() << endl << endl; */
  /* cout << "LHAPDF::getDescription() gives:" << endl; */
  /* LHAPDF::getDescription(); */

  return val;

}
