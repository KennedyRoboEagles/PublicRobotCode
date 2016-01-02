#ifndef SENSORSUBSYSTEM_H
#define SENSORSUBSYSTEM_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author nowireless
 */
class SensorSubsystem: public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	Encoder *leftDriveEncoder;
	Encoder *rightDriveEncoder;
	
	Gyro *horizontalGyro;
	
	DigitalInput *throwerLowLimtSwitch;
	DigitalInput *throwerHighLimitSwitch;
	
	DigitalInput *intakeLowLimitSwitch;
	DigitalInput *intakeHighLimitSwitch;
	DigitalInput *intakeStandbyLimitSwitch;
	DigitalInput *intakeOpenLimitSwitch;
	DigitalInput *intakeBallSensor;
	DigitalInput *intakeBallSensorTwo;
	
	AnalogChannel *throwerRangeFinder;
	
	Solenoid *intakeBallSensorPower;
	Solenoid *intakeBallSensorTwoPower;
	
public:
	SensorSubsystem();
	void InitDefaultCommand();
	
	void Start();
	void Stop();
	
	Encoder *GetLeftDriveEncoder();
	int GetLeftDriveEncoderCount();
	Encoder *GetRightDriveEncoder();
	int GetRightDriveEncoderCount();
	
	
	Gyro *GetHorizontalGyro();
	float GetHorizontalGyroAngle();
	
	bool GetThrowerLowLimt();
	bool GetThrowerHighLimit();
	
	bool GetIntakeLowLimit();
	bool GetIntakeHighLimit();
	bool GetIntakeStandbyLimit();
	bool GetIntakeBallSensor();
	bool GetIntakeBallTwoSensor();
	bool GetIntakeOpenLimit();
	
	float GetRangeFinderDistance();
	
};

#endif
