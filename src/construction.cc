#include "construction.hh"

Construction::Construction() {

}

Construction::~Construction() {

}

G4VPhysicalVolume *Construction::Construct() {
	G4NistManager *nist = G4NistManager::Instance();

	//powietrze 1x1x1
	G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");
	G4Box *solidWorld = new G4Box("solidWorld", .2 * m, .2 * m, .4 * m);
	G4LogicalVolume *logicalWorld = new G4LogicalVolume(solidWorld, worldMat, "logicalW");
	G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0, 0, 0), logicalWorld, "physWorld", 0, false, 0, true);

	// blok 4x4x10 of lead A=207.2 density=11.34
	//https://sci-hub.st/http://dx.doi.org/10.1080/10420150601045382
	G4double A = parameters[1], L1 = parameters[0];
	switch((int)parameters[1]) {
	case 82:
		density = 11.34;
		break;
	case 14:
		density = 28.09;
		break;
	case 50:
		density = 7.31;
		break;
	case 26:
		density = 7.874;
		break;
	case 83:
		density = 9.78;
		break;
	case 74:
		density = 19.25;
		break;
	default:
		exit(-1);
	}
	G4Material* leadBlock = new G4Material("leadBlock", parameters[1], 0, density * g / cm3);
	outFile << "# L1=" << L1 << "cm A=" << leadBlock->GetA() / g << " Z=" << A << " d=" << density << '\n';

	G4Box *sLeadBlock = new G4Box("solidBlock", 0.02 * m, .02 * m, L1 / 200. * m);
	G4LogicalVolume *lLeadBlock = new G4LogicalVolume(sLeadBlock, leadBlock, "lBlock");
	G4VPhysicalVolume *pLeadBlock = new G4PVPlacement(0, G4ThreeVector(0, 0, (0.15  - L1 / 200 /*- 0.01*/) * m),
	        lLeadBlock, "physBlock", logicalWorld, false, 0, false);

	G4Box *sDetPara = new G4Box("solidDetector", 0.01 * m, 0.15 * m,  0.15 * m);
	lDetPara = new G4LogicalVolume(sDetPara, worldMat, "logicDetector");
	G4VPhysicalVolume *pDetPara = new G4PVPlacement(0, G4ThreeVector(0.16 * m, 0, 0), lDetPara, "physDetector", logicalWorld, false, 1, false); //pSurfChk should be true

	G4Box *sDetPerp = new G4Box("solidDetector", 0.15 * m,  0.15 * m, 0.01 * m);
	lDetPerp = new G4LogicalVolume(sDetPerp, worldMat, "logicDetector");
	G4VPhysicalVolume *pDetPerp = new G4PVPlacement(0, G4ThreeVector(0, 0, 0.16 * m), lDetPerp, "physDetector", logicalWorld, false, 1, false); //pSurfChk should be true

	G4Box *sDetFirst = new G4Box("solidDetector", 0.15 * m,  0.15 * m, 0.01 * m);
	lDetFirst = new G4LogicalVolume(sDetFirst, worldMat, "logicDetector");
	G4VPhysicalVolume *pDetFirst = new G4PVPlacement(0, G4ThreeVector(0, 0, -0.3 * m), lDetFirst, "physDetector", logicalWorld, false, 1, false); //pSurfChk should be true

	return physWorld;
}

void Construction::ConstructSDandField() {
	MySensitiveDetector *detPara = new MySensitiveDetector("detPara");
	lDetPara->SetSensitiveDetector(detPara);

	MySensitiveDetector *detPerp = new MySensitiveDetector("detPerp");
	lDetPerp->SetSensitiveDetector(detPerp);

	MySensitiveDetector *detFirst = new MySensitiveDetector("detFirst", false);
	lDetFirst->SetSensitiveDetector(detFirst);
}