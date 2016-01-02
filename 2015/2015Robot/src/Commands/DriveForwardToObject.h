#ifndef DriveForwardToObject_H
#define DriveForwardToObject_H

#include "../CommandBase.h"
#include "WPILib.h"

class DriveForwardToObject: public CommandBase
{
public:
	DriveForwardToObject(double distance);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	// Distance from object to drive
	double distance;
	const double deltaInches = 1;
};

#endif
