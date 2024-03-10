#include <iostream>
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "construction.hh"
#include "physics.hh"
#include "action.hh"

int main(int argc, char** argv) {
	G4RunManager *runManager = new G4RunManager();
	runManager->SetUserInitialization(new Construction());
	runManager->SetUserInitialization(new MyPhysicsList());
	runManager->SetUserInitialization(new MyAction());
	runManager->Initialize();

	G4UIExecutive *ui = new G4UIExecutive(argc, argv);

	G4VisManager *visManager = new G4VisExecutive();
	visManager->Initialize();

	G4UImanager *UImanager = G4UImanager::GetUIpointer();
	UImanager->ApplyCommand("/vis/open TSG");//OGL causes error WHY?
	UImanager->ApplyCommand("/vis/viewer/set/viewpointVector -1 0 0.5");
	UImanager->ApplyCommand("/vis/viewer/set/autoRefresh true");

	UImanager->ApplyCommand("/vis/drawVolume");
	UImanager->ApplyCommand("/vis/scene/add/trajectories smooth");
	UImanager->ApplyCommand("/vis/scene/endOfEventAction accumulate");
	UImanager->ApplyCommand("/vis/scene/add/axes");

	UImanager->ApplyCommand("/run/beamOn 1000");

	// UImanager->ApplyCommand("control/execute vis.mac");

	ui->SessionStart();

	delete ui;
	delete visManager;

	return 0;
}
