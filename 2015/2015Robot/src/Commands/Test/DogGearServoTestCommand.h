#ifndef DogGearServoTestCommand_H
#define DogGearServoTestCommand_H

#include "../../CommandBase.h"
#include "WPILib.h"

class DogGearServoTestCommand: public CommandBase
{
public:
	DogGearServoTestCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
