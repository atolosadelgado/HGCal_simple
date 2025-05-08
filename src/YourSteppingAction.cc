
#include "YourSteppingAction.hh"

#include "YourDetectorConstruction.hh"

#include "G4Step.hh"

#include <iomanip>

#include "YourEventAction.hh"

YourSteppingAction::YourSteppingAction(YourEventAction * evtAction)
:   G4UserSteppingAction(), _evtAction(evtAction) { }


YourSteppingAction::~YourSteppingAction() {}


//
// Score only if the step was done in the Target:
//  - cllect energy deposit for the mean (per-event) energy deposit computation
//  - same for the charged particle track length
void YourSteppingAction::UserSteppingAction(const G4Step* theStep) {

  const G4VPhysicalVolume * volume = theStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
  G4Material * material = volume->GetLogicalVolume()->GetMaterial();
  const G4String material_name = material->GetName();
  _evtAction->material_set.emplace( material_name);

  const G4double trackL = theStep->GetStepLength();
  G4cout << std::setprecision(3) << std::fixed << trackL/CLHEP::mm << "\t\t" << material_name << G4endl;
  _evtAction->layers.push_back( {trackL/CLHEP::mm, material_name} );


}
