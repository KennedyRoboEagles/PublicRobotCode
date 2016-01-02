#ifndef SensorSubsystem_H
#define SensorSubsystem_H

#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "../IMU/IMU.h"

class SensorSubsystem: public Subsystem
{
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	PowerDistributionPanel *powerDistributionPanel;

	Encoder *leftDriveEncoder;
	Encoder *rightDriveEncoder;
	Encoder	*centerDriveEncoder;

	SerialPort *serialPort;
	IMU *imu;
public:
	SensorSubsystem();
	void InitDefaultCommand();

	IMU *GetIMU();
	float GetIMUYawRad();

	Encoder *GetLeftDriveEncoder();
	Encoder *GetRightDriveEncoder();
	Encoder *GetCenterDriveEncoder();

	// PDP operations
	double GetChannelCurrent(uint8_t channel);

};

#endif
