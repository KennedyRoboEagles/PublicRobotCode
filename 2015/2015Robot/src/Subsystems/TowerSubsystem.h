#ifndef TowerSubsystem_H
#define TowerSubsystem_H

#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "SensorSubsystem.h"

class TowerSupervisorCommnad;

class TowerSubsystem: public Subsystem
{
private:
	SensorSubsystem *sensorSubsystem;
public:
	TowerSubsystem(SensorSubsystem *sensorSubsystem);
	void InitDefaultCommand();

	bool GetBottomLimit();
};

#endif
