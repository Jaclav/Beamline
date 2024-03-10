#include "generator.hh"

MyGenerator::MyGenerator() {
	fParticleGun = new G4ParticleGun(1);

	G4ParticleDefinition *particle = G4Proton::Definition();
	fParticleGun->SetParticleDefinition(particle);

	G4ThreeVector momentum(0, 0, 1.);
	fParticleGun->SetParticleMomentumDirection(momentum);
	fParticleGun->SetParticleMomentum(10 * GeV);
}

MyGenerator::~MyGenerator () {
	delete fParticleGun;
}

void MyGenerator::GeneratePrimaries(G4Event* event) {
	// G4ThreeVector pos((G4UniformRand() - 0.5) / 10.f * m, (G4UniformRand() - 0.5) / 10.f * m, -0.5 * m);
	G4ThreeVector pos(0, 0, -0.5 * m);
	fParticleGun->SetParticlePosition(pos);
	fParticleGun->GeneratePrimaryVertex(event);

	// fParticleSrc->ClearAll();
	// fParticleSrc->AddaSource(1);
	// fParticleSrc->SetParticlePosition(G4ThreeVector(0, 0, 0));
	// fParticleSrc->SetNumberOfParticles(3);
	// fParticleSrc->SetParticleDefinition(particle);
	// fParticleSrc->SetCurrentSourceIntensity(10);
	// fParticleSrc->GeneratePrimaryVertex(event);
}
