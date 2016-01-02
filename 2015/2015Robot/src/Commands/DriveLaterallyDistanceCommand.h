#ifndef DriveDistanceCommand_H
#define DriveDistanceCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class DriveLaterallyDistanceCommand: public CommandBase
{
private:
	float distance;
	float error;
	DaisyFilter *filter;
public:
	DriveLaterallyDistanceCommand(float distance);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
