#ifndef ClimberSubsystem_H
#define ClimberSubsystem_H

#include <Commands/Subsystem.h>
#include <SpeedController.h>
#include "Subsystems/SensorSubsystem.h"


class ClimberSubsystem : public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	SpeedController *controller0;
	SpeedController *controller1;
	SensorSubsystem *sensorSubsystem;
public:
	ClimberSubsystem(SensorSubsystem *sensorSubsystem);
	void InitDefaultCommand();
	void Stop();
	void Set(double value);
	bool AtIndex();
};

#endif  // ClimberSubsystem_H
