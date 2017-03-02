#include "HLeptonsCPRW/TQOptObsObservable.h"
#ifdef ROOTCORE_PACKAGE_QFramework
ClassImp(TQOptObsObservable)
#include "QFramework/TQUtils.h"

//#define _DEBUG_
#include "QFramework/TQLibrary.h"
#include "TSystem.h"
#include "TLorentzVector.h"


//______________________________________________________________________________________________

bool TQOptObsObservable::init(TString variable, double dtilde)
{
  m_ooE = new OptObsEventStore();
  m_ooE->initPDFSet(m_tags->getTagStringDefault("PDFset","CT10").Data(),0,91.2);

  return true;
}
TQOptObsObservable::TQOptObsObservable(TString variable, TQTaggable *tags, double dtilde) :
TQTreeObservable()
{
  // default constructor
  m_tags = tags;
  m_var = variable;
  m_dtilde = dtilde;
}
TQOptObsObservable::TQOptObsObservable(TString variable, double dtilde) :
TQTreeObservable()
{
  // default constructor
  m_tags = new TQTaggable();
  m_var = variable;
  m_dtilde = dtilde;
}

TQOptObsObservable::TQOptObsObservable(TString variable, TString tags, double dtilde) :
TQTreeObservable()
{
  // default constructor
  m_tags = new TQTaggable();
  m_tags->importTags(tags);
  m_var = variable;
  m_dtilde = dtilde;
}


//______________________________________________________________________________________________

bool TQOptObsObservable::initializeSelf(){
  // initialize the formula of this observable
  DEBUGclass("initializing ...");

  init(m_var,m_dtilde);

  m_EventNumber = new TTreeFormula("event_number","event_number",fTree);

  if (m_tags->getTagBoolDefault("isReco",false) == false)
  {
    m_jet_0_pz =    new TTreeFormula("truth_reweight_info_parton_0_pz",    "truth_reweight_info_parton_0_pz", fTree);
    m_jet_0_pdgId = new TTreeFormula("truth_reweight_info_parton_0_pdgId", "truth_reweight_info_parton_0_pdgId",  fTree);

    m_jet_1_pz =    new TTreeFormula("truth_reweight_info_parton_1_pz",    "truth_reweight_info_parton_1_pz", fTree);
    m_jet_1_pdgId = new TTreeFormula("truth_reweight_info_parton_1_pdgId", "truth_reweight_info_parton_1_pdgId",  fTree);

    m_jet_2_pt =    new TTreeFormula("truth_reweight_info_parton_2_pt",    "truth_reweight_info_parton_2_pt", fTree);
    m_jet_2_eta =   new TTreeFormula("truth_reweight_info_parton_2_eta",   "truth_reweight_info_parton_2_eta",fTree);
    m_jet_2_phi =   new TTreeFormula("truth_reweight_info_parton_2_phi",   "truth_reweight_info_parton_2_phi",fTree);
    m_jet_2_m =     new TTreeFormula("truth_reweight_info_parton_2_m",     "truth_reweight_info_parton_2_m",  fTree);
    m_jet_2_pdgId = new TTreeFormula("truth_reweight_info_parton_2_pdgId", "truth_reweight_info_parton_2_pdgId",  fTree);

    m_jet_3_pt =    new TTreeFormula("truth_reweight_info_parton_3_pt",    "truth_reweight_info_parton_3_pt", fTree);
    m_jet_3_eta =   new TTreeFormula("truth_reweight_info_parton_3_eta",   "truth_reweight_info_parton_3_eta",fTree);
    m_jet_3_phi =   new TTreeFormula("truth_reweight_info_parton_3_phi",   "truth_reweight_info_parton_3_phi",fTree);
    m_jet_3_m =     new TTreeFormula("truth_reweight_info_parton_3_m",     "truth_reweight_info_parton_3_m",  fTree);
    m_jet_3_pdgId = new TTreeFormula("truth_reweight_info_parton_3_pdgId", "truth_reweight_info_parton_3_pdgId",  fTree);

    m_jet_4_pt =    new TTreeFormula("truth_reweight_info_parton_4_pt",    "truth_reweight_info_parton_4_pt", fTree);
    m_jet_4_eta =   new TTreeFormula("truth_reweight_info_parton_4_eta",   "truth_reweight_info_parton_4_eta",fTree);
    m_jet_4_phi =   new TTreeFormula("truth_reweight_info_parton_4_phi",   "truth_reweight_info_parton_4_phi",fTree);
    m_jet_4_m =     new TTreeFormula("truth_reweight_info_parton_4_m",     "truth_reweight_info_parton_4_m",  fTree);
    m_jet_4_pdgId = new TTreeFormula("truth_reweight_info_parton_4_pdgId", "truth_reweight_info_parton_4_pdgId",  fTree);

    m_h_pt =    new TTreeFormula("truth_reweight_info_higgs_pt",    "truth_reweight_info_higgs_pt", fTree);
    m_h_eta =   new TTreeFormula("truth_reweight_info_higgs_eta",   "truth_reweight_info_higgs_eta",fTree);
    m_h_phi =   new TTreeFormula("truth_reweight_info_higgs_phi",   "truth_reweight_info_higgs_phi",fTree);
    m_h_m =     new TTreeFormula("truth_reweight_info_higgs_m",     "truth_reweight_info_higgs_m",  fTree);
  }

  else
  {
    m_jet_2_pt =  new TTreeFormula("jet_0_pt", "jet_0_pt", fTree);
    m_jet_2_eta = new TTreeFormula("jet_0_eta","jet_0_eta",fTree);
    m_jet_2_phi = new TTreeFormula("jet_0_phi","jet_0_phi",fTree);
    m_jet_2_m =   new TTreeFormula("jet_0_m",  "jet_0_m",  fTree);

    m_jet_3_pt =  new TTreeFormula("jet_1_pt", "jet_1_pt", fTree);
    m_jet_3_eta = new TTreeFormula("jet_1_eta","jet_1_eta",fTree);
    m_jet_3_phi = new TTreeFormula("jet_1_phi","jet_1_phi",fTree);
    m_jet_3_m =   new TTreeFormula("jet_1_m",  "jet_1_m",  fTree);

    m_jet_4_pt =  new TTreeFormula("jet_2_pt", "jet_2_pt", fTree);
    m_jet_4_eta = new TTreeFormula("jet_2_eta","jet_2_eta",fTree);
    m_jet_4_phi = new TTreeFormula("jet_2_phi","jet_2_phi",fTree);
    m_jet_4_m =   new TTreeFormula("jet_2_m",  "jet_2_m",  fTree);

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
  DEBUGclass("Finalising...");
  delete m_ooE;
  delete m_EventNumber;


  delete m_jet_2_pt;
  delete m_jet_2_eta;
  delete m_jet_2_phi;
  delete m_jet_2_m;

  delete m_jet_3_pt;
  delete m_jet_3_eta;
  delete m_jet_3_phi;
  delete m_jet_3_m;

  delete m_jet_4_pt;
  delete m_jet_4_eta;
  delete m_jet_4_phi;
  delete m_jet_4_m;

  delete m_h_pt;
  delete m_h_eta;
  delete m_h_phi;
  delete m_h_m;

  if (m_tags->getTagBoolDefault("isReco",false) == false)
  {
    delete m_jet_0_pdgId;
    delete m_jet_1_pdgId;
    delete m_jet_2_pdgId;
    delete m_jet_3_pdgId;
    delete m_jet_4_pdgId;
    delete m_jet_0_pz;
    delete m_jet_1_pz;
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

  double x1,x2;

  double ptCutoff = m_tags->getTagDoubleDefault("pTCutoff",0.0);

  // find the two non-gluon final state partons
  std::vector<double*> pjets;
  std::vector< std::pair<int,float> > jetList;
  double p0[4],p1[4],p2[4];
  TLorentzVector v0,v1,v2,h;
  std::vector<int> flavourIn, flavourOut;
  std::vector< std::pair<TLorentzVector,int> >jets;

  h.SetPtEtaPhiM(m_h_pt->EvalInstance(),m_h_eta->EvalInstance(),m_h_phi->EvalInstance(),m_h_m->EvalInstance());

  v0.SetPtEtaPhiM(m_jet_2_pt->EvalInstance(),m_jet_2_eta->EvalInstance(),m_jet_2_phi->EvalInstance(),m_jet_2_m->EvalInstance());
  jetList.push_back(std::make_pair(0,v0.Eta()));
  
  v1.SetPtEtaPhiM(m_jet_3_pt->EvalInstance(),m_jet_3_eta->EvalInstance(),m_jet_3_phi->EvalInstance(),m_jet_3_m->EvalInstance());
  jetList.push_back(std::make_pair(1,v1.Eta()));
  
  v2.SetPtEtaPhiM(m_jet_4_pt->EvalInstance(),m_jet_4_eta->EvalInstance(),m_jet_4_phi->EvalInstance(),m_jet_4_m->EvalInstance());
  if (m_jet_4_pt->EvalInstance() > ptCutoff)
  {
    jetList.push_back(std::make_pair(2,v2.Eta()));
  }
  std::sort(jetList.begin(),jetList.end(), sortObj);

  if (m_tags->getTagBoolDefault("isReco",false) == false)
  {
    DEBUGclass("Running truth observable");
    x1 = TMath::Abs(m_jet_0_pz->EvalInstance()/(ecm*0.5));           
    x2 = TMath::Abs(m_jet_1_pz->EvalInstance()/(ecm*0.5));           
    flavourIn.push_back((m_jet_0_pdgId->EvalInstance() == 21) ? 0 : m_jet_0_pdgId->EvalInstance());
    flavourIn.push_back((m_jet_1_pdgId->EvalInstance() == 21) ? 0 : m_jet_1_pdgId->EvalInstance());

    jets.push_back(std::make_pair(v0, (m_jet_2_pdgId->EvalInstance() == 21) ? 0 : m_jet_2_pdgId->EvalInstance()));
    jets.push_back(std::make_pair(v1, (m_jet_3_pdgId->EvalInstance() == 21) ? 0 : m_jet_3_pdgId->EvalInstance()));
    if (m_jet_4_pt->EvalInstance() > ptCutoff)
    {
      jets.push_back(std::make_pair(v2, (m_jet_4_pdgId->EvalInstance() == 21) ? 0 : m_jet_4_pdgId->EvalInstance()));
    }



    for (unsigned int i=0;i<jetList.size();++i)
      flavourOut.push_back(jets.at(jetList[i].first).second);

    std::vector<int>::iterator it = std::find(flavourOut.begin(),flavourOut.end(),0);
    int nG = std::count(flavourOut.begin(),flavourOut.end(),0);
    if (nG > 1)
      ERRORclass("Found %i gluons in the final state. check input!",nG);

    if (m_var.Contains("hqqq"))
    {
      if (jets.size() == 3)
        return (h+v0+v1+v2).Pt();
      else
        return (h+v0+v1).Pt();
    }

    if (m_var.Contains("npafin"))
      return jets.size();

    if (m_tags->getTagBoolDefault("isDebugRun",false) && nG == 0 && jets.size() == 3)
    {
      INFOclass("Event %i",eventNumber);
      INFOclass("Incoming partons: (x1=%f, f1=%i; x2=%f, f2=%i",x1,flavourIn.at(0),x2,flavourIn.at(1));
      INFOclass("Pt of the hqq (0,1)-system: %f",(h+v0+v1).Pt());
      INFOclass("Pt of the hqq (0,2)-system: %f",(h+v0+v2).Pt());
      INFOclass("Pt of the hqq (1,2)-system: %f",(h+v2+v1).Pt());
      INFOclass("Pt of the hqqq-system: %f",(h+v0+v1+v2).Pt());
      for (unsigned int i=0; i<jets.size(); ++i)
      {
        INFOclass("kinematics of jet %i: Pt = %f, eta=%g, phi=%f, flavour=%i",i,jets.at(i).first.Pt(),jets.at(i).first.Eta(),jets.at(i).first.Phi(),jets.at(i).second);
      }
      INFOclass("dR (0,1) = %f",jets.at(0).first.DeltaR(jets.at(1).first));
      if (jets.size() == 3)
      {
        INFOclass("dR (0,2) = %f",jets.at(0).first.DeltaR(jets.at(2).first));
        INFOclass("dR (1,2) = %f",jets.at(1).first.DeltaR(jets.at(2).first));
      }
      INFOclass("========");
    }
    if (it != flavourOut.end())
    {
      flavourOut.erase(it);
      flavourOut.push_back(0);
      int index = it-flavourOut.begin();
      std::pair<int,float> g = jetList.at(index);
      jetList.erase(jetList.begin()+index);
      jetList.push_back(g);
    }
  }
  else
  {
    DEBUGclass("Running reco observable");

    TLorentzVector fO;

    fO = (h + v0 + v1);

    x1 = ((fO).M()/ecm)*TMath::Exp(fO.Rapidity());
    x2 = ((fO).M()/ecm)*TMath::Exp(fO.Rapidity()*-1);

    jets.push_back(std::make_pair(v0, 0));
    jets.push_back(std::make_pair(v1, 0));
    if (m_jet_4_pt->EvalInstance() > 0.0)
    {
      jets.push_back(std::make_pair(v2, 0));
    }
  }


    p0[0] = jets.at(jetList[0].first).first.E();
    p0[1] = jets.at(jetList[0].first).first.Px();
    p0[2] = jets.at(jetList[0].first).first.Py();
    p0[3] = jets.at(jetList[0].first).first.Pz();
    p1[0] = jets.at(jetList[1].first).first.E();
    p1[1] = jets.at(jetList[1].first).first.Px();
    p1[2] = jets.at(jetList[1].first).first.Py();
    p1[3] = jets.at(jetList[1].first).first.Pz();
    pjets.push_back(p0);
    pjets.push_back(p1);
    if (jetList.size() == 3)
    {
      p2[0] = jets.at(jetList[2].first).first.E();
      p2[1] = jets.at(jetList[2].first).first.Px();
      p2[2] = jets.at(jetList[2].first).first.Py();
      p2[3] = jets.at(jetList[2].first).first.Pz();
      pjets.push_back(p2);
    }
    else
    {
      p2[0] = 0;
      p2[1] = 0;
      p2[2] = 0;
      p2[3] = 0;
      pjets.push_back(p2);
    }




  v0.SetPtEtaPhiM(m_h_pt->EvalInstance(),m_h_eta->EvalInstance(),m_h_phi->EvalInstance(),m_h_m->EvalInstance());
  double phiggs[] = {v0.E(),v0.Px(),v0.Py(),v0.Pz()};     

  unsigned int npafin = jetList.size();
 


  //
  //***************

  DEBUGclass("getting value for variable %s!",m_var.Data());
  double retval = -999;
  int entry = -1;
  if (m_var.Contains("1") || m_var.Contains("_lin"))
    entry = 0;
  else if (m_var.Contains("2") || m_var.Contains("_quad"))
    entry = 1;
  if (m_tags->getTagBoolDefault("isReco",false) && x1<0.0000001)
  {
    ERRORclass("non-physical value for (reco) x1=%f when trying to calculate variabe %s. Returning -1234!",x1,m_var.Data());
    return -1234;
  }
  if (m_var.Contains("OptimalObservable"))
  {
    DEBUGclass("Inputs for OO calculation: ecm=%f, mH=%f, x1=%f, x2=%f, Q=%f",ecm,mH,x1,x2,Q);
    DEBUGclass("Inputs for OO calculation (j1): %f, %f, %f, %f",pjets[0][0],pjets[0][1],pjets[0][2],pjets[0][3]);
    DEBUGclass("Inputs for OO calculation (j2): %f, %f, %f, %f",pjets[1][0],pjets[1][1],pjets[1][2],pjets[1][3]);
    DEBUGclass("Inputs for OO calculation (H): %f, %f, %f, %f",phiggs[0],phiggs[1],phiggs[2],phiggs[3]);
    if (pjets[0][0] > 0. && pjets[1][0] > 0. && phiggs[0] > 0.)
      {
	retval = m_ooE->getOptObs(entry, eventNumber, ecm, mH ,x1,x2,Q,pjets[0],pjets[1],phiggs);
      }
  }
  else if (m_var.Contains("WeightDTilde"))
  {
    DEBUGclass("Inputs for weights calculation: ecm=%f, mH=%f, npafin=%i, fli[0]=%i, fli[1]=%i, flo[0]=%i, flo[1]=%i, flo[2]=%i, x1=%f, x2=%f",ecm,mH,npafin,flavourIn[0],flavourIn[1],flavourOut[0],flavourOut[1],flavourOut[2],x1,x2);
    DEBUGclass("Inputs for weights calculation (j1): %f, %f, %f, %f",pjets[0][0],pjets[0][1],pjets[0][2],pjets[0][3]);
    DEBUGclass("Inputs for weights calculation (j2): %f, %f, %f, %f",pjets[1][0],pjets[1][1],pjets[1][2],pjets[1][3]);
    DEBUGclass("Inputs for weights calculation (H): %f, %f, %f, %f",phiggs[0],phiggs[1],phiggs[2],phiggs[3]);
    retval = m_ooE->getWeightsDtilde(entry, eventNumber, ecm, mH , npafin,flavourIn[0],flavourIn[1],flavourOut[0],flavourOut[1],flavourOut[2],x1,x2,pjets[0],pjets[1],pjets[2],phiggs);
    if (TMath::Abs(retval) < 1e-8)
    {

      ERRORclass("Number of gluons: %i",std::count(flavourOut.begin(),flavourOut.end(),0));
      ERRORclass("Inputs for weights calculation: ecm=%f, mH=%f, npafin=%i, fli[0]=%i, fli[1]=%i, flo[0]=%i, flo[1]=%i, flo[2]=%i, x1=%f, x2=%f",ecm,mH,npafin,flavourIn[0],flavourIn[1],flavourOut[0],flavourOut[1],flavourOut[2],x1,x2);
      ERRORclass("Inputs for weights calculation (j1): %f, %f, %f, %f",pjets[0][0],pjets[0][1],pjets[0][2],pjets[0][3]);
      ERRORclass("Inputs for weights calculation (j2): %f, %f, %f, %f",pjets[1][0],pjets[1][1],pjets[1][2],pjets[1][3]);
      ERRORclass("Inputs for weights calculation (j3): %f, %f, %f, %f",pjets[2][0],pjets[2][1],pjets[2][2],pjets[2][3]);
      ERRORclass("Inputs for weights calculation (H): %f, %f, %f, %f",phiggs[0],phiggs[1],phiggs[2],phiggs[3]);
    }
  }
  else if (m_var.Contains("Reweight"))
  {
    double rsmin=1, lambdahvvin=-1;
    int ModelSwitch = 1;

    retval = m_ooE->getReweight(ecm, mH, ModelSwitch , 
        rsmin, 0, 0, m_dtilde, m_dtilde, lambdahvvin,
        0,0,0,         
        0,0,0,        
        0,0,0,       
        0,0,0,      
        npafin,flavourIn[0],flavourIn[1],flavourOut[0],flavourOut[1],flavourOut[2],
        x1,x2,pjets[0],pjets[1],pjets[2],phiggs);
  }
  DEBUGclass("Returning %f for variable %s in Event %i",retval,m_var.Data(),eventNumber);
  return retval;
}



//______________________________________________________________________________________________

TObjArray* TQOptObsObservable::getBranchNames() const {
  // retrieve the list of branch names 
  // ownership of the list belongs to the caller of the function
  DEBUGclass("getting branch names!");
  TObjArray* retval = new TObjArray();
  retval->Add(new TObjString("event_number"));

  if (m_tags->getTagBoolDefault("isReco",false) == false)
  {
    retval->Add(new TObjString("truth_reweight_info_parton_0_pz"));
    retval->Add(new TObjString("truth_reweight_info_parton_0_pdgId"));

    retval->Add(new TObjString("truth_reweight_info_parton_1_pz"));
    retval->Add(new TObjString("truth_reweight_info_parton_1_pdgId"));

    retval->Add(new TObjString("truth_reweight_info_parton_2_pt"));
    retval->Add(new TObjString("truth_reweight_info_parton_2_eta"));
    retval->Add(new TObjString("truth_reweight_info_parton_2_phi"));
    retval->Add(new TObjString("truth_reweight_info_parton_2_m"));
    retval->Add(new TObjString("truth_reweight_info_parton_2_pdgId"));

    retval->Add(new TObjString("truth_reweight_info_parton_3_pt"));
    retval->Add(new TObjString("truth_reweight_info_parton_3_eta"));
    retval->Add(new TObjString("truth_reweight_info_parton_3_phi"));
    retval->Add(new TObjString("truth_reweight_info_parton_3_m"));
    retval->Add(new TObjString("truth_reweight_info_parton_3_pdgId"));

    retval->Add(new TObjString("truth_reweight_info_parton_4_pt"));
    retval->Add(new TObjString("truth_reweight_info_parton_4_eta"));
    retval->Add(new TObjString("truth_reweight_info_parton_4_phi"));
    retval->Add(new TObjString("truth_reweight_info_parton_4_m"));
    retval->Add(new TObjString("truth_reweight_info_parton_4_pdgId"));

    retval->Add(new TObjString("truth_reweight_info_higgs_pt"));
    retval->Add(new TObjString("truth_reweight_info_higgs_eta"));
    retval->Add(new TObjString("truth_reweight_info_higgs_phi"));
    retval->Add(new TObjString("truth_reweight_info_higgs_m"));
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
