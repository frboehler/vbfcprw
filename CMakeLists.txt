################################################################################
# Package: HLeptonsCPRW
# calculates VBFH matrix element for event reweighting and Optimal Observable computation
################################################################################

# Declare the package name:
atlas_subdir( HLeptonsCPRW )

atlas_depends_on_subdirs( PUBLIC
			  External/AtlasROOT )

find_package( ROOT   )
find_package( Lhapdf )

# Component(s) in the package:
atlas_add_library( HLeptonsCPRW
  Root/*.f Root/*.cxx
  PUBLIC_HEADERS HLeptonsCPRW
  PRIVATE_INCLUDE_DIRS   ${LHAPDF_INCLUDE_DIRS}
  PRIVATE_LINK_LIBRARIES ${LHAPDF_LIBRARIES} 
  )

#dictionary for ROOT
atlas_add_dictionary(
  HLeptonsCPRWDict
  HLeptonsCPRW/HLeptonsCPRWDict.h
  HLeptonsCPRW/selection.xml
  LINK_LIBRARIES HLeptonsCPRW
  )

atlas_install_python_modules( python/*.py )
atlas_install_scripts( examples/*.py )

# compile the test
atlas_add_executable(
  testCPRW
  examples/testCPRW.cxx
  INCLUDE_DIRS   ${ROOT_INCLUDE_DIRS}
  LINK_LIBRARIES ${ROOT_LIBRARIES}   HLeptonsCPRW
  )
  
#tests
atlas_add_test(
  test_py
  SCRIPT
  testCPRW.py  --useEventStore
  )

atlas_add_test(
  test_cpp
  SCRIPT
  testCPRW --useEventStore
  )
