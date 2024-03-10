#ifndef ACTION_HPP
#define ACTION_HPP

#include "G4VUserActionInitialization.hh"
#include "generator.hh"

class MyAction : public G4VUserActionInitialization {
public:
	MyAction();
	~MyAction();
	virtual void Build() const;
};

#endif //ACTION_HPP
