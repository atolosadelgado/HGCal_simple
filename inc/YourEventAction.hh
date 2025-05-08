
#ifndef YOUREVENTACTION_HH
#define YOUREVENTACTION_HH

#include "G4UserEventAction.hh"

#include "globals.hh"
#include <string>
#include <set>
#include "G4Material.hh"
  #include <vector>
#include <utility>
#include <G4Types.hh>
#include <G4String.hh>
#include <iostream>
#include <iomanip>

/**
 * @file    YourEventAction.hh
 * @class   YourEventAction
 * @author  M. Novak
 * @date    December 2019
 *
 * Implementation of the ``Geant4`` ``G4UserEventAction`` **optional interface** for this user application.
 *
 * This interface gives the possibility for interacting with the simulation before
 * (BeginOfEventAction()) and after (EndOfEventAction()) the simulation of each event.
 *
 */

class YourEventAction : public G4UserEventAction {

  // Method declaration:
  public:

    // CTR:
    YourEventAction();
    ~YourEventAction() override;

    /**
     * Virtial method that is called by the RunManager before the start of each event.
     *
     * This is the point where we usually reset some local variables that are used to accumulate
     * information during the simnulation of a given event.
     *
     * @param[in] evt Pointer to the ``G4Event`` object that will be simulated now.
     */
    void BeginOfEventAction(const G4Event* evt) override;

    /**
     * Virtial method that is called by the RunManager after the end of each event.
     *
     * This is the point where we usually propagate to upper level (i.e. usualy to the run (YourRun) obejct)
     * local infomation, that has been collected during the simnulation of a given event.
     *
     * @param[in] evt Pointer to the ``G4Event`` object that simulated has just been completed.
     */
    void EndOfEventAction(const G4Event* evt) override;




    std::set<G4String> material_set;
    /// mymm = length in milimeters!
    using mymm=G4double;
    std::vector<std::pair<mymm, G4String>> layers;


  void PrintMaterialAsDD4hepXML(const G4Material* mat) {
      if (!mat) {
          std::cerr << "Null material pointer." << std::endl;
          return;
      }

      std::cout << "<material name=\"" << mat->GetName() << "\">\n";
      std::cout << "  <D value=\"" << mat->GetDensity() / (CLHEP::g/CLHEP::cm3) << "\" unit=\"g/cm3\"/>\n";

      if (mat->GetNumberOfElements() == 1 && mat->GetElement(0)->GetZ() == mat->GetZ()) {
          // Pure material (element)
          auto elem = mat->GetElement(0);
          std::cout << "  <atomicNumber value=\"" << elem->GetZ() << "\"/>\n";
          std::cout << "  <A value=\"" << elem->GetA() / (CLHEP::g/CLHEP::mole) << "\" unit=\"g/mole\"/>\n";
      } else {
          // Composite material
          for (size_t i = 0; i < mat->GetNumberOfElements(); ++i) {
              const G4Element* elem = mat->GetElement(i);
              double fraction = mat->GetFractionVector()[i];  // mass fraction
              std::cout << "  <composite ref=\"" << elem->GetName()
                        << "\" fraction=\"" << std::fixed << std::setprecision(6)
                        << fraction << "\"/>\n";
          }
      }

      std::cout << "</material>\n";
  }



void WriteDetectorXML(const std::vector<std::pair<G4double, G4String>>& layers) {
    std::cout << "<detector id=\"1\" name=\"MyDetector\" type=\"layered\" >\n";
    std::cout << "  <dimensions x=\"10\" y=\"10\" unit=\"cm\"/>\n";

    G4double zpos = 0.0; // cumulative position in mm

    for (size_t i = 0; i < layers.size(); ++i) {
        G4double thickness = layers[i].first;  // in mm
        const G4String& material = layers[i].second;

        std::cout << "  <slice name=\"layer" << i
                  << "\" thickness=\"" << std::fixed << std::setprecision(3)
                  << thickness << "\" unit=\"mm\" material=\"" << material << "\"/>\n";

        zpos += thickness;
    }

    std::cout << "</detector>\n";
}

};

#endif
