#include "detector.hh"
#include <mutex>

static std::mutex detMtx;
static std::mutex initMtx;

MySensitiveDetector::MySensitiveDetector(G4String name): G4VSensitiveDetector(name) {
	initMtx.lock();
	G4ParticleTable *pt = G4ParticleTable::GetParticleTable();
	for(int i = 0; i < pt->size(); i++)
		massTable[(int)std::round(pt->FindParticle(pt->GetParticleName(i))->GetPDGMass() * 1000)] = pt->FindParticle(pt->GetParticleName(i));
	initMtx.unlock();
}

MySensitiveDetector::~MySensitiveDetector() {
}

G4bool MySensitiveDetector::ProcessHits(G4Step* aStep, G4TouchableHistory *ROhist) {
	G4Track *track = aStep->GetTrack();
	track->SetTrackStatus(fStopAndKill);
	G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
	G4StepPoint *postStepPoint = aStep->GetPostStepPoint();

	if(!massTable.count((int)std::round(preStepPoint->GetMass() * 1000.f))) {
		//IDK why this happens
		std::cerr << "!!!!! UNKOWN:" <<
		          preStepPoint->GetMass() << ' ' <<
		          preStepPoint->GetKineticEnergy() << ' ' <<
		          preStepPoint->GetCharge() << '\n';
		return true;
	}

	detMtx.lock();
	particleCounts[(int)std::round(preStepPoint->GetMass() * 1000.f)]++;

	outFile << preStepPoint->GetMass() << ';' <<
	        preStepPoint->GetCharge() << ';' <<
	        preStepPoint->GetPosition().x() << ';' <<
	        preStepPoint->GetPosition().y() << ';' <<
	        preStepPoint->GetPosition().z() << ';' <<
	        preStepPoint->GetKineticEnergy() << ';' <<
	        massTable[(int)std::round(preStepPoint->GetMass() * 1000.f)]->GetParticleName() << '\n';

	detMtx.unlock();
	return true;
}
