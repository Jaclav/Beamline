#include "detector.hh"
#include <mutex>

static std::mutex detMtx;
static std::mutex initMtx;

MySensitiveDetector::MySensitiveDetector(G4String name, G4bool killAfter): G4VSensitiveDetector(name) {
	initMtx.lock();
	mName = name;
	this->killAfter = killAfter;
	G4ParticleTable *pt = G4ParticleTable::GetParticleTable();
	for(int i = 0; i < pt->size(); i++)
		massTable[(int)std::round(pt->FindParticle(pt->GetParticleName(i))->GetPDGMass() * 1000)] = pt->FindParticle(pt->GetParticleName(i));
	initMtx.unlock();
}

MySensitiveDetector::~MySensitiveDetector() {
}

G4bool MySensitiveDetector::ProcessHits(G4Step* aStep, G4TouchableHistory *ROhist) {
	G4Track *track = aStep->GetTrack();
	G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
	G4StepPoint *postStepPoint = aStep->GetPostStepPoint();

	if(killAfter)
		track->SetTrackStatus(fStopAndKill);

	if(!massTable.count((int)std::round(preStepPoint->GetMass() * 1000.f))) {
		//IDK why this happens
		std::cerr << "#!!!!! UNKOWN:" <<
		          preStepPoint->GetCharge() << "C\t" <<
		          preStepPoint->GetMass() / amu_c2 << "u(" << preStepPoint->GetMass() << "MeV)\t" <<
		          preStepPoint->GetKineticEnergy() << '\n';
		return true;
	}

	if(massTable[(int)std::round(preStepPoint->GetMass() * 1000.f)]->GetParticleName() == "nu_mu")//don't put rubbish data
		return false;

	detMtx.lock();
	particleCounts[(int)std::round(preStepPoint->GetMass() * 1000.f)]++;

	outFile << preStepPoint->GetMass() << ';' <<
	        preStepPoint->GetCharge() << ';' <<
	        preStepPoint->GetPosition().x() << ';' <<//it is in mm
	        preStepPoint->GetPosition().y() << ';' <<//it is in mm
	        preStepPoint->GetPosition().z() << ';' <<//it is in mm
	        preStepPoint->GetKineticEnergy() << ';' <<
	        massTable[(int)std::round(preStepPoint->GetMass() * 1000.f)]->GetParticleName() << ';' <<
	        mName << ';' <<
	        preStepPoint->GetVelocity() << '\n';//in 1000 km/s

	detMtx.unlock();
	return true;
}
