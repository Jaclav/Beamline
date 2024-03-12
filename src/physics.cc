#include "physics.hh"
#include "G4PhotoElectricEffect.hh"
#include "G4GammaConversion.hh"
#include "G4RayleighScattering.hh"
#include "G4ComptonScattering.hh"

MyPhysicsList::MyPhysicsList() {
	RegisterPhysics (new G4EmStandardPhysics(false));
	// RegisterPhysics (new G4OpticalPhysics());
	RegisterPhysics (new G4HadronPhysicsShielding(false));
}

MyPhysicsList::~ MyPhysicsList() {

}
