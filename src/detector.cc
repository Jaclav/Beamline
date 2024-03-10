#include "detector.hh"

MySensitiveDetector::MySensitiveDetector(G4String name): G4VSensitiveDetector(name) {

}

MySensitiveDetector::~MySensitiveDetector() {

}

G4bool MySensitiveDetector::ProcessHits(G4Step* aStep, G4TouchableHistory *ROhist) {
	G4Track *track = aStep->GetTrack();
	track->SetTrackStatus(fStopAndKill);
	G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
	G4StepPoint *postStepPoint = aStep->GetPostStepPoint();

	if(std::round(preStepPoint->GetMass()) == 940) {
		std::cerr << "NN\n";
	}
	std::cerr << preStepPoint->GetMass() << ";" <<
	          preStepPoint->GetCharge() << ";" <<
	          preStepPoint->GetPosition().x() << ";" <<
	          preStepPoint->GetPosition().y() << ";" <<
	          preStepPoint->GetKineticEnergy() << "\n";
	return true;
}
