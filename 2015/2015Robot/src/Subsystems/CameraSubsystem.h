#ifndef CameraSubsystem_H
#define CameraSubsystem_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class CameraSubsystem: public Subsystem
{
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	Servo *cameraServo;
	Solenoid *ledRing;
public:
	CameraSubsystem();
	void InitDefaultCommand();

	void SetLedRingState(bool state);
	void SetCameraTilt(double position);
	void SetCameraTiltRawServo(float position);
};

#endif
