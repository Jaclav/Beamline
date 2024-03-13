#ifndef MY_MAGNETIC
#define MY_MAGNETIC

#include "G4MagneticField.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"

class MyMagneticField: public G4MagneticField {
public:
	MyMagneticField(G4double Bmax);
	~MyMagneticField() override;
	void GetFieldValue(const G4double yTrack[4],
	                   G4double* MagField) const override;
private:
	G4double Bmax;
};

#endif