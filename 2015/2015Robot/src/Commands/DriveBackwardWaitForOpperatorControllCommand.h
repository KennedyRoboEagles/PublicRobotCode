#ifndef DriveBackwardWaitForOpperatorControllCommand_H
#define DriveBackwardWaitForOpperatorControllCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class DriveBackwardWaitForOpperatorControllCommand: public CommandBase
{
private:
	Timer *timer;
	float timeOut;
	float speed;

	bool isDriverPresent();
public:
	DriveBackwardWaitForOpperatorControllCommand(float timeOut, float speed);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
