# Simulations for Beamline For schools 2024
Smiling Of Spallation Team, Poland\
We used standard nist AIR, tin, silicon, bizmuth, iron and lead.\
Our detectors, are all knowing, but as we wrote from proposal we can determine particle's name from its energy and velocity
GitHub didn't let us put all data files, because of their weights, so they are here: https://drive.google.com/drive/folders/1U2vgCLuIntWeLd-AVQ5JxnH0i5vrkNc-
## To run simulation:
mkdir build\
cmake .. -DGeant4_DIR=\<your geant4 path\>\
make\
cp ../*.mac #copy macro files\
./sim # to open visual mode\
./sim L A E # to open simulation mode with sample length L, sample material with atomic number A and beam energy E\
Output #!!!! Unknown  means that simulation created particle unknown to geant4 particle table
## files in data/ - our plots making scripts
in /sims catalog we have our simulation results in catalogs named after beam energy
| file                   | description                                                                                                          |                    parameters                     |
| :--------------------- | :------------------------------------------------------------------------------------------------------------------- | :-----------------------------------------------: |
| getPerpAndPara         | gives information how many neutrons or protons came through which detector and generates output for crossSections.py |                 type of particle                  |
| countsOfParticles.py   | gives information about how many counts corresponds to which energy or velocity                                      | file.csv detPerp/detPara Energy/Momentum/Velocity |
| crossSections.py       | gives plot of cross section versus energy                                                                            |         (gets data from sims/through.py)          |
| positionAndCounting.py | gives information about number and position of specific particle                                                     |        (gets data from sims/spallatedN.py)        |
| Z.py                   | gives information about where on Z axis particle was found, we can approximate mean free path from this              |                     file.csv                      |
## script.sh
It runs simulation for all energies and all lengths, creates folders named after beam energy
## csv files
They have all information from simulation, beam properties, all detections etc.\
Detection logs has following format:\
mass;charge;X;Y;Z;Kinetic Energy;particle's name;velocity\
Don't worry we didn't use unknown values (like charge or name) at all, they are here just for backward compatibility