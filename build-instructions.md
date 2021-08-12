# Buidling locally

```bash
# just the f2py step manually
python -m numpy.f2py -c Root/*.f -m hawkroutines
# building the package, making a wheel, installing
python setup.py build
python setup.py bdist_wheel
python setup.py install
# or
python -m build
```

# Building wheels

You can use manylinux docker images to build compatible
wheels. Several manylinux and python versions are available.

```bash
docker run -ti -v $(pwd):/io quay.io/pypa/manylinux2010_x86_64 /bin/bash
# inside docker
cd /io
# build wheel. output in dist/
/opt/python/cp38-cp38/bin/python -m build
# relabel the wheel. output in wheelhouse/
auditwheel repair dist/vbfcprw-0.1-cp38-cp38-linux_x86_64.whl 
```

These wheels should cover running in any modern docker python
image. These wheels did not work with LCG_100 because that contains an
old numpy version.

# Publish to PyPI

Create your API token and use it as password with username "__token__" below.

```bash
# upload the sdist (tar.gz), but not the incompatible wheels
python3 -m twine upload dist/*
# upload the manylinux wheels
python3 -m twine upload wheelhouse/*
```
