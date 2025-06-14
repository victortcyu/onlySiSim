// file: src/PhononPhysicsList.cc

#include "PhononPhysicsList.hh"
#include "G4CMPPhysics.hh"        
#include "G4EmStandardPhysics.hh" 

#include "G4SystemOfUnits.hh"

PhononPhysicsList::PhononPhysicsList(G4int verbose) : G4VModularPhysicsList() {
	SetVerboseLevel(verbose);

	if (verbose) G4cout << "G4CMPPhysicsList::constructor" << G4endl;

	defaultCutValue = DBL_MIN;

	RegisterPhysics(new G4EmStandardPhysics(verbose));

	RegisterPhysics(new G4CMPPhysics(verbose));
}

PhononPhysicsList::~PhononPhysicsList() {}

void PhononPhysicsList::SetCuts() {
	SetCutsWithDefault();
}