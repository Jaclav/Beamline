#include "construction.hh"

Construction::Construction() {

}

Construction::~Construction() {

}

G4VPhysicalVolume *Construction::Construct() {
	G4NistManager *nist = G4NistManager::Instance();

	//powietrze 1x1x1
	G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");
	G4Box *solidWorld = new G4Box("solidWorld", .2 * m, .2 * m, .6 * m);
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
	G4double CPb = parameters[1], L1 = parameters[0], L2 = parameters[4];
	G4Material* leadBlock = new G4Material("leadBlock", 82, 207.976 * g / mole, dPb * g / cm3); //https://www.ciaaw.org/lead.htm
	outFile << "# L1=" << L1 << "cm " << leadBlock->GetA() / g << "Pb=" << CPb << "%m d=" << dPb << "L2=" << L2 << '\n';

	G4Box *sLeadBlock = new G4Box("solidBlock", 0.02 * m, .02 * m, L1 / 200. * m);
	G4LogicalVolume *lLeadBlock = new G4LogicalVolume(sLeadBlock, leadBlock, "lBlock");
	G4VPhysicalVolume *pLeadBlock = new G4PVPlacement(0, G4ThreeVector(0, 0, (0.15  - L1 / 200 /*- 0.01*/) * m),
	        lLeadBlock, "physBlock", logicalWorld, false, 0, false);

	G4Box *sLeadBlock2 = new G4Box("solidBlock", 0.02 * m, .02 * m, L2 / 200. * m);
	G4LogicalVolume *lLeadBlock2 = new G4LogicalVolume(sLeadBlock2, leadBlock, "lBlock2");
	G4VPhysicalVolume *pLeadBlock2 = new G4PVPlacement(0, G4ThreeVector(0, 0, (0.17 + L2 / 200)*m), lLeadBlock2, "physBlock2", logicalWorld, false, 0, false);

	G4Box *sDetPara = new G4Box("solidDetector", 0.01 * m, 0.15 * m,  0.15 * m);
	lDetPara = new G4LogicalVolume(sDetPara, worldMat, "logicDetector");
	G4VPhysicalVolume *pDetPara = new G4PVPlacement(0, G4ThreeVector(0.16 * m, 0, 0), lDetPara, "physDetector", logicalWorld, false, 1, false); //pSurfChk should be true

	G4Box *sDetPerp = new G4Box("solidDetector", 0.15 * m,  0.15 * m, 0.01 * m);
	lDetPerp = new G4LogicalVolume(sDetPerp, worldMat, "logicDetector");
	G4VPhysicalVolume *pDetPerp = new G4PVPlacement(0, G4ThreeVector(0, 0, 0.16 * m), lDetPerp, "physDetector", logicalWorld, false, 1, false); //pSurfChk should be true


	G4Box *sDetEnd = new G4Box("solidDetector", 0.01 * m, 0.15 * m,  0.15 * m);
	lDetEnd = new G4LogicalVolume(sDetEnd, worldMat, "logicDetector");
	G4VPhysicalVolume *pDetEnd = new G4PVPlacement(0, G4ThreeVector(0.16 * m, 0, parameters[3] * m), lDetEnd, "physDetector", logicalWorld, false, 1, false); //pSurfChk should be true

	// G4Box *sDetEnd = new G4Box("solidDetector", 0.15 * m,  0.15 * m, 0.01 * m);
	// lDetEnd = new G4LogicalVolume(sDetEnd, worldMat, "logicDetector");
	// G4VPhysicalVolume *pDetEnd = new G4PVPlacement(0, G4ThreeVector(0, 0, parameters[3] * m), lDetEnd, "physDetector", logicalWorld, false, 1, false); //pSurfChk should be true

	return physWorld;
}

void Construction::ConstructSDandField() {
	MySensitiveDetector *detPara = new MySensitiveDetector("detPara");
	lDetPara->SetSensitiveDetector(detPara);

	MySensitiveDetector *detPerp = new MySensitiveDetector("detPerp", false);
	lDetPerp->SetSensitiveDetector(detPerp);

	MySensitiveDetector *detEnd = new MySensitiveDetector("detEnd");
	lDetEnd->SetSensitiveDetector(detEnd);
}