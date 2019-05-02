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
atlas_add_library( HLeptonsCPRWLib
  Root/*.f Root/*.cxx
  PUBLIC_HEADERS HLeptonsCPRW
  INCLUDE_DIRS           ${ROOT_INCLUDE_DIRS}
  PRIVATE_INCLUDE_DIRS   ${LHAPDF_INCLUDE_DIRS}
  LINK_LIBRARIES         ${ROOT_LIBRARIES}
  PRIVATE_LINK_LIBRARIES ${LHAPDF_LIBRARIES} 
  )
