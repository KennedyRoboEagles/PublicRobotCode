#ifndef TestDaisyFIlterJoystickCommand_H
#define TestDaisyFIlterJoystickCommand_H

#include "../../CommandBase.h"
#include "WPILib.h"
#include "../../DiasyFilter/DaisyFilter.h"

class TestDaisyFIlterJoystickCommand: public CommandBase
{
private:
	DaisyFilter *filter;
public:
	TestDaisyFIlterJoystickCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
