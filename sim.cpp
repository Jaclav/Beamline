#include <iostream>
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "construction.hh"
#include "physics.hh"
#include "action.hh"

G4double CPb = 0;

int main(int argc, char** argv) {
	G4UIExecutive *ui = nullptr;
	if(argc > 1)
		CPb = std::stoi(argv[1]);
	else
		ui = new G4UIExecutive(argc, argv);

	G4RunManager *runManager = new G4RunManager();
	runManager->SetUserInitialization(new Construction());
	runManager->SetUserInitialization(new MyPhysicsList());
	runManager->SetUserInitialization(new MyAction());
	runManager->Initialize();

	G4VisManager *visManager;
	G4UImanager *UImanager = G4UImanager::GetUIpointer();
	if(ui) {
		visManager = new G4VisExecutive();
		visManager->Initialize();

		UImanager->ApplyCommand("/vis/open TSG");//OGL causes error WHY?
		UImanager->ApplyCommand("/vis/viewer/set/viewpointVector -1 0 0.5");
		UImanager->ApplyCommand("/vis/viewer/set/autoRefresh true");

		UImanager->ApplyCommand("/vis/drawVolume");
		UImanager->ApplyCommand("/vis/scene/add/trajectories smooth");
		UImanager->ApplyCommand("/vis/scene/endOfEventAction accumulate");
		UImanager->ApplyCommand("/vis/scene/add/axes");
	}
	else
		UImanager->ApplyCommand("/run/beamOn 1000");

	// UImanager->ApplyCommand("control/execute vis.mac");
	if(ui) {
		ui->SessionStart();
		delete visManager;
		delete ui;
	}

	return 0;
}
