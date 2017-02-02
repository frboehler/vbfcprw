#include "HLeptonsCPRW/TQOptObsObservable.h"

int main(int argc, char* argv[])
{
  OptObsEventStore *ooE = new OptObsEventStore();
  TQOptObsObservable *oo1 = new TQOptObsObservable(ooE,"OptimalObservable1");
  TQOptObsObservable *oo2 = new TQOptObsObservable(ooE,"OptimalObservable2");
  TQOptObsObservable *wdtlin = new TQOptObsObservable(ooE,"WeightDTildeLin");
  TQOptObsObservable *wdtquad = new TQOptObsObservable(ooE,"WeightDTildeQuad");
  TQOptObsObservable *rw = new TQOptObsObservable(ooE,"Reweight");
  TQObservable::addObservable(oo1,"OO1");
  TQObservable::addObservable(oo2,"OO2");
  TQObservable::addObservable(wdtlin,"weightDTilde_lin");
  TQObservable::addObservable(wdtquad,"weightDTilde_quad");
  TQObservable::addObservable(rw,"weightDTilde");
  TQObservable::printObservables();
  return 1;
}
