#include "HLeptonsCPRW/WeightAndOptObsWrapper.h"

extern "C"
{
  void optobs_(double*, double*, double*, double*, double*, double*, double*, double*, double*,
               double*, double*, int*); 
  
  void reweight_(double*, double*, int*, double*,
		 double*, double*, double*, double*, double*,
		 double*, double*, double*, double*, double*, double*,
		 double*, double*, double*, double*, double*, double*,
		 int*, int*, int*, int*, int*, int*,  
		 double*, double*, double*, double*, double*, double*, 
		 double*, int*); 

  void weightdtilde_(double*,double*,
          int*,int*,int*,int*,int*,int*,  
          double*,double*,double*,double*,double*,double*,
          double*,double*, int*); 

}

namespace HLeptonsCPRW {

  std::pair<double,double> getWeightsDtilde(double ecm, double mH, int npafin,int ifl1in,int ifl2in,int ifl1out, int ifl2out, int ifl3out, double x1, double x2, double* pjet1, double *pjet2, double *pjet3, double *phiggs) {
    double wedtlin = -999.0;
    double wedtquad = -999.0;
    int ierr =-1;
    weightdtilde_(&ecm,&mH,&npafin,&ifl1in,&ifl2in,&ifl1out,&ifl2out,&ifl3out,&x1,&x2,pjet1,pjet2,pjet3,phiggs,&wedtlin,&wedtquad,&ierr);
    if (ierr != 0)
      std::cout<<"Problem in getWeightDtilde. Check output!"<<std::endl;
    return std::make_pair(wedtlin,wedtquad);
  }
  double getReweight(double ecm, double mH, int ipara, double rsmin, 
  double din, double dbin, double dtin, double dtbin, double lambdahvvin, 
  double a1hwwin, double a2hwwin, double a3hwwin, double a1haain, double a2haain, double a3haain, 
  double a1hazin,  double a2hazin, double a3hazin, double a1hzzin, double a2hzzin, double a3hzzin, 
  int npafin, int iflin1, int iflin2, int iflout1, int iflout2, int iflout3, 
  double x1, double x2, double *pjet1, double *pjet2, double *pjet3, double *phiggs)
  {
    double weight = -999.0;
    int ierr =-1;
    reweight_(&ecm,&mH, &ipara, &rsmin, &din, &dbin, &dtin, &dtbin, &lambdahvvin, &a1hwwin, &a2hwwin, &a3hwwin, &a1haain, &a2haain, &a3haain, &a1hazin, &a2hazin, &a3hazin, &a1hzzin, &a2hzzin, &a3hzzin, &npafin, &iflin1, &iflin2, &iflout1, &iflout2, &iflout3, &x1, &x2, pjet1, pjet2, pjet3, phiggs, &weight,&ierr);
    if (ierr != 0)
      std::cout<<"Problem in getReweight. Check output!"<<std::endl;
    return weight;
  }

  std::pair<double,double> getOptObs(double ecm,double mH,double x1,double x2,double pdf1,double pdf2, double *pjet1, double *pjet2, double *phiggs) {
    double oo1=-1;
    double oo2=-1;
    int ierr =-1;
    optobs_(&ecm,&mH,&x1,&x2,&pdf1,&pdf2,pjet1,pjet2,phiggs,&oo1,&oo2,&ierr);
    if (ierr != 0)
      std::cout<<"Problem in getOptObs. Check output!"<<std::endl;
    return std::make_pair(oo1,oo2);
  }

}
