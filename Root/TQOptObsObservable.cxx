#include "HLeptonsCPRW/TQOptObsObservable.h"
#ifdef ROOTCORE_PACKAGE_QFramework
ClassImp(TQOptObsObservable)
#include "QFramework/TQUtils.h"

//#define _DEBUG_
#include "QFramework/TQLibrary.h"
#include "TSystem.h"
#include "TLorentzVector.h"


//______________________________________________________________________________________________

TQOptObsObservable::TQOptObsObservable(TString variable, TQTaggable *tags, double dtilde) :
TQTreeObservable()
{
  // default constructor
  m_ooE = new OptObsEventStore();
  m_tags = tags;
  m_var = variable;
}


//______________________________________________________________________________________________

bool TQOptObsObservable::initializeSelf(){
  // initialize the formula of this observable
  DEBUGclass("initializing ...");

  m_EventNumber = new TTreeFormula("event_number","event_number",fTree);

  if (m_tags->getTagBoolDefault("isTruth",false))
  {
    m_jet_0_pt =    new TTreeFormula("truth_opt_obs_parton_0_pt",    "truth_opt_obs_parton_0_pt", fTree);
    m_jet_0_eta =   new TTreeFormula("truth_opt_obs_parton_0_eta",   "truth_opt_obs_parton_0_eta",fTree);
    m_jet_0_phi =   new TTreeFormula("truth_opt_obs_parton_0_phi",   "truth_opt_obs_parton_0_phi",fTree);
    m_jet_0_m =     new TTreeFormula("truth_opt_obs_parton_0_m",     "truth_opt_obs_parton_0_m",  fTree);
    m_jet_0_pdgId = new TTreeFormula("truth_opt_obs_parton_0_pdgId", "truth_opt_obs_parton_0_pdgId",  fTree);

    m_jet_1_pt =    new TTreeFormula("truth_opt_obs_parton_1_pt",    "truth_opt_obs_parton_1_pt", fTree);
    m_jet_1_eta =   new TTreeFormula("truth_opt_obs_parton_1_eta",   "truth_opt_obs_parton_1_eta",fTree);
    m_jet_1_phi =   new TTreeFormula("truth_opt_obs_parton_1_phi",   "truth_opt_obs_parton_1_phi",fTree);
    m_jet_1_m =     new TTreeFormula("truth_opt_obs_parton_1_m",     "truth_opt_obs_parton_1_m",  fTree);
    m_jet_1_pdgId = new TTreeFormula("truth_opt_obs_parton_1_pdgId", "truth_opt_obs_parton_1_pdgId",  fTree);

    m_jet_2_pt =    new TTreeFormula("truth_opt_obs_parton_2_pt",    "truth_opt_obs_parton_2_pt", fTree);
    m_jet_2_eta =   new TTreeFormula("truth_opt_obs_parton_2_eta",   "truth_opt_obs_parton_2_eta",fTree);
    m_jet_2_phi =   new TTreeFormula("truth_opt_obs_parton_2_phi",   "truth_opt_obs_parton_2_phi",fTree);
    m_jet_2_m =     new TTreeFormula("truth_opt_obs_parton_2_m",     "truth_opt_obs_parton_2_m",  fTree);
    m_jet_2_pdgId = new TTreeFormula("truth_opt_obs_parton_2_pdgId", "truth_opt_obs_parton_2_pdgId",  fTree);

    m_h_pt =    new TTreeFormula("truth_opt_obs_higgs_pt",    "truth_opt_obs_higgs_pt", fTree);
    m_h_eta =   new TTreeFormula("truth_opt_obs_higgs_eta",   "truth_opt_obs_higgs_eta",fTree);
    m_h_phi =   new TTreeFormula("truth_opt_obs_higgs_phi",   "truth_opt_obs_higgs_phi",fTree);
    m_h_m =     new TTreeFormula("truth_opt_obs_higgs_m",     "truth_opt_obs_higgs_m",  fTree);

    m_x1 = new TTreeFormula("truth_event_info_x1","truth_event_info_x1",fTree);
    m_x2 = new TTreeFormula("truth_event_info_x2","truth_event_info_x2",fTree);

    m_pdgIn1 = new TTreeFormula("truth_event_info_parton_0_pdgId","truth_event_info_parton_0_pdgId", fTree);
    m_pdgIn2 = new TTreeFormula("truth_event_info_parton_0_pdgId","truth_event_info_parton_0_pdgId", fTree);

  }

  else
  {
    m_jet_0_pt =  new TTreeFormula("jet_0_pt", "jet_0_pt", fTree);
    m_jet_0_eta = new TTreeFormula("jet_0_eta","jet_0_eta",fTree);
    m_jet_0_phi = new TTreeFormula("jet_0_phi","jet_0_phi",fTree);
    m_jet_0_m =   new TTreeFormula("jet_0_m",  "jet_0_m",  fTree);

    m_jet_1_pt =  new TTreeFormula("jet_1_pt", "jet_1_pt", fTree);
    m_jet_1_eta = new TTreeFormula("jet_1_eta","jet_1_eta",fTree);
    m_jet_1_phi = new TTreeFormula("jet_1_phi","jet_1_phi",fTree);
    m_jet_1_m =   new TTreeFormula("jet_1_m",  "jet_1_m",  fTree);

    m_jet_2_pt =  new TTreeFormula("jet_2_pt", "jet_2_pt", fTree);
    m_jet_2_eta = new TTreeFormula("jet_2_eta","jet_2_eta",fTree);
    m_jet_2_phi = new TTreeFormula("jet_2_phi","jet_2_phi",fTree);
    m_jet_2_m =   new TTreeFormula("jet_2_m",  "jet_2_m",  fTree);

    m_h_pt = new TTreeFormula("lephad_mmc_maxw_pt","lephad_mmc_maxw_pt",fTree);
    m_h_eta = new TTreeFormula("lephad_mmc_maxw_eta","lephad_mmc_maxw_eta",fTree);
    m_h_phi = new TTreeFormula("lephad_mmc_maxw_phi","lephad_mmc_maxw_phi",fTree);
    m_h_m = new TTreeFormula("lephad_mmc_maxw_m","lephad_mmc_maxw_m",fTree);
  }

  DEBUGclass("initialized!");
  
  return true;
}

//______________________________________________________________________________________________

bool TQOptObsObservable::finalizeSelf(){
  delete m_ooE;
  delete m_EventNumber;
  delete m_jet_0_pt;
  delete m_jet_0_eta;
  delete m_jet_0_phi;
  delete m_jet_0_m;
  delete m_jet_0_pdgId;

  delete m_jet_1_pt;
  delete m_jet_1_eta;
  delete m_jet_1_phi;
  delete m_jet_1_m;
  delete m_jet_1_pdgId;

  delete m_jet_2_pt;
  delete m_jet_2_eta;
  delete m_jet_2_phi;
  delete m_jet_2_m;
  delete m_jet_2_pdgId;

  delete m_h_pt;
  delete m_h_eta;
  delete m_h_phi;
  delete m_h_m;

  delete m_x1;
  delete m_x2;
  delete m_pdgIn1;
  delete m_pdgIn2;
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

  //
  double ecm = m_tags->getTagDoubleDefault("ecm",13000);                           //proton-proton center-of mass energy in GeV
  double Q =  m_tags->getTagDoubleDefault("scale_Q",125); // scale used for lhapdf
  double mH = m_h_m->EvalInstance();


  int eventNumber = m_EventNumber->EvalInstance();

  double x1,x2;

  int npafin = 2;


  // find the two non-gluon final state partons
  std::vector<double*> pjets;
  TLorentzVector v;
  std::vector<int> flavourIn, flavourOut;
  if (m_tags->getTagBoolDefault("isTruth",false))
  {
    x1 = m_x1->EvalInstance();           
    x2 = m_x2->EvalInstance();
    flavourIn.push_back(m_pdgIn1->EvalInstance());
    flavourIn.push_back(m_pdgIn2->EvalInstance());
    if (m_jet_0_pdgId->EvalInstance() != 21)
    {
      v.SetPtEtaPhiM(m_jet_0_pt->EvalInstance(),m_jet_0_eta->EvalInstance(),m_jet_0_phi->EvalInstance(),m_jet_0_m->EvalInstance());
      double p[] = {v.E(),v.Px(),v.Py(),v.Pz()};
      pjets.push_back(p);
      flavourOut.push_back(m_jet_0_pdgId->EvalInstance());
    }
    if (m_jet_1_pdgId->EvalInstance() != 21)
    {
      v.SetPtEtaPhiM(m_jet_1_pt->EvalInstance(),m_jet_1_eta->EvalInstance(),m_jet_1_phi->EvalInstance(),m_jet_1_m->EvalInstance());
      double p[] = {v.E(),v.Px(),v.Py(),v.Pz()};
      pjets.push_back(p);
      flavourOut.push_back(m_jet_1_pdgId->EvalInstance());
    }
    v.SetPtEtaPhiM(m_jet_2_pt->EvalInstance(),m_jet_2_eta->EvalInstance(),m_jet_2_phi->EvalInstance(),m_jet_2_m->EvalInstance());
    double p[] = {v.E(),v.Px(),v.Py(),v.Pz()};
    pjets.push_back(p);
    flavourOut.push_back(m_jet_0_pdgId->EvalInstance());
    if (v.Pt() > 0)
      npafin = 3;
    if (m_jet_0_pdgId->EvalInstance() != 21 && pjets.size() < 3)
    {
      v.SetPtEtaPhiM(m_jet_0_pt->EvalInstance(),m_jet_0_eta->EvalInstance(),m_jet_0_phi->EvalInstance(),m_jet_0_m->EvalInstance());
      double p[] = {v.E(),v.Px(),v.Py(),v.Pz()};
      pjets.push_back(p);
      flavourOut.push_back(m_jet_0_pdgId->EvalInstance());
    }
    if (m_jet_1_pdgId->EvalInstance() != 21 && pjets.size() < 3)
    {
      v.SetPtEtaPhiM(m_jet_1_pt->EvalInstance(),m_jet_1_eta->EvalInstance(),m_jet_1_phi->EvalInstance(),m_jet_1_m->EvalInstance());
      double p[] = {v.E(),v.Px(),v.Py(),v.Pz()};
      pjets.push_back(p);
      flavourOut.push_back(m_jet_1_pdgId->EvalInstance());
    }
  }

  else
  {
    
    v.SetPtEtaPhiM(m_jet_0_pt->EvalInstance(),m_jet_0_eta->EvalInstance(),m_jet_0_phi->EvalInstance(),m_jet_0_m->EvalInstance());
    double p[] = {v.E(),v.Px(),v.Py(),v.Pz()};
    pjets.push_back(p);
    TLorentzVector fO = (TLorentzVector(m_h_pt->EvalInstance(),m_h_eta->EvalInstance(),m_h_phi->EvalInstance(),m_h_m->EvalInstance()) + v + TLorentzVector(m_jet_1_pt->EvalInstance(),m_jet_1_eta->EvalInstance(),m_jet_1_phi->EvalInstance(),m_jet_1_m->EvalInstance()));
    x1 = ((fO).M()/ecm)*TMath::Exp(fO.Rapidity());
    x2 = ((fO).M()/ecm)*TMath::Exp(fO.Rapidity()*-1);

    v.SetPtEtaPhiM(m_jet_1_pt->EvalInstance(),m_jet_1_eta->EvalInstance(),m_jet_1_phi->EvalInstance(),m_jet_1_m->EvalInstance());
    double p2[] = {v.E(),v.Px(),v.Py(),v.Pz()};
    pjets.push_back(p2);
  }


  v.SetPtEtaPhiM(m_h_pt->EvalInstance(),m_h_eta->EvalInstance(),m_h_phi->EvalInstance(),m_h_m->EvalInstance());
  double phiggs[] = {v.E(),v.Px(),v.Py(),v.Pz()};     
 


  //
  //***************

  DEBUGclass("getting value for variable %s!",m_var.Data());
  double retval = -999;
  //m_jet_pt->GetNdata();
  int entry = -1;
  if (m_var.Contains("0") || m_var.Contains("_lin"))
    entry = 0;
  else if (m_var.Contains("1") || m_var.Contains("_quad"))
    entry = 1;
  if (m_var.Contains("OptimalObservable"))
    retval = m_ooE->getOptObs(entry, eventNumber, ecm, mH ,x1,x2,Q,pjets[0],pjets[1],phiggs);
  else if (m_var.Contains("WeightDTilde"))
    retval = m_ooE->getWeightsDtilde(entry, eventNumber, ecm, mH , npafin,flavourIn[0],flavourIn[1],flavourOut[0],flavourOut[1],flavourOut[3],x1,x2,pjets[0],pjets[1],pjets[2],phiggs);
  else if (m_var.Contains("Reweight"))
    retval = m_ooE->getReweight(ecm, mH, 1 , 
        0.5, 0.5, 0.5, 0.5, 0.5, //rsmin,din,dbin,dtin,dtbin
        0.5, 0.5, 0.5,           //a1hwwin,a2hwwin,a3hwwin
        0.5, 0.5, 0.5,           //a1haain,a2haain,a3haain
        0.5, 0.5, 0.5,           //a1hazin,a2hazin,a3hazin
        0.5, 0.5, 0.5,           //a1hzzin,a2hzzin,a3hzzin
        0.5,                     //lambdahvvin for formfactor if set to positive value
        npafin,flavourIn[0],flavourIn[1],flavourOut[0],flavourOut[1],flavourOut[2],
        x1,x2,pjets[0],pjets[1],pjets[2],phiggs);
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
