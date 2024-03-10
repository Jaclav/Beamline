#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include "G4VModularPhysicsList.hh"
#include "G4EmStandardPhysics.hh"
#include "G4OpticalPhysics.hh"
#include "G4HadronPhysicsShielding.hh"

class MyPhysicsList : public G4VModularPhysicsList {
public:
	MyPhysicsList();
	~MyPhysicsList();
};

#endif //PHYSICS_HPP
