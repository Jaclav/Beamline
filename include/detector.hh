#ifndef DETECTOR_HH
#define DETECTOR_HH

#include "G4VSensitiveDetector.hh"
#include "G4ParticleTable.hh"
#include "G4StepPoint.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include <fstream>
#include <map>

extern std::fstream outFile;
extern std::map<int, G4ParticleDefinition*> massTable;//mass in KeV to particle data
extern std::map<int, int> particleCounts;//mass to particleCounts

class MySensitiveDetector: public G4VSensitiveDetector {
public:
	MySensitiveDetector(G4String);
	~MySensitiveDetector();
private:
	virtual G4bool ProcessHits(G4Step*, G4TouchableHistory*);
	G4String mName;
};

#endif