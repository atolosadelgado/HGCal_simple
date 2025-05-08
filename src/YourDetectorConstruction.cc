
#include "YourDetectorConstruction.hh"

// for geometry definitions 
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

// for material definitions
#include "G4Material.hh"
#include "G4NistManager.hh"

// for having units and constants
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

//
#include "G4GDMLParser.hh"
#include "G4GeomTestVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SDManager.hh"
#include "G4VisAttributes.hh"

// CTR
YourDetectorConstruction::YourDetectorConstruction()
:   G4VUserDetectorConstruction() {

}

// DTR
YourDetectorConstruction::~YourDetectorConstruction() {}

//
// The detector is a simple slab (with fTargetThickness along the x-direction).
//
G4VPhysicalVolume* YourDetectorConstruction::Construct() {
  G4GDMLParser Parser;
  Parser.Read("TBHGCal181Oct.gdml", false);
  auto worldPV = Parser.GetWorldVolume();

  return worldPV;

}
