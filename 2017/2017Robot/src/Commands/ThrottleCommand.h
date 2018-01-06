#ifndef ThrottleCommand_H
#define ThrottleCommand_H

#include "../CommandBase.h"
#include "../Subsystems/Chassis.h"

class ThrottleCommand : public CommandBase {
public:
	ThrottleCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	//Joystick *controller;
};

#endif  // ThrottleCommand_H
