This is a RootCore-compliant wrapper around Fortran-routines written by M. Schumacher using routines from hawk (https://hawk.hepforge.org). 
The header has three functions in the namespace HLeptonsCPRW:

    -  double getReweight(double ecm, double mH, int ipara, double rsmin, 
   double din, double dbin, double dtin, double dtbin, double lambdahvvin, 
   double a1hwwin, double a2hwwin, double a3hwwin, double a1haain, double a2haain, double a3haain, 
   double a1hazin,  double a2hazin, double a3hazin, double a1hzzin, double a2hzzin, double a3hzzin, 
   int npafin, int iflin1, int iflin2, int iflout1, int iflout2, int iflout3, 
   double x1, double x2, double *pjet1, double *pjet2, double *pjet3, double *phiggs);
   
   the inputs are:
   
              ecms proton-pton center-of mass energy in GeV 
              mhiggs mass of Higgs boson in Gev
              ipara = 1 use parametrization in terms of d, db dt, dbt etc.
                      else use parametrization in a1, a2, a3
              anomalous couplings: rsmin,din,dbin,dtin,dtbin, 
              a1hwwin,a2hwwin,a3hwwin,a1haain,a2haain,a3haain,
              a1hazin,a2hazin,a3hazin,a1hzzin,a2hzzin,a3hzzin
              lambdahvvin for formfactor if set to positive value
              set lambdahvvin to negative values in ordr no to use formfactors
 
              npafin:   number of partons in final state  either  2 or 3 
              ifl1in:   flavour of incoming parton 1  
              ifl2in:   flavour of incoming parton 2
              ifl1out:  flavour of outgoing parton 1  
              ifl2out:  flavour of outgoing parton 2
              ifl3out:  flavour of outgoing parton 3
 
              flavour assignment: t = 6  b = 5 c = 4, s = 3, u = 2, d = 1   
                                  anti-qarks with negative sign
                                  gluon = 0 
    
              x1, x2:   Bjorken x of incoming partons,  
                        1 in + z , 2 in -z direction
              pjet1(0:3):  E,px,py,pz of 1st final state parton
              pjet2(0:3):  E,px,py,pz of 2nd final state parton 
              pjet3(0:3):  E,px,py,pz of 3rd final state parton 
                          if npafin=3.  gluon should be 3rd parton
              phiggs(0:3): E,px,py,pz of Higgs boson
              make sure that four momentum conservation holds 
              
  
  returning a single event weight to reweight from SM to the chosen parameters.
  
  ===================================================
   
    - std::pair<double,double> getWeightsDtilde(double ecm, double mH,int npafin, int ifl1in,int ifl2in,int ifl1out, int ifl2out, int ifl3out, double x1, double x2, double* pjet1, double *pjet2, double *pjet3, double *phiggs);
   
   the inputs are:
              ecms proton-proton center-of mass energy in GeV 
              mhiggs mass of Higgs boson in Gev
 
              npafin:   number of partons in final state  either  2 or 3 
              ifl1in:   flavour of incoming parton 1  
              ifl2in:   flavour of incoming parton 2
              ifl1out:  flavour of outgoing parton 1  
              ifl2out:  flavour of outgoing parton 2
              ifl3out:  flavour of outgoing parton 3
 
              flavour assignment: t = 6  b = 5 c = 4, s = 3, u = 2, d = 1   
                                  anti-qarks with negative sign
                                  gluon = 0 
    
              x1, x2:   Bjorken x of incoming partons,  
                        1 in + z , 2 in -z direction
              pjet1(0:3):  E,px,py,pz of 1st final state parton
              pjet2(0:3):  E,px,py,pz of 2nd final state parton 
              pjet3(0:3):  E,px,py,pz of 3rd final state parton 
                           if npafin=3.  gluon should be 3rd parton
              phiggs(0:3): E,px,py,pz of Higgs boson
              make sure that four-momentum conservation holds 

   returning a pair (wedtlin,wedtquad) which are the contributions to the event weight. The event weight is decomposed as weight = 1 + dtilde wedtline + dtilde^2 wedtquad. 
   The weight is calculated under the assumption dtilde=detilde_b and all other anomalous couplings/ Wilson coefficients asumed to vanish.
     
  ===================================================
   
    - std::pair<double,double> getOptObs(double ecm,double mH,double x1,double x2,double pdf1,double pdf2, double* pjet1, double* pjet2, double* phiggs);
    
    the inputs are:
             ecms proton-pton center-of mass energy in GeV 
             mhiggs mass of Higgs boson in GeV
             1st incoming parton in positive z direction
             2nd incoming parton in negative z direction
             x1, x2: Bjorken x of 1st and 2ns incoming partons
             pdf1,pdf2 from -6 to 6: pdfs for 1st and 2nd parton
             pjet1(0:3):  E,px,py,pz of 1st outgoing jet
             pjet1(0:3):  E,px,py,pz of 2nd outgoing jet
             phiggs(0:3): E,px,py,pz of Higgs boson
    
    returning a pair (oo1,oo2) which are the optimal observables of 1st and 2nd order.