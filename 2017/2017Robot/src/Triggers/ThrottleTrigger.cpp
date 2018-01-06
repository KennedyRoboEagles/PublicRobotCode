#include <Triggers/ThrottleTrigger.h>

ThrottleTrigger::ThrottleTrigger(frc::Joystick *joy) {
	this->joy = joy;
}

bool ThrottleTrigger::Get() {
	return joy->GetRawAxis(3) > 0.05;
}

