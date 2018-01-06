#ifndef DriveWithJoystickCommand_H
#define DriveWithJoystickCommand_H

#include "../CommandBase.h"

class DriveWithJoystickCommand : public CommandBase {
public:
	DriveWithJoystickCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // DriveWithJoystickCommand_H
