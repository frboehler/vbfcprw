//this file looks like plain C, but it's actually -*- c++ -*-
#include "RootCore/Packages.h"
#ifdef ROOTCORE_PACKAGE_QFramework
#ifndef __TQOptObsObservable__
#define __TQOptObsObservable__


#include "TTreeFormula.h"
#include "HLeptonsCPRW/OptObsEventStore.h"
#include "QFramework/TQTreeObservable.h"
#include "QFramework/TQTaggable.h"

class TQOptObsObservable : public TQTreeObservable {

protected:

  virtual bool initializeSelf() override;
  virtual bool finalizeSelf() override;
  TString m_var;
  TQTaggable *m_tags;
  TTreeFormula *m_EventNumber;
  TTreeFormula *m_jet_0_pt;
  TTreeFormula *m_jet_0_eta;
  TTreeFormula *m_jet_0_phi;
  TTreeFormula *m_jet_0_m;
  TTreeFormula *m_jet_0_pdgId;
  TTreeFormula *m_jet_1_pt;
  TTreeFormula *m_jet_1_eta;
  TTreeFormula *m_jet_1_phi;
  TTreeFormula *m_jet_1_m;
  TTreeFormula *m_jet_1_pdgId;
  TTreeFormula *m_jet_2_pt;
  TTreeFormula *m_jet_2_eta;
  TTreeFormula *m_jet_2_phi;
  TTreeFormula *m_jet_2_m;
  TTreeFormula *m_jet_2_pdgId;
  TTreeFormula *m_h_pt;
  TTreeFormula *m_h_eta;
  TTreeFormula *m_h_phi;
  TTreeFormula *m_h_m;
  TTreeFormula *m_x1;
  TTreeFormula *m_x2;
  TTreeFormula *m_pdgIn1;
  TTreeFormula *m_pdgIn2;
  OptObsEventStore *m_ooE = 0;

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
