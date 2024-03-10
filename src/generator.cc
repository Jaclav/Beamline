#include "generator.hh"

MyGenerator::MyGenerator() {
	fParticleGun = new G4ParticleGun(1);

	G4ParticleDefinition *particle = G4Proton::Definition();
	fParticleGun->SetParticleDefinition(particle);

	G4ThreeVector momentum(0, 0, 1.);
	fParticleGun->SetParticleMomentumDirection(momentum);
	fParticleGun->SetParticleEnergy(parameters[2] / 10 * GeV);
	std::cerr << fParticleGun->GetParticleEnergy() << '\n';
}

MyGenerator::~MyGenerator () {
	delete fParticleGun;
}

void MyGenerator::GeneratePrimaries(G4Event* event) {
	G4ThreeVector pos((G4UniformRand() - 0.5) * 0.02 * m, (G4UniformRand() - 0.5) * 0.02 * m, -0.5 * m);
	fParticleGun->SetParticlePosition(pos);
	fParticleGun->GeneratePrimaryVertex(event);

	//TODO: add fParticleSource
}
