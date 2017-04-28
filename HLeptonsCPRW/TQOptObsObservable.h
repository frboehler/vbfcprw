//this file looks like plain C, but it's actually -*- c++ -*-
#include "RootCore/Packages.h"
#ifdef ROOTCORE_PACKAGE_QFramework
#ifndef __TQOptObsObservable__
#define __TQOptObsObservable__


#include "TTreeFormula.h"
#include "HLeptonsCPRW/OptObsEventStore.h"
#include "QFramework/TQTreeObservable.h"
#include "QFramework/TQTaggable.h"
#ifdef ROOTCORE_PACKAGE_Htt2016_leplep
#include "Htt2016_leplep/EventSelection_leplep_fake.h"
#include "Htt2016_leplep/EventSelection_leplep_default.h"
#endif

class TQOptObsObservable : public TQTreeObservable {

protected:

  bool init(TString var, double dt);
  virtual bool initializeSelf() override;
  virtual bool finalizeSelf() override;
  double m_dtilde;
  TString m_var;
  TQTaggable *m_tags;
  TTreeFormula *m_EventNumber;
  TTreeFormula *m_jet_0_pz;
  TTreeFormula *m_jet_0_pdgId;
  TTreeFormula *m_jet_1_pz;
  TTreeFormula *m_jet_1_pdgId;
  TTreeFormula *m_jet_2_pt;
  TTreeFormula *m_jet_2_eta;
  TTreeFormula *m_jet_2_phi;
  TTreeFormula *m_jet_2_m;
  TTreeFormula *m_jet_2_pdgId;
  TTreeFormula *m_jet_3_pt;
  TTreeFormula *m_jet_3_eta;
  TTreeFormula *m_jet_3_phi;
  TTreeFormula *m_jet_3_m;
  TTreeFormula *m_jet_3_pdgId;
  TTreeFormula *m_jet_4_pt;
  TTreeFormula *m_jet_4_eta;
  TTreeFormula *m_jet_4_phi;
  TTreeFormula *m_jet_4_m;
  TTreeFormula *m_jet_4_pdgId;
  TTreeFormula *m_h_pt;
  TTreeFormula *m_h_eta;
  TTreeFormula *m_h_phi;
  TTreeFormula *m_h_m;

  TTreeFormula *m_jets_pt_vec;
  TTreeFormula *m_jets_eta_vec;
  TTreeFormula *m_jets_phi_vec;
  TTreeFormula *m_jets_m_vec;
  TTreeFormula *m_h_pt_vec;
  TTreeFormula *m_h_eta_vec;
  TTreeFormula *m_h_phi_vec;
  TTreeFormula *m_h_m_vec;

#ifdef ROOTCORE_PACKAGE_Htt2016_leplep
  EventSelection_leplep_fake * EVS_fake;
  EventSelection_leplep_default * EVS_def;
#endif

  OptObsEventStore *m_ooE = 0;

struct sortClass {
  bool operator() (std::pair<int,float> a, std::pair<int,float> b){
    return a.second > b.second; }
} sortObj;

public:

  bool isInitialized;

  TQOptObsObservable(TString variable, double dtilde = 0);
  TQOptObsObservable(TString variable, TQTaggable *tags, double dtilde = 0);
  TQOptObsObservable(TString variable, TString tags, double dtilde = 0);

  virtual double getValue() const override;

  virtual TObjArray* getBranchNames() const override;

  virtual ~TQOptObsObservable();
 
  ClassDefOverride(TQOptObsObservable, 0);


};
#endif
#endif
