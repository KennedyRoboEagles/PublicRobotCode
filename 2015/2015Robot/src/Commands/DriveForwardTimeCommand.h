#ifndef DriveForwardTimeCommand_H
#define DriveForwardTimeCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class DriveForwardTimeCommand: public CommandBase
{
private:
	float time;
	float speed;
	Timer *timer;
public:
	DriveForwardTimeCommand(float time, float speed);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
