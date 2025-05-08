
#include "YourEventAction.hh"

// #include "G4RunManager.hh"
// #include "YourRun.hh"
#include "G4Material.hh"
#include "G4MaterialTable.hh"

YourEventAction::YourEventAction()
: G4UserEventAction() {}


YourEventAction::~YourEventAction() {}


// Beore each event: reset per-event variables
void YourEventAction::BeginOfEventAction(const G4Event* /*anEvent*/) {
//   fEdepPerEvt           = 0.0;
//   fChTrackLengthPerEvt  = 0.0;
}


// After each event:
// fill the data collected for this event into the Run global (thread local)
// data Run data object (i.e. into YourRun)
void YourEventAction::EndOfEventAction(const G4Event* /*anEvent*/) {
  // get the current Run object and cast it to YourRun (because for sure this is its type)
//   YourRun* currentRun = static_cast< YourRun* > ( G4RunManager::GetRunManager()->GetNonConstCurrentRun() );
    // add the quantities to the (thread local) run global YourRun object
//     currentRun->AddEnergyDepositPerEvent( fEdepPerEvt );
//     currentRun->AddChTrackLengthPerEvent( fChTrackLengthPerEvt );
//     currentRun->FillEdepHistogram( fEdepPerEvt );
  G4cout << "List of materials crossed\n";
  for( auto & material_name : material_set )
  {
//     G4cout << material_name << G4endl;

    auto mat = G4Material::GetMaterial( material_name);
    PrintMaterialAsDD4hepXML(mat);

  }

  WriteDetectorXML( this->layers );
}
