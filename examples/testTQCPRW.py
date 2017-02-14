#! /bin/env python2

def main():
    from HLeptonsCPRW import TQOptObsObservable
    import QFramework
    dtPos = 0.3
    dtNeg = -0.2
    pTCutoff = 0.0
    tags = 'pTCutoff={}'.format(pTCutoff)
    hqqq = TQOptObsObservable("hqqq",tags);
    npafin = TQOptObsObservable("npafin",tags);
    oo1truth = TQOptObsObservable("OptimalObservable1",tags);
    oo2truth = TQOptObsObservable("OptimalObservable2",tags);
    wdtlin = TQOptObsObservable("WeightDTilde_lin",'isDebugRun=false,'+tags);
    wdtquad = TQOptObsObservable("WeightDTilde_quad",tags);
    rwPos = TQOptObsObservable("Reweight", tags, dtPos);
    rwNeg = TQOptObsObservable("Reweight", tags, dtNeg);
    oo1reco = TQOptObsObservable("OptimalObservable1",'isReco=true,'+tags);
    oo2reco = TQOptObsObservable("OptimalObservable2",'isReco=true,'+tags);
    QFramework.TQObservable.addObservable(npafin,"npafin");
    QFramework.TQObservable.addObservable(hqqq,"hqqq");
    QFramework.TQObservable.addObservable(oo1truth,"OO1Truth");
    QFramework.TQObservable.addObservable(oo2truth,"OO2Truth");
    QFramework.TQObservable.addObservable(oo1reco,"OO1Reco");
    QFramework.TQObservable.addObservable(oo2reco,"OO2Reco");
    QFramework.TQObservable.addObservable(wdtlin,"weightDTilde_lin");
    QFramework.TQObservable.addObservable(wdtquad,"weightDTilde_quad");
    QFramework.TQObservable.addObservable(rwPos,"weightDTildePos");
    QFramework.TQObservable.addObservable(rwNeg,"weightDTildeNeg");
    QFramework.TQObservable.printObservables();
    samples = QFramework.TQSampleFolder.newSampleFolder('samples')
    sample = QFramework.TQSample('testSample')
    fileIn = '/storage/groups/atl/reweight_samples/hist-mc15_13TeV.341156.PowhegPythia8EvtGen_CT10_AZNLOCTEQ6L1_VBFH125_tautaulh.merge.DAOD_HIGG4D2.e3888_s2608_s2183_r7772_r7676_p2949.root'
    sample.setTagString('.xsp.filepath',fileIn)
    sample.setTagString('.xsp.treename','NOMINAL')
    samples.setTagBool( "usemcweights", True)
    samples.addObject(sample)
    QFramework.TQTreeObservable.allowErrorMessages(True)
    init = QFramework.TQSampleInitializer()
    sample.visitMe(init)
    cut = QFramework.TQCut('base')
    cut.setCutExpression('1')
    #cut.setCutExpression('event_number == 356242')
    cut.setWeightExpression('1.')
    #cut.setWeightExpression('(0.1*[weightDTilde_lin])+(0.01*[weightDTilde_quad])+1')
    histograms = QFramework.TQHistoMakerAnalysisJob()
    histograms.bookHistogram("TH1F('npafin','npafin',4,-0.5,3.5) << ([npafin] : 'npafin')")
    histograms.bookHistogram("TH1F('hqqq','hqqq',200,-100,100) << ([hqqq] : 'hqqq')")
    histograms.bookHistogram("TH1F('lin','lin',45,-2,2) << ([weightDTilde_lin] : 'lin')")
    histograms.bookHistogram("TH1F('quad','quad',45,-2,2) << ([weightDTilde_quad] : 'quad')")
    histograms.bookHistogram("TH1F('rwPos','rwPos',45,-2,2) << ([weightDTildePos] : 'rwPos')")
    histograms.bookHistogram("TH1F('rwNeg','rwNeg',45,-2,2) << ([weightDTildeNeg] : 'rwNeg')")
    histograms.bookHistogram("TH1F('test','test',45,-2,2) << ( ({0}*[weightDTilde_lin])+({0}*{0}*[weightDTilde_quad])-[weightDTildePos]+1 : 'test')".format(dtPos))
    histograms.bookHistogram("TH1F('testNeg','testNeg',45,-2,2) << ( ({0}*[weightDTilde_lin])+({0}*{0}*[weightDTilde_quad])-[weightDTildeNeg]+1 : 'testNeg')".format(dtNeg))
    histograms.bookHistogram("TH1F('mmc_m','mmc_m',60,0,600) << (lephad_mmc_maxw_m : 'mmc_mc')")
    histograms.bookHistogram("TH1F('OO1Truth','OO1Truth',60,-12,12) << ([OO1Truth] : 'OO1Truth')")
    histograms.bookHistogram("TH1F('OO2Truth','OO2Truth',60,-12,12) << ([OO2Truth] : 'OO2Truth')")
    histograms.bookHistogram("TH1F('OO1Reco','OO1Reco',60,-12,12) << ([OO1Reco] : 'OO1Reco')")
    histograms.bookHistogram("TH1F('OO2Reco','OO2Reco',60,-12,12) << ([OO2Reco] : 'OO2Reco')")
    cut.addAnalysisJob(histograms)
    vis = QFramework.TQAnalysisSampleVisitor()
    vis.setVerbose(True)
    vis.setBaseCut(cut)
    cut.printCut()
    samples.visitMe(vis)
    samples.writeToFile('output.root')
    return 1;

if __name__ == '__main__':
    main()
