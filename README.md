This is a RootCore-compliant wrapper around Fortran-routines written by M. Schumacher using routines from HAWK (https://hawk.hepforge.org). 
The module `hawkroutines` contains the bare fortran interface. The relevant subroutines are mirrored in the `vbfcprw` module with docstrings: `optobs`, `weightdtilde`, `reweight`.

The module `vbfcprw` additionally contains more convenient object-style interfaces `OptimalObservable` and `WeightDtilde`

# Examples 

See also `vbfcprw/test_vbfcprw.py`
```
oo = OptimalObservable([pjet1, pjet2], phiggs)
print(f"First order OO: {oo.oo1}, Second order: {oo.o2}")
```

# Requirements

- CT10 PDF set
- Fortran compiler

# References
- HAWK (https://hawk.hepforge.org)
- CT10
- LHAPDF
