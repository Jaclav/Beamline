#include "construction.hh"

Construction::Construction() {

}

Construction::~Construction() {

}

G4VPhysicalVolume *Construction::Construct() {
	G4NistManager *nist = G4NistManager::Instance();

	//powietrze 1x1x1
	G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");
	G4Box *solidWorld = new G4Box("solidWorld", 1.5 * m, 1.5 * m, 1.5 * m);
	G4LogicalVolume *logicalWorld = new G4LogicalVolume(solidWorld, worldMat, "logicalW");
	G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0, 0, 0), logicalWorld, "physWorld", 0, false, 0, true);

	// //pole magnetyczne
	// G4FieldManager* fieldMgr = G4TransportationManager::GetTransportationManager()->GetFieldManager();
	// G4MagneticField *magField = new MyMagneticField(1.0 * tesla);
	// // G4MagneticField* magField = new	G4UniformMagField( G4ThreeVector(0, 1.0 * tesla, 0));
	// fieldMgr->SetDetectorField(magField);
	// fieldMgr->CreateChordFinder(magField);
	// logicalWorld->SetFieldManager(fieldMgr, true);

	// blok 4x4x10
	//https://sci-hub.st/http://dx.doi.org/10.1080/10420150601045382
	G4double CPb = parameters[1], L = parameters[0];
	outFile << "# L=" << L << "cm Pb=" << CPb << "%m d=" << 1 / ((CPb / 100) / dPb + ((1 - CPb / 100) ) / dBi) << '\n';
	G4Material *Block = new G4Material("Block", 1 / ((CPb / 100) / dPb + ((1 - CPb / 100) ) / dBi)*g / cm3, 2);
	Block->AddElement(nist->FindOrBuildElement("Pb"), CPb * perCent) ;
	Block->AddElement(nist->FindOrBuildElement("W"), (100 - CPb)* perCent) ;

	G4Box *solidBlock = new G4Box("solidBlock", 0.02 * m, .02 * m, L / 200. * m);
	G4LogicalVolume *logicalBlock = new G4LogicalVolume(solidBlock, Block, "logicalBlock");
	G4VPhysicalVolume *physBlock = new G4PVPlacement(0, G4ThreeVector(0, 0, solidBlock->GetZHalfLength()), logicalBlock, "physBlock", logicalWorld, false, 0, false);

	//detektory 1x1x2
	G4Box *solidDetector = new G4Box("solidDetector", 0.005 * m,  0.01 * m, 0.005 * m);
	logicDetector = new G4LogicalVolume(solidDetector, worldMat, "logicDetector");
	for(G4int i = 0; i < 100; i++) {
		for(G4int j = 0; j < 100; j++) {
			G4VPhysicalVolume *physDetector = new G4PVPlacement(0, G4ThreeVector(-0.5 * m + (i + 0.5)*m / 100, 0.2 * m,  -0.5 * m + (j + 0.5)*m / 100), logicDetector, "physDetector", logicalWorld, false, i + j * 100, false);//pSurfChk should be true
		}
	}

	return physWorld;
}

void Construction::ConstructSDandField() {
	MySensitiveDetector *senDet = new MySensitiveDetector("Sens det");
	logicDetector->SetSensitiveDetector(senDet);
}