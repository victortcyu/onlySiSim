#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4UIExecutive.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"

#include "PhononPhysicsList.hh"
#include "G4CMPConfigManager.hh"
#include "PhononActionInitialization.hh"
#include "PhononConfigManager.hh"
#include "PhononDetectorConstruction.hh"
#include "PhononSteppingAction.hh"

int main(int argc,char** argv)
{

 // Construct the run manager
#ifdef G4MULTITHREADED
    auto runManager = new G4MTRunManager;
    G4int nThreads = G4Threading::G4GetNumberOfCores();
    runManager->SetNumberOfThreads(nThreads);
    G4cout << "----> G4CMP Phonon example is running in multithreaded mode with " << nThreads << " threads." << G4endl;
#else
    auto runManager = new G4RunManager;
    G4cout << "----> G4CMP Phonon example is running in sequential mode." << G4endl;
#endif

 // Set mandatory initialization classes
 //
 PhononDetectorConstruction* detector = new PhononDetectorConstruction();
 runManager->SetUserInitialization(detector);

 G4VUserPhysicsList* physics = new PhononPhysicsList();
 physics->SetCuts();
 runManager->SetUserInitialization(physics);
 
 // Set user action classes (different for Geant4 10.0)
 //
 runManager->SetUserInitialization(new PhononActionInitialization);

 // Create configuration managers to ensure macro commands exist
 G4CMPConfigManager::Instance();
 PhononConfigManager::Instance();

 // Visualization manager
 //
 G4VisManager* visManager = new G4VisExecutive;
 visManager->Initialize();
 
 // Get the pointer to the User Interface manager
 //
 G4UImanager* UImanager = G4UImanager::GetUIpointer();  

 if (argc==1)   // Define UI session for interactive mode
 {
      G4UIExecutive * ui = new G4UIExecutive(argc,argv);
      ui->SessionStart();
      delete ui;
 }
 else           // Batch mode
 {
   G4String command = "/control/execute ";
   G4String fileName = argv[1];
   UImanager->ApplyCommand(command+fileName);
 }

 delete visManager;
 delete runManager;

 return 0;
}


