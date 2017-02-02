#include "HLeptonsCPRW/TQOptObsObservable.h"
#include "QFramework/TQUtils.h"

//#define _DEBUG_
#include "QFramework/TQLibrary.h"
#include "TSystem.h"

ClassImp(TQOptObsObservable)

//______________________________________________________________________________________________

TQOptObsObservable::TQOptObsObservable(OptObsEventStore *ooe,TString variable) :
TQTreeObservable()
{
  // default constructor
  m_ooE = ooe;
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
  DEBUGclass("getting value for variable %s!",m_var.Data());
  double retval = -999;
  m_EventNumber->GetNdata();
  //m_jet_pt->GetNdata();
  int entry = -1;
  if (m_var.Contains("1"))
    entry = 1;
  else if (m_var.Contains("0"))
    entry = 0;
  if (m_var.Contains("OptimalObservable"))
    //retval = m_ooE->getOptObs(entry, m_EventNumber, ecm, mH ,x1,x2,Q,pjet1,pjet2,phiggs);
    retval = 1.0;
  //else if (m_var == "phi")
  //retval = m_jet_phi->EvalInstance();
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

