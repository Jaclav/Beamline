#include "generator.hh"
#include <mutex>

std::mutex initMutex;

MyGenerator::MyGenerator() {
	initMutex.lock();
	fParticleGun = new G4ParticleGun(1);

	G4ParticleDefinition *particle = G4Proton::Definition();
	fParticleGun->SetParticleDefinition(particle);

	G4ThreeVector momentum(0, 0, 1.);
	fParticleGun->SetParticleMomentumDirection(momentum);
	// fParticleGun->SetParticleMomentum(parameters[2] * GeV);
	fParticleGun->SetParticleEnergy(parameters[2] * GeV);
	outFile << "# Name=" << particle->GetParticleName() <<
	        " p=" << fParticleGun->GetParticleMomentum() / 1000. << "GeV/c " <<
	        " E=" << fParticleGun->GetParticleEnergy() / 1000. << "GeV\n";

	initMutex.unlock();
}
MyGenerator::~MyGenerator () {
	delete fParticleGun;
}

void MyGenerator::GeneratePrimaries(G4Event * event) {
	if(isUI)
		outFile.flush();
	//diameter of beam is 2cm
	G4double r = G4UniformRand() * m / 100;
	G4double phi = G4UniformRand() * M_PI;
	G4ThreeVector pos(r * std::cos(phi), r * sin(phi), -.5 * m);
	fParticleGun->SetParticlePosition(pos);
	fParticleGun->GeneratePrimaryVertex(event);

	//TODO: add fParticleSource
}
