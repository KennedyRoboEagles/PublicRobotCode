#include "ReverseTrigger.h"

ReverseTrigger::ReverseTrigger(frc::Joystick *joy) {
	this->joy = joy;
}

bool ReverseTrigger::Get() {
//	printf("2:%f\n",joy->GetRawAxis(2));
	return joy->GetRawAxis(2) > 0.05;
}

