#! /bin/env python2

def main():
    from HLeptonsCPRW import TQOptObsObservable
    from QFramework import TQObservable
    oo1 = TQOptObsObservable("OptimalObservable1");
    oo2 = TQOptObsObservable("OptimalObservable2");
    wdtlin = TQOptObsObservable("WeightDTilde_lin");
    wdtquad = TQOptObsObservable("WeightDTilde_quad");
    rw0 = TQOptObsObservable("Reweight",0);
    rw01 = TQOptObsObservable("Reweight",0.1);
    TQObservable.addObservable(oo1,"OO1");
    TQObservable.addObservable(oo2,"OO2");
    TQObservable.addObservable(wdtlin,"weightDTilde_lin");
    TQObservable.addObservable(wdtquad,"weightDTilde_quad");
    TQObservable.addObservable(rw0,"weightDTilde0");
    TQObservable.addObservable(rw01,"weightDTilde01");
    TQObservable.printObservables();
    return 1;

if __name__ == '__main__':
    main()
