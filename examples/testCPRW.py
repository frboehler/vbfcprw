#! /bin/env python2

def main(useEventStore,silent,useNewEvent,iterations):
    from HLeptonsCPRW import OptObsEventStore
    import ROOT
    import array
    pjet1 = array.array('d', [438.019730, -24.873165, -94.306022, 427.023386])               # E,px,py,pz of nth final state parton
    pjet2  = array.array('d',[656.475632, -55.150478, 66.466227, -650.769506])
    pjet3  = array.array('d',[51.082110, 25.871174, 3.770224, 43.884504])
    phiggs = array.array('d',[177.080599, 54.152473, 24.069573, -110.547404])            # E,px,py,pz of Higgs boson make sure that four-momentum conservation holds 
    Q = 84000;

    #std::pair<double,double> oo, weights;
    eventNumber = 1234;
    ecm = 13000;                           #proton-proton center-of mass energy in GeV
    mH = 124.999901;                       #mass of Higgs boson in Gev
    npafin = 3;                            #number of partons in final state  either  2 or 3
    x1 = 0.072082;                  #Bjorken x of incoming partons, 1 in + z , 2 in -z direction
    x2 = 0.123500;
    pdf1 = array.array('d',[0,0.0391232,0.0541232,0.0845228,0.105186,0.129429,0.86471,0.345418,0.561297,0.0845228,0.0541232,0.0391232,0])  #from -6 to 6: pdfs for 1st parton
    pdf2 = array.array('d',[0,0.0143834,0.0205766,0.0334123,0.0462144,0.0601489,0.345621,0.246406,0.468401,0.0334123,0.0205766,0.0143834,0])  #from -6 to 6: pdfs for 2nd parton
    flavour1In = -2;                          #flavour of incoming/outgoing parton n
    flavour2In = 2;                           #flavour assignment: t = 6  b = 5 c = 4, s = 3, u = 2, d = 1   
    flavour1Out = -2;                         #anti-qarks with negative sign
    flavour2Out = 2;                          #gluon = 0 
    flavour3Out = 0;

    ooES = OptObsEventStore();
    if (useEventStore):
      if (silent == False):
        print("Using EventStore")
      ooES.initPDFSet("CT10", 0, 91.2)

    for i in range(0,iterations):
      if not silent:
        print("Running iteration {}".format(i+1))
      if useEventStore:
        if (useNewEvent):
          eventNumber+=i

        oo1 = ooES.getWeightsDtilde(0, eventNumber, ecm, mH , npafin,flavour1In,flavour2In,flavour1Out,flavour2Out,flavour3Out,x1,x2,pjet1,pjet2,pjet3,phiggs);
        oo2 = ooES.getWeightsDtilde(1, eventNumber, ecm, mH , npafin,flavour1In,flavour2In,flavour1Out,flavour2Out,flavour3Out,x1,x2,pjet1,pjet2,pjet3,phiggs);
        if not silent:
          print("Calling getWeightsDtilde(...)! Results are: {} , {}".format(oo1,oo2))

        oo1 = ooES.getOptObs(0, eventNumber, ecm, mH ,x1,x2,Q,pjet1,pjet2,phiggs);
        oo2 = ooES.getOptObs(1, eventNumber, ecm, mH ,x1,x2,Q,pjet1,pjet2,phiggs);

        if not silent:
          print("Calling getOptObs(...)! Results are: {} , {}".format(oo1,oo2))

        rw =  ooES.getReweight(ecm, mH, 1 , \
          0.5, 0.5, 0.5, 0.5, 0.5, # rsmin,din,dbin,dtin,dtbin \
          0.5, 0.5, 0.5,           # a1hwwin,a2hwwin,a3hwwin \
          0.5, 0.5, 0.5,           # a1haain,a2haain,a3haain \
          0.5, 0.5, 0.5,           # a1hazin,a2hazin,a3hazin \
          0.5, 0.5, 0.5,           # a1hzzin,a2hzzin,a3hzzin \
          0.5,                     # lambdahvvin for formfactor if set to positive value \
          npafin,flavour1In,flavour2In,flavour1Out,flavour2Out,flavour3Out, \
          x1,x2,pjet1,pjet2,pjet3,phiggs)
        if not silent:
          print("Calling getReweight(...)! Result is: {}".format(rw))

      else:

        weights = ROOT.HLeptonsCPRW.getWeightsDtilde(ecm, mH , npafin,flavour1In,flavour2In,flavour1Out,flavour2Out,flavour3Out,x1,x2,pjet1,pjet2,pjet3,phiggs);
        if not silent:
          print("Calling getWeightsDtilde(...)! Results are: {} , {}".format(weights.first,weights.second))

        oo = ROOT.HLeptonsCPRW.getOptObs(ecm, mH ,x1,x2,pdf1,pdf2,pjet1,pjet2,phiggs);
        if not silent:
          print("Calling getOptObs(...)! Results are: {} , {}".format(oo.first,oo.second))

        rw = \
        ROOT.HLeptonsCPRW.getReweight(ecm, mH, 1 , \
        0.5, 0.5, 0.5, 0.5, 0.5, #rsmin,din,dbin,dtin,dtbin \
        0.5, 0.5, 0.5,           #a1hwwin,a2hwwin,a3hwwin \
        0.5, 0.5, 0.5,           #a1haain,a2haain,a3haain \
        0.5, 0.5, 0.5,           #a1hazin,a2hazin,a3hazin \
        0.5, 0.5, 0.5,           #a1hzzin,a2hzzin,a3hzzin \
        0.5,                     #lambdahvvin for formfactor if set to positive value \
        npafin,flavour1In,flavour2In,flavour1Out,flavour2Out,flavour3Out, \
        x1,x2,pjet1,pjet2,pjet3,phiggs)
        if not silent:
            print("Calling getReweight(...)! Result is: {}".format(rw))



if __name__ == '__main__':

    import argparse

    parser = argparse.ArgumentParser(description='Dumping tables for the effect of sys')
    parser.add_argument ("-s","--silent",
                        dest="silent",
                        action='store_true',
                        default=False)
    parser.add_argument ("-e","--useEventStore",
                        dest="useEventStore",
                        action='store_true',
                        default=False)
    parser.add_argument ("-u","--useNewEvent",
                        dest="useNewEvent",
                        action='store_true',
                        default=False)
    parser.add_argument ("-i","--iterations",
                        dest="iterations",
                        default=1)

    args = parser.parse_args()

    #for(int i=0; i<argc; ++i)
    #{   
      #if (TString(argv[i]).Contains("--useEventStore")) useEventStore = true;
      #if (TString(argv[i]).Contains("--silent")) silent = true;
      #if (TString(argv[i]).Contains("--useNewEvent")) useNewEvent = true;
      #if (TString(argv[i]) == "-i") iterations = atoi(argv[i+1]);
    #}
    main(args.useEventStore,args.silent,args.useNewEvent,args.iterations)
