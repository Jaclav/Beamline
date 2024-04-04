#ifndef CONSTRUCTION_HPP
#define CONSTRUCTION_HPP

#include "G4VUserDetectorConstruction.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4UIExecutive.hh"
#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"

#include "G4FieldManager.hh"
#include "G4MagneticField.hh"
#include "G4UniformMagField.hh"
#include "G4TransportationManager.hh"

#include "detector.hh"
#include "MyMagneticField.hh"
#include <fstream>

extern std::fstream outFile;
extern G4double *parameters;
constexpr G4double dBi = 9.78, dPb = 11.34;

class Construction : public G4VUserDetectorConstruction {
public:
	Construction();
	~Construction();
	virtual G4VPhysicalVolume *Construct();
private:
	G4LogicalVolume *lCircDet;
	G4LogicalVolume *lPlateDet;
	G4LogicalVolume *lDetPara;
	G4LogicalVolume *lDetPerp;
	virtual void ConstructSDandField();
};

#endif //CONSTRUCTION_HPP
