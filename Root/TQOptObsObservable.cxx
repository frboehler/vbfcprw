#include "HLeptonsCPRW/TQOptObsObservable.h"
#ifdef ROOTCORE_PACKAGE_QFramework
ClassImp(TQOptObsObservable)
#include "QFramework/TQUtils.h"

//#define _DEBUG_
#include "QFramework/TQLibrary.h"
#include "TSystem.h"


//______________________________________________________________________________________________

TQOptObsObservable::TQOptObsObservable(TString variable, double dtilde) :
TQTreeObservable()
{
  // default constructor
  m_ooE = new OptObsEventStore();
  m_var = variable;
}


//______________________________________________________________________________________________

bool TQOptObsObservable::initializeSelf(){
  // initialize the formula of this observable
  DEBUGclass("initializing ...");

  m_EventNumber = new TTreeFormula("EventNumber","EventNumber",fTree);
  //m_jet_eta = new TTreeFormula("jet_eta",TString::Format("jet_eta[%i]",m_jetN),fTree);

  DEBUGclass("initialized!");
  
  return true;
}

//______________________________________________________________________________________________

bool TQOptObsObservable::finalizeSelf(){
  delete m_ooE;
  delete m_EventNumber;
  //.
  //.
  //.

  return true;
}

//______________________________________________________________________________________________

TQOptObsObservable::~TQOptObsObservable(){
}

//______________________________________________________________________________________________

double TQOptObsObservable::getValue() const {
  // retrieve the value of this tree observable
  // return NaN in case of failure

  //************
  // This needs to be filled with proper branches from ntuples
  //
  m_EventNumber->GetNdata();
  int eventNumber = m_EventNumber->EvalInstance();
  double pjet1[] = {60,25,25,25};               //E,px,py,pz of nth final state parton
  double pjet2[] = {76,44,12,24};
  double pjet3[] = {23,70,11,111};
  double phiggs[] = {123,12,44,123};            //E,px,py,pz of Higgs boson make sure that four-momentum conservation holds 
 
  double ecm = 13000;                           //proton-proton center-of mass energy in GeV
  double mH = 125;                              //mass of Higgs boson in Gev
  int npafin = 2;                               //number of partons in final state  either  2 or 3
  double x1 = 0.2;                              //Bjorken x of incoming partons, 1 in + z , 2 in -z direction
  double x2 = 0.3;
  double Q = 84000;
  int flavour1In = 1;                           //flavour of incoming/outgoing parton n
  int flavour2In = 1;                           //flavour assignment: t = 6  b = 5 c = 4, s = 3, u = 2, d = 1   
  int flavour1Out = 1;                          //anti-qarks with negative sign
  int flavour2Out = 1;                          //gluon = 0 
  int flavour3Out = 1;
  //
  //***************

  DEBUGclass("getting value for variable %s!",m_var.Data());
  double retval = -999;
  //m_jet_pt->GetNdata();
  int entry = -1;
  if (m_var.Contains("1") || m_var.Contains("_lin"))
    entry = 1;
  else if (m_var.Contains("0"))
    entry = 0;
  if (m_var.Contains("OptimalObservable") || m_var.Contains("_quad"))
    retval = m_ooE->getOptObs(entry, eventNumber, ecm, mH ,x1,x2,Q,pjet1,pjet2,phiggs);
  else if (m_var.Contains("WeightDTilde"))
    retval = m_ooE->getWeightsDtilde(entry, eventNumber, ecm, mH , npafin,flavour1In,flavour2In,flavour1Out,flavour2Out,flavour3Out,x1,x2,pjet1,pjet2,pjet3,phiggs);
  else if (m_var.Contains("Reweight"))
    retval = m_ooE->getReweight(ecm, mH, 1 , 
        0.5, 0.5, 0.5, 0.5, 0.5, //rsmin,din,dbin,dtin,dtbin
        0.5, 0.5, 0.5,           //a1hwwin,a2hwwin,a3hwwin
        0.5, 0.5, 0.5,           //a1haain,a2haain,a3haain
        0.5, 0.5, 0.5,           //a1hazin,a2hazin,a3hazin
        0.5, 0.5, 0.5,           //a1hzzin,a2hzzin,a3hzzin
        0.5,                     //lambdahvvin for formfactor if set to positive value
        npafin,flavour1In,flavour2In,flavour1Out,flavour2Out,flavour3Out,
        x1,x2,pjet1,pjet2,pjet3,phiggs);
  DEBUGclass("Returning %f for variable %s",retval,m_var.Data());
  return retval;
}



//______________________________________________________________________________________________

TObjArray* TQOptObsObservable::getBranchNames() const {
  // retrieve the list of branch names 
  // ownership of the list belongs to the caller of the function
  DEBUGclass("getting branch names!");
  TObjArray* retval = new TObjArray();
  retval->Add(new TObjString("EventNumber"));
  //.
  //.
  //.
  return retval;
}

#endif
