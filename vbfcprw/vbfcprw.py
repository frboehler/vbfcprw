import hawkroutines
import numpy
from pylorentz import Momentum4
import parton

ecm = 13e3
scale_Q = 125
pdfdir = "."

# TODO try this and print error when not available
pdf = parton.mkPDF('CT10', 0, pdfdir=pdfdir)


def rapidity(lv):
    """calculate the rapidity of the Lorentz vector lv in z direction"""
    return 0.5*numpy.log((lv.e+lv.p_z)/(lv.e-lv.p_z))


class WeightDtilde:
    """object-style interface to weightdtilde function"""

    def __init__(self, flavourIn, flavourOut, pjetOut, phiggs):
        """
Args:
    flavourIn (list[int]): flavours of incoming partons in PDG ID
    flavourOut (list[int]): flavours of outgoin partons in PDG ID
    pjetIn (list[numpy.array[float]]): 4-moms of outgoing partons (E, Px, Py, Pz)
    phiggs (numpy.array[float]): 4-mom of Higgs boson (E, Px, Py, Pz)

Returns:
    None
        """
        assert len(flavourIn) == 2
        npafin = len(flavourOut)
        assert npafin == 2 or npafin == 3
        assert len(pjetOut) == npafin

        lv = Momentum4(*phiggs)
        mH = lv.m
        for pjet in pjetOut:
            lv += Momentum4(*pjet)
        x1 = lv.m/ecm*numpy.exp(rapidity(lv))
        x2 = lv.m/ecm*numpy.exp(-1*rapidity(lv))

        if npafin == 2:
            flavourOut += [0]
            pjetOut += [numpy.zeros(4)]

        self.wlin, self.wquad, ierr = weightdtilde(ecm, mH, npafin,
                                                   *flavourIn,
                                                   *flavourOut,
                                                   x1, x2,
                                                   *pjetOut,
                                                   phiggs)
        if ierr:
            raise RuntimeError("Something wrong in weightdtilde: ierr = %s" % ierr)

    def eventweight(self, dtilde=0):
        return 1 + self.wlin*dtilde + self.wquad*dtilde**2


def getPDFs(x1, x2, Q):
    # pre- and appending 0s for top quarks
    pdf1 = numpy.array([0]+[pdf.xfxQ(flavor, x1, Q) for flavor in range(-5, 6)]+[0])
    pdf2 = numpy.array([0]+[pdf.xfxQ(flavor, x2, Q) for flavor in range(-5, 6)]+[0])
    pdfIn = [pdf1, pdf2]
    return pdfIn


def getPDFs2(x1, x2, Q):
    """
this function is 30% faster than the one above
    """
    x = numpy.array([x1, x2])
    flavors = numpy.arange(-6, 7)

    def protect_top(f):
        if abs(f) == 6:
            return numpy.zeros(2).reshape(2, 1)
        else:
            return pdf.xfxQ(f, x, Q)

    pdfOut = numpy.concatenate([protect_top(f) for f in flavors], axis=1)
    return pdfOut


class OptimalObservable:
    """object style interfacet to optimal observable function"""

    def __init__(self, pdfIn, pjetOut, phiggs):
        """
Args:
    pdfIn (list[numpy.array[float]]): PDFs of incoming partons
    pjetOut (list[numpy.array[float]]): 4-moms of outgoin jets (E, Px, Py, Pz)
    phiggs (numpy.array[float]): 4-mom of Higgs boson (E, Px, Py, Pz)

"""
        assert len(pdfIn) == 2
        assert len(pjetOut) == 2

        lv = Momentum4(*phiggs)
        if scale_Q == "mH":
            Q = lv.m
        else:
            Q = scale_Q
        for pjet in pjetOut:
            lv += Momentum4(*pjet)
        x1 = lv.m/ecm*numpy.exp(rapidity(lv))
        x2 = lv.m/ecm*numpy.exp(-1*rapidity(lv))

        pdfIn = getPDFs2(x1, x2, Q)

        # self.oo1, self.oo2, ierr = 1,1,1
        self.oo1, self.oo2, ierr = optobs(ecm, mH,
                                          x1, x2,
                                          *pdfIn,
                                          *pjetOut,
                                          phiggs)

        if ierr:
            raise RuntimeError("Something wrong in weightdtilde: ierr = %s" % ierr)


def optobs(ecm, mH, x1, x2, pdf1, pdf2, pjet1, pjet2, phiggs):
    """
wrapper for optobs subroutine in weightandoptobs.f
Args:
    ecm (float): center of mass energy in GeV
    mH (float): Higgs boson mass in GeV
    x1 (float): momentum fraction of incoming parton 1 ((finalstate_tlv.M()/ecm)*TMath::Exp(finalstate_tlv.Rapidity());)
    x2 (float): momentum fraction of incoming parton 2 ((finalstate_tlv.M()/ecm)*TMath::Exp(-1*finalstate_tlv.Rapidity());)
    pdf1 (numpy.array[float]): PDFs of incoming parton 1 from -6 to 6 reprensenting the quark flavours
    pdf2 (numpy.array[float]): PDFs of incoming parton 2 from -6 to 6 reprensenting the quark flavours
    pjet1 (numpy.array): 4-mom of outgoing jet 1 (E, Px, Py, Pz)
    pjet2 (numpy.array): 4-mom of outgoing jet 2 (E, Px, Py, Pz)
    phiggs (numpy.array): 4-mom of Higgs boson (E, Px, Py, Pz)

Returns:
    tuple: (oo1, oo2, ierr) Optimal Observable first order, second order, error code
"""
    return hawkroutines.optobs(ecm, mH,
                               x1, x2,
                               pdf1, pdf2,
                               pjet1, pjet2,
                               phiggs)


def weightdtilde(ecm, mH, npafin, flavour1In, flavour2In, flavour1Out, flavour2Out, flavour3Out, x1, x2, pjet1, pjet2, pjet3, phiggs):
    """
wrapper for the fortran function in weightandoptons.f

Args:
    ecm (float): center of mass energy in GeV
    mH (float): Higgs boson mass in GeV
    npafin (int): number of partons in final state, 2 or 3
    flavour1In (int): PDG ID of incoming parton 1, i.e. t = 6  b = 5 c = 4, s = 3, u = 2, d = 1
    flavour2In (int): PDG ID of incoming parton 2
    flavour1Out (int): PDG ID of outgoing parton 1
    flavour2Out (int): PDG ID of outgoing parton 2
    flavour3Out (int): PDG ID of outgoing parton 3
    x1 (float): momentum fraction of incoming parton 1 ((finalstate_tlv.M()/ecm)*TMath::Exp(finalstate_tlv.Rapidity());)
    x2 (float): momentum fraction of incoming parton 2 ((finalstate_tlv.M()/ecm)*TMath::Exp(-1*finalstate_tlv.Rapidity());)
    pjet1 (numpy.array): 4-mom of outgoing parton 1 (E, Px, Py, Pz)
    pjet2 (numpy.array): 4-mom of outgoing parton 2 (E, Px, Py, Pz)
    pjet3 (numpy.array): 4-mom of outgoing parton 3 (E, Px, Py, Pz)
    phiggs (numpy.array): 4-mom of Higgs boson (E, Px, Py, Pz)

Returns:
    tuple: (wedtlin, wedtquad, ierr) linear weight, quadratic weight, error code
"""
    return hawkroutines.weightdtilde(ecm, mH, npafin,
                                     flavour1In,
                                     flavour2In,
                                     flavour1Out,
                                     flavour2Out,
                                     flavour3Out,
                                     x1, x2,
                                     pjet1, pjet2, pjet3,
                                     phiggs)




pjet1 = numpy.array([438.019730, -24.873165, -94.306022, 427.023386])               # E,px,py,pz of nth final state parton
pjet2 = numpy.array([656.475632, -55.150478, 66.466227, -650.769506])
pjet3 = numpy.array([51.082110, 25.871174, 3.770224, 43.884504])
phiggs= numpy.array([177.080599, 54.152473, 24.069573, -110.547404])            # E,px,py,pz of Higgs boson make sure that four-momentum conservation holds 
ecm = 13000.;                           #proton-proton center-of mass energy in GeV
mH = 124.999901;                       #mass of Higgs boson in Gev
npafin = 3;                            #number of partons in final state  either  2 or 3
x1 = 0.072082;                  #Bjorken x of incoming partons, 1 in + z , 2 in -z direction
x2 = 0.123500;
Q = 84000;
flavour1In = -2;                          #flavour of incoming/outgoing parton n
flavour2In = 2;                           #flavour assignment: t = 6  b = 5 c = 4, s = 3, u = 2, d = 1   
flavour1Out = -2;                         #anti-qarks with negative sign
flavour2Out = 2;                          #gluon = 0 
flavour3Out = 0;
eventNumber = 1234;

# Only used when ran without the Event-store:
pdf1 = numpy.array([0, 0.0391232, 0.0541232, 0.0845228, 0.105186,  0.129429,  0.86471,  0.345418, 0.561297, 0.0845228, 0.0541232, 0.0391232, 0])  #from -6 to 6: pdfs for 1st parton
pdf2 = numpy.array([0, 0.0143834, 0.0205766, 0.0334123, 0.0462144, 0.0601489, 0.345621, 0.246406, 0.468401, 0.0334123, 0.0205766, 0.0143834, 0])  #from -6 to 6: pdfs for 2nd parton

def test1():
    print(hawkroutines.weightdtilde(ecm, mH, npafin, flavour1In, flavour2In, flavour1Out, flavour2Out, flavour3Out, x1, x2, pjet1, pjet2, pjet3, phiggs))
def test2():
    print(weightdtilde(ecm, mH, npafin, flavour1In, flavour2In, flavour1Out, flavour2Out, flavour3Out, x1, x2, pjet1, pjet2, pjet3, phiggs))
def test3():
    w = WeightDtilde([flavour1In, flavour2In],
                     [flavour1Out, flavour2Out, flavour3Out],
                     [pjet1, pjet2, pjet3],
                     phiggs)
    print(w.eventweight())
    return w
def test4():
    oo = OptimalObservable([pdf1, pdf2],
                           [pjet1, pjet2],
                           phiggs)
    # print(oo.oo1, oo.oo2)
    return oo
