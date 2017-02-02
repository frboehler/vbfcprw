#include "HLeptonsCPRW/TQOptObsObservable.h"

int main(int argc, char* argv[])
{
  OptObsEventStore *ooE = new OptObsEventStore();
  OptObsEventStore *ooE2 = new OptObsEventStore();
  TQOptObsObservable *oo1 = new TQOptObsObservable(ooE,"OptimalObservable1");
  TQOptObsObservable *oo2 = new TQOptObsObservable(ooE,"OptimalObservable2");
  TQOptObsObservable *wdtlin = new TQOptObsObservable(ooE,"WeightDTilde_lin");
  TQOptObsObservable *wdtquad = new TQOptObsObservable(ooE,"WeightDTilde_quad");
  TQOptObsObservable *rw0 = new TQOptObsObservable(ooE,"Reweight",0);
  TQOptObsObservable *rw01 = new TQOptObsObservable(ooE2,"Reweight",0.1);
  TQObservable::addObservable(oo1,"OO1");
  TQObservable::addObservable(oo2,"OO2");
  TQObservable::addObservable(wdtlin,"weightDTilde_lin");
  TQObservable::addObservable(wdtquad,"weightDTilde_quad");
  TQObservable::addObservable(rw0,"weightDTilde0");
  TQObservable::addObservable(rw01,"weightDTilde01");
  TQObservable::printObservables();
  delete ooE;
  delete ooE2;
  return 1;
}
