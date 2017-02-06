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
  m_tags = tags;
  m_ooE = new OptObsEventStore();
  m_ooE->initPDFSet(m_tags->getTagStringDefault("PDFset","CT10").Data(),0,91.2);
  m_var = variable;
}
TQOptObsObservable::TQOptObsObservable(TString variable, double dtilde) :
TQTreeObservable()
{
  // default constructor
  m_tags = new TQTaggable();
  m_ooE = new OptObsEventStore();
  m_ooE->initPDFSet(m_tags->getTagStringDefault("PDFset","CT10").Data(),0,91.2);
  m_var = variable;
}

TQOptObsObservable::TQOptObsObservable(TString variable, TString tags, double dtilde) :
TQTreeObservable()
{
  // default constructor
  m_tags = new TQTaggable();
  m_tags->importTags(tags);
  m_ooE = new OptObsEventStore();
  m_ooE->initPDFSet(m_tags->getTagStringDefault("PDFset","CT10").Data(),0,91.2);
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

    m_x1 = new TTreeFormula("truth_event_info_Bjorken_x1","truth_event_info_Bjorken_x1",fTree);
    m_x2 = new TTreeFormula("truth_event_info_Bjorken_x2","truth_event_info_Bjorken_x2",fTree);

    m_pdgIn1 = new TTreeFormula("truth_event_info_pdgId1","truth_event_info_pdgId1", fTree);
    m_pdgIn2 = new TTreeFormula("truth_event_info_pdgId2","truth_event_info_pdgId2", fTree);

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

  delete m_jet_1_pt;
  delete m_jet_1_eta;
  delete m_jet_1_phi;
  delete m_jet_1_m;

  delete m_jet_2_pt;
  delete m_jet_2_eta;
  delete m_jet_2_phi;
  delete m_jet_2_m;

  delete m_h_pt;
  delete m_h_eta;
  delete m_h_phi;
  delete m_h_m;

  if (m_tags->getTagBoolDefault("isTruth",false))
  {
    delete m_jet_0_pdgId;
    delete m_jet_1_pdgId;
    delete m_jet_2_pdgId;
    delete m_x1;
    delete m_x2;
    delete m_pdgIn1;
    delete m_pdgIn2;
  }



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
  //ERRORclass("%i",eventNumber);

  double x1,x2;

  int npafin = 2;


  // find the two non-gluon final state partons
  std::vector<double*> pjets;
  double p1[4],p2[4],p3[4];
  DEBUGclass("size = %i",pjets.size());
  TLorentzVector v;
  std::vector<int> flavourIn, flavourOut;
  if (m_tags->getTagBoolDefault("isTruth",false))
  {
    DEBUGclass("Running truth observable");
    x1 = m_x1->EvalInstance();           
    x2 = m_x2->EvalInstance();
    flavourIn.push_back(m_pdgIn1->EvalInstance());
    flavourIn.push_back(m_pdgIn2->EvalInstance());
    if (m_jet_0_pdgId->EvalInstance() != 21)
    {
      v.SetPtEtaPhiM(m_jet_0_pt->EvalInstance(),m_jet_0_eta->EvalInstance(),m_jet_0_phi->EvalInstance(),m_jet_0_m->EvalInstance());
      p1[0] = v.E();
      p1[1] = v.Px();
      p1[2] = v.Py();
      p1[3] = v.Pz();
      pjets.push_back(p1);
      flavourOut.push_back(m_jet_0_pdgId->EvalInstance());
      //ERRORclass("pushing back 1 - 1");
    }
    if (m_jet_1_pdgId->EvalInstance() != 21)
    {
      v.SetPtEtaPhiM(m_jet_1_pt->EvalInstance(),m_jet_1_eta->EvalInstance(),m_jet_1_phi->EvalInstance(),m_jet_1_m->EvalInstance());
      p2[0] = v.E();
      p2[1] = v.Px();
      p2[2] = v.Py();
      p2[3] = v.Pz();
      pjets.push_back(p2);
      flavourOut.push_back(m_jet_1_pdgId->EvalInstance());
      //ERRORclass("pushing back 2 - 1");
    }
    v.SetPtEtaPhiM(m_jet_2_pt->EvalInstance(),m_jet_2_eta->EvalInstance(),m_jet_2_phi->EvalInstance(),m_jet_2_m->EvalInstance());
    ERRORclass("%f",v.Pt());
    if (v.Pt()>0)
    {
      p3[0] = v.E();
      p3[1] = v.Px();
      p3[2] = v.Py();
      p3[3] = v.Pz();
      pjets.push_back(p3);
      if (m_jet_2_pdgId->EvalInstance() == 21)
        flavourOut.push_back(0);
      else
        flavourOut.push_back(m_jet_2_pdgId->EvalInstance());
      npafin = 3;
    }
    //ERRORclass("pushing back 3 - 1");
    //if (v.Pt() > 0)
    //if (m_jet_0_pdgId->EvalInstance() != 21 && pjets.size() < 3)
    //{
    //v.SetPtEtaPhiM(m_jet_0_pt->EvalInstance(),m_jet_0_eta->EvalInstance(),m_jet_0_phi->EvalInstance(),m_jet_0_m->EvalInstance());
    //p1[0] = v.E();
    //p1[1] = v.Px();
    //p1[2] = v.Py();
    //p1[3] = v.Pz();
    //pjets.push_back(p1);
    //flavourOut.push_back(m_jet_0_pdgId->EvalInstance());
    //}
    //if (m_jet_1_pdgId->EvalInstance() != 21 && pjets.size() < 3)
    //{
    //v.SetPtEtaPhiM(m_jet_1_pt->EvalInstance(),m_jet_1_eta->EvalInstance(),m_jet_1_phi->EvalInstance(),m_jet_1_m->EvalInstance());
    //p2[0] = v.E();
    //p2[1] = v.Px();
    //p2[2] = v.Py();
    //p2[3] = v.Pz();
    //pjets.push_back(p2);
    //flavourOut.push_back(m_jet_1_pdgId->EvalInstance());
    //}

    //for (unsigned int i=0; i<flavourIn.size(); ++i)
    //ERRORclass("i = %i flav = %i",i,flavourIn[i]);
    //for (unsigned int i=0; i<flavourOut.size(); ++i)
    //ERRORclass("i = %i flavOut = %i",i,flavourOut[i]);
  }

  else
  {
    DEBUGclass("Running reco observable");
    
    TLorentzVector v2;

    v.SetPtEtaPhiM(m_jet_0_pt->EvalInstance(),m_jet_0_eta->EvalInstance(),m_jet_0_phi->EvalInstance(),m_jet_0_m->EvalInstance());
    v2.SetPtEtaPhiM(m_jet_1_pt->EvalInstance(),m_jet_1_eta->EvalInstance(),m_jet_1_phi->EvalInstance(),m_jet_1_m->EvalInstance());
    p1[0] = v.E();
    p1[1] = v.Px();
    p1[2] = v.Py();
    p1[3] = v.Pz();
    pjets.push_back(p1);
    TLorentzVector h;
    h.SetPtEtaPhiM(m_h_pt->EvalInstance(),m_h_eta->EvalInstance(),m_h_phi->EvalInstance(),m_h_m->EvalInstance());
    TLorentzVector fO = (h + v + v2);
    x1 = ((fO).M()/ecm)*TMath::Exp(fO.Rapidity());
    x2 = ((fO).M()/ecm)*TMath::Exp(fO.Rapidity()*-1);


    p2[0] = v2.E();
    p2[1] = v2.Px();
    p2[2] = v2.Py();
    p2[3] = v2.Pz();
    pjets.push_back(p2);
  }


  v.SetPtEtaPhiM(m_h_pt->EvalInstance(),m_h_eta->EvalInstance(),m_h_phi->EvalInstance(),m_h_m->EvalInstance());
  double phiggs[] = {v.E(),v.Px(),v.Py(),v.Pz()};     
 


  //
  //***************

  DEBUGclass("getting value for variable %s!",m_var.Data());
  double retval = -999;
  int entry = -1;
  if (m_var.Contains("1") || m_var.Contains("_lin"))
    entry = 0;
  else if (m_var.Contains("2") || m_var.Contains("_quad"))
    entry = 1;
  if (m_tags->getTagBoolDefault("isTruth") == kFALSE && x1<0.0000001)
  {
    ERRORclass("non-physical value for (reco) x1. Returning -1234!");
    return -1234;
  }
  if (m_var.Contains("OptimalObservable"))
  {
    DEBUGclass("Inputs for OO calculation: ecm=%f, mH=%f, x1=%f, x2=%f, Q=%f",ecm,mH,x1,x2,Q);
    DEBUGclass("Inputs for OO calculation (j1): %f, %f, %f, %f",pjets[0][0],pjets[0][1],pjets[0][2],pjets[0][3]);
    DEBUGclass("Inputs for OO calculation (j2): %f, %f, %f, %f",pjets[1][0],pjets[1][1],pjets[1][2],pjets[1][3]);
    DEBUGclass("Inputs for OO calculation (H): %f, %f, %f, %f",phiggs[0],phiggs[1],phiggs[2],phiggs[3]);
    retval = m_ooE->getOptObs(entry, eventNumber, ecm, mH ,x1,x2,Q,pjets[0],pjets[1],phiggs);
  }
  else if (m_var.Contains("WeightDTilde"))
  {
    DEBUGclass("Inputs for weights calculation: ecm=%f, mH=%f, npafin=%i, fli[0]=%i, fli[1]=%i, flo[o]=%i, flo[1]=%i, flo[2]=%i, x1=%f, x2=%f",ecm,mH,npafin,flavourIn[0],flavourIn[1],flavourOut[0],flavourOut[1],flavourOut[2],x1,x2);
    DEBUGclass("Inputs for weights calculation (j1): %f, %f, %f, %f",pjets[0][0],pjets[0][1],pjets[0][2],pjets[0][3]);
    DEBUGclass("Inputs for weights calculation (j2): %f, %f, %f, %f",pjets[1][0],pjets[1][1],pjets[1][2],pjets[1][3]);
    DEBUGclass("Inputs for weights calculation (H): %f, %f, %f, %f",phiggs[0],phiggs[1],phiggs[2],phiggs[3]);
    retval = m_ooE->getWeightsDtilde(entry, eventNumber, ecm, mH , npafin,flavourIn[0],flavourIn[1],flavourOut[0],flavourOut[1],flavourOut[3],x1,x2,pjets[0],pjets[1],pjets[2],phiggs);
    //ERRORclass("%i",npafin);
  }
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
  retval->Add(new TObjString("event_number"));

  if (m_tags->getTagBoolDefault("isTruth",false))
  {
    retval->Add(new TObjString("truth_opt_obs_parton_0_pt"));
    retval->Add(new TObjString("truth_opt_obs_parton_0_eta"));
    retval->Add(new TObjString("truth_opt_obs_parton_0_phi"));
    retval->Add(new TObjString("truth_opt_obs_parton_0_m"));
    retval->Add(new TObjString("truth_opt_obs_parton_0_pdgId"));

    retval->Add(new TObjString("truth_opt_obs_parton_1_pt"));
    retval->Add(new TObjString("truth_opt_obs_parton_1_eta"));
    retval->Add(new TObjString("truth_opt_obs_parton_1_phi"));
    retval->Add(new TObjString("truth_opt_obs_parton_1_m"));
    retval->Add(new TObjString("truth_opt_obs_parton_1_pdgId"));

    retval->Add(new TObjString("truth_opt_obs_parton_2_pt"));
    retval->Add(new TObjString("truth_opt_obs_parton_2_eta"));
    retval->Add(new TObjString("truth_opt_obs_parton_2_phi"));
    retval->Add(new TObjString("truth_opt_obs_parton_2_m"));
    retval->Add(new TObjString("truth_opt_obs_parton_2_pdgId"));

    retval->Add(new TObjString("truth_opt_obs_higgs_pt"));
    retval->Add(new TObjString("truth_opt_obs_higgs_eta"));
    retval->Add(new TObjString("truth_opt_obs_higgs_phi"));
    retval->Add(new TObjString("truth_opt_obs_higgs_m"));

    retval->Add(new TObjString("truth_event_info_Bjorken_x1"));
    retval->Add(new TObjString("truth_event_info_Bjorken_x2"));

    retval->Add(new TObjString("truth_event_info_pdgId1"));
    retval->Add(new TObjString("truth_event_info_pdgId2"));

  }

  else
  {
    retval->Add(new TObjString("jet_0_pt"));
    retval->Add(new TObjString("jet_0_eta"));
    retval->Add(new TObjString("jet_0_phi"));
    retval->Add(new TObjString("jet_0_m"));

    retval->Add(new TObjString("jet_1_pt"));
    retval->Add(new TObjString("jet_1_eta"));
    retval->Add(new TObjString("jet_1_phi"));
    retval->Add(new TObjString("jet_1_m"));

    retval->Add(new TObjString("jet_2_pt"));
    retval->Add(new TObjString("jet_2_eta"));
    retval->Add(new TObjString("jet_2_phi"));
    retval->Add(new TObjString("jet_2_m"));

    retval->Add(new TObjString("lephad_mmc_maxw_pt"));
    retval->Add(new TObjString("lephad_mmc_maxw_eta"));
    retval->Add(new TObjString("lephad_mmc_maxw_phi"));
    retval->Add(new TObjString("lephad_mmc_maxw_m"));
  }
  //.
  //.
  //.
  return retval;
}

#endif
