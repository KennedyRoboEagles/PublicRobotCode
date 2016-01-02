#ifndef DriveLaterallyTimeCommand_H
#define DriveLaterallyTimeCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class DriveLaterallyTimeCommand: public CommandBase
{
private:
	float time;
	float speed;
	Timer *timer;
public:
	DriveLaterallyTimeCommand(float time, float speed);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
