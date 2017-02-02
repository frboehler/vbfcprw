//this file looks like plain C, but it's actually -*- c++ -*-
#ifndef __TQOptObsObservable__
#define __TQOptObsObservable__

#include "TTreeFormula.h"
#include "QFramework/TQTreeObservable.h"
#include "HLeptonsCPRW/OptObsEventStore.h"

class TQOptObsObservable : public TQTreeObservable {

protected:

  virtual bool initializeSelf() override;
  virtual bool finalizeSelf() override;
  TString m_var;
  TTreeFormula *m_EventNumber;
  OptObsEventStore *m_ooE = 0;

public:

  bool isInitialized;

  TQOptObsObservable(OptObsEventStore *ooe, TString variable, double dtilde = 0);

  virtual double getValue() const override;

  virtual TObjArray* getBranchNames() const override;

  virtual ~TQOptObsObservable();
 
  ClassDefOverride(TQOptObsObservable, 0);


};

#endif
