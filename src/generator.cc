#include "generator.hh"

MyGenerator::MyGenerator() {
	fParticleGun = new G4ParticleGun(1);

	G4ParticleDefinition *particle = G4Proton::Definition();
	fParticleGun->SetParticleDefinition(particle);

	G4ThreeVector momentum(0, 0, 1.);
	fParticleGun->SetParticleMomentumDirection(momentum);
	fParticleGun->SetParticleMomentum(parameters[2] * GeV);
	outFile << "# Name=" << particle->GetParticleName() << " p=" << fParticleGun->GetParticleMomentum() / 1000. << "GeV/c\n";
}
MyGenerator::~MyGenerator () {
	delete fParticleGun;
}

void MyGenerator::GeneratePrimaries(G4Event * event) {
	//todo do it circle
	// G4ThreeVector pos((G4UniformRand() - 0.5) * 0.02 * m, (G4UniformRand() - 0.5) * 0.02 * m, -0.5 * m);
	G4ThreeVector pos(0.02 * m, 0.02 * m, -0.5 * m);
	fParticleGun->SetParticlePosition(pos);
	fParticleGun->GeneratePrimaryVertex(event);

	//TODO: add fParticleSource
}
