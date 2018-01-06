#ifndef ThrottleTrigger_H
#define ThrottleTrigger_H

#include <Buttons/Trigger.h>
#include <Joystick.h>

class ThrottleTrigger : public frc::Trigger {
private:
	frc::Joystick *joy;
public:
	ThrottleTrigger(frc::Joystick *joy);
	virtual bool Get();
};

#endif  // ThrottleTrigger_H
