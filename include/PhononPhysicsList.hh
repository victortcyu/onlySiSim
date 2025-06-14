// file: include/PhononPhysicsList.hh

#ifndef PhononPhysicsList_h
#define PhononPhysicsList_h 1

#include "G4VModularPhysicsList.hh"

// A custom physics list that inherits from the Geant4 modular physics list.
// This will allow us to register multiple physics components.

class PhononPhysicsList : public G4VModularPhysicsList {
public:
	PhononPhysicsList(G4int verbose = 1);
	virtual ~PhononPhysicsList();
	virtual void SetCuts();
};

#endif