#include "MyMagneticField.hh"

#include <cmath>

MyMagneticField::MyMagneticField(G4double Bmax) {
	this->Bmax = Bmax;
}

MyMagneticField::~MyMagneticField() {

}

void MyMagneticField::GetFieldValue(const double Point[4], double *field) const
{
	//SRC: http://geant4.in2p3.fr/2007/prog/JohnApostolakis/EMField.pdf
	G4double r = std::sqrt(Point[0] * Point[0] + Point[1] * Point[1] + Point[2] * Point[2]);
	// field[0] = Bmax * r;
	// field[1] = Bmax / r;
	// field[2] = Bmax * r;
	field[1] = Bmax / r / tesla;
	// std::cout<<r;
	field[0] = 0;
	field[2] = 0;
	field[3] = 0;
}