
#include "YourActionInitialization.hh"

#include "YourDetectorConstruction.hh"

#include "YourPrimaryGeneratorAction.hh"

#include "G4MaterialScanner.hh"

#include "YourSteppingAction.hh"

#include "YourEventAction.hh"

YourActionInitialization::YourActionInitialization(YourDetectorConstruction* det)
:   G4VUserActionInitialization(),
    fYourDetector(det) { }


YourActionInitialization::~YourActionInitialization() {}


// Create all User Actions here: 
void YourActionInitialization::Build() const {
  // Set UserPrimaryGeneratorAction
  YourPrimaryGeneratorAction* primaryAction = new YourPrimaryGeneratorAction(fYourDetector);
  SetUserAction(primaryAction);

  YourEventAction * evtAction = new YourEventAction;
  SetUserAction(evtAction);
  SetUserAction( new YourSteppingAction(evtAction) );
}
