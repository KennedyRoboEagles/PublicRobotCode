#ifndef UpperTowerSupervisor_H
#define UpperTowerSupervisor_H

#include "../CommandBase.h"
#include "WPILib.h"

class UpperTowerSupervisorCommand: public CommandBase
{
private:
	PIDController *controller;
	Timer *timer;
	float setpoint;
	bool paused;
	int pausedSetpoint;
	bool isCalibrated;

	void run();
	void cleanUp();
public:
	UpperTowerSupervisorCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
