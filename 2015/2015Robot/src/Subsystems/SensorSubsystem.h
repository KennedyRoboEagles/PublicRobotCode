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
	DigitalInput *towerLowLimit;

	DigitalInput *toteDetector;

	AnalogInput *chassisUltrasonicLeft;
	AnalogInput *chassisUltrasonicRight;
	AnalogInput *chassisUltrasonicCenter;

	// Lower Car
	AnalogInput *lowerCarForceSensor;
	DigitalInput *lowerCarTopLimit;
	Encoder *lowerCarManipulatorEncoder;
	Encoder *lowerCarVerticalPositionEncoder;

	//Upper Car
	AnalogInput *upperCarForceSensor;
	DigitalInput *upperCarTopLimit;
	Encoder *upperCarEncoder;

	Encoder *leftDriveEncoder;
	Encoder *rightDriveEncoder;
	Encoder *centerDriveEncoder;

	SerialPort *serialPort;
	IMU *imu;
public:
	SensorSubsystem();
	void InitDefaultCommand();

	IMU *GetIMU();
	float GetIMUYawRad();

	bool IsTotePresentAtChassis();

	float GetRobotToToteAngle();
	float GetRobotToToteAngleDeg();

	float GetChassisUltrasonicLeftDistance();
	float GetChassisUltrasonicRightDistance();
	float GetChassisUltrasonicCenterDistance();

	bool TowerLowLimit();

	bool GetLowerCarTopLimit();
	Encoder *GetLowerCarManipulatorEncoder();
	Encoder *GetLowerCarVerticalPositionEncoder();
	float GetLowerCarOpenDistance();
	AnalogInput *GetLowerCarForceInput();
	float GetLowerCarForce();

	bool GetUpperCarTopLimit();
	Encoder *GetUpperCarVerticalPositionEncoder();
	AnalogInput *GetUpperCarForceInput();
	float GetUpperCarForceInPounds();

	Encoder *GetLeftDriveEncoder();
	Encoder *GetRightDriveEncoder();
	Encoder *GetCenterDriveEncoder();

	// PDP operations
	double GetChannelCurrent(uint8_t channel);

};

#endif
