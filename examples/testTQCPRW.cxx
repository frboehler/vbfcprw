#include "HLeptonsCPRW/TQOptObsObservable.h"

int main(int argc, char* argv[])
{
  TQOptObsObservable *oo1 = new TQOptObsObservable("OptimalObservable1");
  TQOptObsObservable *oo2 = new TQOptObsObservable("OptimalObservable2");
  TQOptObsObservable *wdtlin = new TQOptObsObservable("WeightDTilde_lin");
  TQOptObsObservable *wdtquad = new TQOptObsObservable("WeightDTilde_quad");
  TQOptObsObservable *rw0 = new TQOptObsObservable("Reweight",0);
  TQOptObsObservable *rw01 = new TQOptObsObservable("Reweight",0.1);
  TQObservable::addObservable(oo1,"OO1");
  TQObservable::addObservable(oo2,"OO2");
  TQObservable::addObservable(wdtlin,"weightDTilde_lin");
  TQObservable::addObservable(wdtquad,"weightDTilde_quad");
  TQObservable::addObservable(rw0,"weightDTilde0");
  TQObservable::addObservable(rw01,"weightDTilde01");
  TQObservable::printObservables();
  return 1;
}
