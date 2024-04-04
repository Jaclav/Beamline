#include <iostream>
#include <fstream>
#include <chrono>
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4MTRunManager.hh"
#include "G4UIExecutive.hh"

#include "construction.hh"
#include "physics.hh"
#include "action.hh"

G4double *parameters;
std::fstream outFile;
std::map<int, G4ParticleDefinition*> massTable;//mass in KeV to particle data
std::map<int, int> particleCounts;//mass to particleCounts

/**
 * @param argc 1 when UI, 1 < when command line
 * @param argv
 * |   i   | parameter |  units  | default |
 * | :---: | :-------: | :-----: | :-----: |
 * |   0   |     L     |  (cm)   |   45    |
 * |   1   |    Pb     |   %m    |   100   |
 * |   2   |     E     | (Gev)   |   10    |
 */
int main(int argc, char** argv) {
	G4UIExecutive *ui = nullptr;
	G4double parametersDefault[] = {1, 100, 10, 0};
	parameters = parametersDefault;
	if(argc > 1)
		for(int i = 1; i < argc; i++)
			parameters[i - 1] = std::stod(argv[i]);
	else
		ui = new G4UIExecutive(argc, argv);

	std::time_t result = std::time(nullptr);
	std::string name = std::string(std::ctime(&result));
	name = name.substr(0, name.end() - name.begin() - 1);
	for(int i = 0; i < sizeof(parametersDefault) / sizeof(G4double); i++) {
		std::stringstream ss;
		ss << " " << parameters[i];
		name += ss.str();
	}
	for(int i = 0; i < name.size(); i++)
		if(name[i] == ' ')
			name[i] = '_';
	outFile.open(name + ".csv\0", std::ios::app);
	outFile << "# " << __TIME__ << __DATE__ << " Parameters:";
	for(int i = 0; i < sizeof(parametersDefault) / sizeof(G4double); i++)
		outFile << ' ' << parameters[i];
	outFile << "\n";

	G4RunManager *runManager;
	if(ui) {//use multithreading only in non gui mode
		runManager = new G4RunManager();
	}
	else {
		runManager = new G4MTRunManager();
		runManager->SetNumberOfThreads(15);
	}

	runManager->SetUserInitialization(new Construction());
	runManager->SetUserInitialization(new MyPhysicsList());
	runManager->SetUserInitialization(new MyAction());
	runManager->Initialize();

	G4UImanager *UImanager = G4UImanager::GetUIpointer();
	if(ui) {
		G4VisManager *visManager = new G4VisExecutive();
		visManager->SetVerboseLevel(G4VisManager::quiet);
		visManager->Initialize();

		UImanager->ApplyCommand("/control/execute vis.mac");
		ui->SessionStart();

		delete visManager;
		delete ui;
	}
	else {
		std::fstream file("cli.mac");
		if(!file.good())
			std::cerr << "ERROR: " << __LINE__ << __FILE__ << '\n';
		std::string str;
		while(std::getline(file, str)) {
			outFile << "# " << str << "\n";
		}
		UImanager->ApplyCommand("/control/execute cli.mac");
	}

	std::cout << "ParticleCounts neutrons: ";
	std::cout << particleCounts[(int)std::round(G4Neutron::Definition()->GetPDGMass() * 1000.f)] << '\n';
	for(auto it = massTable.begin(); it != massTable.end(); it++) {
		if(particleCounts[(int)std::round(it->second->GetPDGMass() * 1000.f)] != 0) {
			std::cout << ' ' << it->second->GetParticleName() << ' ' << particleCounts[(int)std::round(it->second->GetPDGMass() * 1000.f)];
			outFile << "# " << it->second->GetParticleName() << ' ' << particleCounts[(int)std::round(it->second->GetPDGMass() * 1000.f)] << '\n';
		}
	}
	std::cout << "\n";
	outFile.close();

	return 0;
}
