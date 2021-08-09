import parton
import numpy

pdfdir = "."

# TODO try this and print error when not available
# pdf = parton.mkPDF(name='CT10', member=0, pdfdir=pdfdir)

PDF = None


def init_PDF():
    global PDF
    print(pdfdir)
    PDF = parton.mkPDF(name='CT10', member=0, pdfdir=pdfdir)
    return PDF


try:
    PDF = init_PDF()
except ValueError as e:
    print(f"{e}")
    print("Install the CT10 PDF set in your working dir or specify in vbfcprw.pdf.pdfdir e.g. by:")
    print("wget -qO- http://lhapdfsets.web.cern.ch/lhapdfsets/current/CT10.tar.gz| tar xvz -C .")
    print("and call vbfcprw.init_PDF() again yourself.")


def getPDFs(x1, x2, Q):
    # pre- and appending 0s for top quarks
    pdf1 = numpy.array([0]+[PDF.xfxQ(flavor, x1, Q) for flavor in range(-5, 6)]+[0])
    pdf2 = numpy.array([0]+[PDF.xfxQ(flavor, x2, Q) for flavor in range(-5, 6)]+[0])
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
            return PDF.xfxQ(f, x, Q)

    pdfOut = numpy.concatenate([protect_top(f) for f in flavors], axis=1)
    return pdfOut
