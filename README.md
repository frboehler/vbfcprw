This is a wrapper around Fortran-routines written by M. Schumacher
using routines extracted from [HAWK](https://hawk.hepforge.org).  The
module `hawkroutines` contains the bare fortran interface. The
relevant subroutines are mirrored in the `vbfcprw` module with
docstrings: `optobs`, `weightdtilde`, `reweight`.

The module `vbfcprw` additionally contains more convenient
object-style interfaces `OptimalObservable` and `WeightDtilde`

# Examples 

See also `vbfcprw/test_vbfcprw.py`
```py
import vbfcprw, numpy

pjet1 = numpy.array([438.019730, -24.873165, -94.306022, 427.023386])  # E,px,py,pz of nth final state parton
pjet2 = numpy.array([656.475632, -55.150478, 66.466227, -650.769506])
phiggs= numpy.array([177.080599, 54.152473, 24.069573, -110.547404])   # E,px,py,pz of Higgs boson make sure that four-momentum conservation holds 

oo = vbfcprw.OptimalObservable([pjet1, pjet2], phiggs)
print(f"First order OO: {oo.oo1}, Second order: {oo.oo2}")
```

# Requirements

If the wheel is incompatible:
- Fortran and C compiler (e.g. gfortran in gcc)

# References
- [HAWK](https://hawk.hepforge.org)
- [CT10 PDF set](https://ct.hepforge.org/PDFs/ct10_2010.html)
- Markus Schumacher
- [arXiv:2002.05315 [hep-ex]](https://arxiv.org/abs/2002.05315)
- [arXiv:1602.04516 [hep-ex]](https://arxiv.org/abs/1602.04516)


# Link back
https://pypi.org/project/vbfcprw/
