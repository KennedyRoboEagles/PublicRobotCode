#ifndef DriveDistanceCommand_H
#define DriveDistanceCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class DriveDistanceCommand: public CommandBase
{
private:
	float distance;
	float error;
	DaisyFilter *filter;
public:
	DriveDistanceCommand(float distance);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
