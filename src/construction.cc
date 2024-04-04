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

	// pole magnetyczne
	// G4MagneticField *magField = new MyMagneticField(1.0 * tesla);
	// G4FieldManager* fieldMgr = new G4FieldManager();
	// G4MagneticField* magField = new	G4UniformMagField( G4ThreeVector(0, 1.35 * tesla, 0));
	// fieldMgr->SetDetectorField(magField);
	// fieldMgr->CreateChordFinder(magField);
	// logicalWorld->SetFieldManager(fieldMgr, true);

	// blok 4x4x10 of lead A=207.2 density=11.34
	//https://sci-hub.st/http://dx.doi.org/10.1080/10420150601045382
	G4double CPb = parameters[1], L = parameters[0];

	G4Material* leadBlock = new G4Material("leadBlock", 82, 207.976 * g / mole, dPb * g / cm3); //https://www.ciaaw.org/lead.htm
	outFile << "# L=" << L << "cm " << leadBlock->GetA() / g << "Pb=" << CPb << "%m d=" << dPb << '\n';
	G4Box *sLeadBlock = new G4Box("solidBlock", 0.02 * m, .02 * m, L / 200. * m);
	G4LogicalVolume *lLeadBlock = new G4LogicalVolume(sLeadBlock, leadBlock, "logicalBlock");
	G4VPhysicalVolume *pLeadBlock = new G4PVPlacement(0, G4ThreeVector(0, 0, 0), lLeadBlock, "physBlock", logicalWorld, false, 0, false);

	// G4Tubs *sCircDetector = new G4Tubs("solidDetector", 0.05 * m, 0.06 * m, 0.3 * m, 90 * deg, 3600 * deg);
	// lCircDet = new G4LogicalVolume(sCircDetector, worldMat, "logicDetector");
	// G4VPhysicalVolume *physCircDetector = new G4PVPlacement(0, G4ThreeVector(0, 0, 0), lCircDet, "physDetector", logicalWorld, false, 1, false); //pSurfChk should be true

	// G4Box *solidDetector = new G4Box("solidDetector", 0.005 * m,  0.01 * m, 0.005 * m);
	// lPlateDet = new G4LogicalVolume(solidDetector, worldMat, "logicDetector");
	// for(G4int i = 0; i < 100; i++) {
	// 	for(G4int j = 0; j < 100; j++) {
	// 		G4VPhysicalVolume *physDetector = new G4PVPlacement(0, G4ThreeVector( -0.5 * m + (i + 0.5)*m / 100,  -0.5 * m + (j + 0.5)*m / 100, 1.5 * m),
	// 		        lPlateDet, "physDetector", logicalWorld, false, i + j * 100, false); //pSurfChk should be true
	// 	}
	// }

	G4Box *sDetPara = new G4Box("solidDetector", 0.01 * m, 0.15 * m,  0.15 * m);
	lDetPara = new G4LogicalVolume(sDetPara, worldMat, "logicDetector");
	G4VPhysicalVolume *pDetPara = new G4PVPlacement(0, G4ThreeVector(0.11 * m, 0, -parameters[3] * m), lDetPara, "physDetector", logicalWorld, false, 1, false); //pSurfChk should be true

	G4Box *sDetPerp = new G4Box("solidDetector", 0.15 * m,  0.15 * m, 0.01 * m);
	lDetPerp = new G4LogicalVolume(sDetPerp, worldMat, "logicDetector");
	G4VPhysicalVolume *pDetPerp = new G4PVPlacement(0, G4ThreeVector(0, 0, 0.2 * m), lDetPerp, "physDetector", logicalWorld, false, 1, false); //pSurfChk should be true

	return physWorld;
}

void Construction::ConstructSDandField() {
	// MySensitiveDetector *senDet2 = new MySensitiveDetector("Circ");
	// lCircDet->SetSensitiveDetector(senDet2);

	MySensitiveDetector *detPara = new MySensitiveDetector("detPara");
	lDetPara->SetSensitiveDetector(detPara);

	MySensitiveDetector *detPerp = new MySensitiveDetector("detPerp");
	lDetPerp->SetSensitiveDetector(detPerp);
}