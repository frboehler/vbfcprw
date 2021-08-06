import setuptools
from numpy.distutils.core import setup, Extension


#---------------------------------------------------------------------------  
ext1 = Extension(
    name='hawkroutines',
    sources=['Root/hawkroutines.f',
             'Root/weightandoptobs.f'],
    f2py_options=["--quiet"],
)

#--------------------------------------------------------------------------
setup(
    name='vbfcprw',
    version='0.1',
    ext_modules=[ext1],
    py_modules=['vbfcprw'],
    install_requires=["numpy", "pylorentz", "parton"],
    author="David Hohn",
    author_email="hohn.david@gmail.com",
    url="https://gitlab.cern.ch/FreiburgSchumacher/vbfcp/HLeptonsCPRW"
)

# manually this works too
# python -m numpy.f2py -c Root/*.f -m hawkroutines
