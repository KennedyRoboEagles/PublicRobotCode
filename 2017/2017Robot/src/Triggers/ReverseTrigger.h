#ifndef ReverseTrigger_H
#define ReverseTrigger_H

#include <Buttons/Trigger.h>
#include <Joystick.h>

class ReverseTrigger : public Trigger {
private:
	Joystick *joy;
public:
	ReverseTrigger(frc::Joystick *joy);
	virtual bool Get();
};

#endif  // ReverseTrigger_H
