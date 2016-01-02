#ifndef Chassis_H
#define Chassis_H

#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "DiasyFilter/DaisyFilter.h"

class Chassis: public Subsystem
{
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	DaisyFilter *leftFilter;
	DaisyFilter *rightFilter;
	DaisyFilter *centerFilter;
	SpeedController *leftSpeedController;
	SpeedController *rightSpeedController;
	SpeedController *centerSpeedController;
	RobotDrive *drive;

	float limit(float val);

public:
	Chassis();
	void InitDefaultCommand();

	void Stop();
	RobotDrive *GetDrive();

	void FilteredLeft(float y);
	void FilteredRight(float y);
	void FilteredCenter(float x);
	void FilteredArcade(float move, float rotate, bool squaredInputs);

	void ResetFilters();
	void ResetFilters(float leftGain, float rightGain, float centerGain);

	SpeedController *GetCenterSpeedController();
};

#endif
