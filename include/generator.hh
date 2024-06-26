#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4GeneralParticleSource.hh"
#include "G4SystemOfUnits.hh"
#include "G4UniformRandPool.hh"
#include "G4Proton.hh"
#include "G4Neutron.hh"
#include "G4PionPlus.hh"
#include <fstream>

extern std::fstream outFile;
extern G4double *parameters;
extern bool isUI;
class MyGenerator : public G4VUserPrimaryGeneratorAction {
public:
	MyGenerator();
	~MyGenerator ();
	virtual void GeneratePrimaries(G4Event*);
private:
	G4ParticleGun *fParticleGun;
};

#endif //GENERATOR_HPP
