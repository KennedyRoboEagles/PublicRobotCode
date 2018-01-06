#ifndef SensorSubsystem_H
#define SensorSubsystem_H

#include <Commands/Subsystem.h>
#include <AHRS.h>
#include <DigitalInput.h>
#include <Encoder.h>
#include <PowerDistributionPanel.h>
#include <Util/Pose.h>

using namespace frc;

class SensorSubsystem : public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

	PowerDistributionPanel *pdp;

	DigitalInput* climberIndex;

	Encoder* chassisLeftEncoder;
	Encoder* chassisRightEncoder;

	AnalogGyro *gyro;
	AHRS *imu;

public:
	SensorSubsystem();
	void InitDefaultCommand();

	Encoder* GetChassisLeftEncoder();
	Encoder* GetChassisRightEncoder();

	double GetChassisLeftCurrent();
	double GetChassisRightCurrent();

	bool GetClimberIndex();

	AnalogGyro* GetGyro();
	AHRS* GetIMU();

	PowerDistributionPanel* GetPDP();

	PIDSource* GetYawSource();
	double GetYaw();
	double GetYawRate();
	void ZeroYaw();

	void ResetPhysicalPose();
	Pose GetPhysicalPose();
};

#endif  // SensorSubsystem_H
