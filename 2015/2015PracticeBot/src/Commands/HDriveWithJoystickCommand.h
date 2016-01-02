#ifndef HDriveWithJoystickCommand_H
#define HDriveWithJoystickCommand_H

#include "../CommandBase.h"
#include "WPILib.h"
#include "../DiasyFilter/DaisyFilter.h"

class HDriveWithJoystickCommand: public CommandBase
{
private:
	DaisyFilter *zFilter;
public:
	HDriveWithJoystickCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
