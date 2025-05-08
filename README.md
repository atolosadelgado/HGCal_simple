# To configure, build and install

```
cmake -B build -S . -D CMAKE_INSTALL_PREFIX=install
cmake --build build -- -j 5 install
export LD_LIBRARY_PATH=$PWD/install/lib:$LD_LIBRARY_PATH
```

# Geant4 application

Evolved from Geant4 course by M. Novak.

Geant4 application shoots a geantino and prints the layer information and the material information suitable for DD4hep

# DD4hep

Layered detector builds the 900 layers of HGCal TB, as in the GDML. Simulation is slower with respect to Geant4 stand alone, but DD4hep+EDM4hep provide the machinery to record hits and MC particle tree out of the box.

## Key parameters

## Production cut per particle

In DD4hep, cuts per particle are specified as limits in `<limitset name="my_limits">`. To check if they took effect, execute UI command `/run/dumpRegions my_region`.

## Filter to avoid saving every hit

Specified by `SIM.filter.tracker`in `steering.py`.

## Checking data extension

Inside a ROOT session,

```
gSystem->Load("libDDCore");
gSystem->Load("libDDG4");
gSystem->Load("install/lib/liblayered_detector.so");
.L dd4hep_plugin/hgcal_info.hpp
dd4hep::Detector& lcdd = dd4hep::Detector::getInstance();
lcdd.fromXML("compact/hgcal_simple.xml")
auto det = lcdd.detector("MyDetector")
auto info = det.extension<hgcal_info>();
info->layer_v.size()
```
