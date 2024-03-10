#include "action.hh"

MyAction::MyAction () {

}

MyAction ::~MyAction () {
}

void MyAction::Build() const {
	MyGenerator *generator = new MyGenerator();
	SetUserAction(generator);
}
