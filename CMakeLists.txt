#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(yourG4Application)


#----------------------------------------------------------------------------
# Find Geant4 package, no UI and Vis drivers activated
#
#find_package(Geant4 REQUIRED)

#----------------------------------------------------------------------------
# Find Geant4 package, with UI and Vis drivers activated
#
find_package(Geant4 REQUIRED ui_all vis_all)


#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
#
include(${Geant4_USE_FILE})


#----------------------------------------------------------------------------
# Locate sources and headers for this project
#
include_directories(${PROJECT_SOURCE_DIR}/inc
                    ${Geant4_INCLUDE_DIR})
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/inc/*.hh)

#----------------------------------------------------------------------------
# Add the executables, and link it to the Geant4 libraries
#
## APPLICATION WITHOUT UI and VIS (NOTE: use the proper find_package)
## add_executable(yourMainApplication yourMainApplication_noUI.cc ${sources} ${headers})
#
## APPLICATION WITH UI and VIS (NOTE: use the proper find_package)
add_executable(yourMainApplication yourMainApplication.cc ${sources} ${headers})

target_link_libraries(yourMainApplication ${Geant4_LIBRARIES} )



IF(NOT TARGET DD4hep::DDCore)
  find_package ( DD4hep REQUIRED )
  include ( ${DD4hep_DIR}/cmake/DD4hep.cmake )
  include ( ${DD4hep_DIR}/cmake/DD4hepBuild.cmake )
  dd4hep_configure_output()
ENDIF()


dd4hep_add_plugin(layered_detector SOURCES dd4hep_plugin/layered_detector.cpp
  USES DD4hep::DDCore DD4hep::DDRec )
install(TARGETS layered_detector LIBRARY DESTINATION lib)
