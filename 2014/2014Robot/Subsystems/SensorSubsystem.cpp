#include "SensorSubsystem.h"
#include "../Robotmap.h"
#include "../Commands/SensorUpdateCommand.h"

SensorSubsystem::SensorSubsystem() : Subsystem("SensorSubsystem") {
	this->leftDriveEncoder	= new Encoder(DRIVE_ENCODER_LEFT_A, DRIVE_ENCODER_LEFT_B, Encoder::k4X);
	this->leftDriveEncoder->SetPIDSourceParameter(Encoder::kDistance);
	this->leftDriveEncoder->SetDistancePerPulse(1);
	this->leftDriveEncoder->SetMaxPeriod(1.0);
	this->leftDriveEncoder->Reset();
	this->leftDriveEncoder->Start();
	
	this->rightDriveEncoder	= new Encoder(DRIVE_ENCODER_RIGHT_A, DRIVE_ENCODER_RIGHT_B, Encoder::k4X);
	this->rightDriveEncoder->SetPIDSourceParameter(Encoder::kDistance);
	this->rightDriveEncoder->SetDistancePerPulse(1.0);
	this->rightDriveEncoder->Reset();
	this->rightDriveEncoder->Start();
	
	this->throwerLowLimtSwitch		= new DigitalInput(THROWER_LOW_LIMIT_SWITCH);
	this->throwerHighLimitSwitch	= new DigitalInput(THROWER_HIGH_LIMIT_SWITCH);
	this->intakeLowLimitSwitch		= new DigitalInput(INTAKE_LOW_LIMIT_SWITCH);
	this->intakeHighLimitSwitch		= new DigitalInput(INTAKE_HIGH_LIMIT_SWITCH);
	this->intakeStandbyLimitSwitch	= new DigitalInput(INTAKE_STANDBY_LIMIT_SWITCH);
	this->intakeBallSensor			= new DigitalInput(INTAKE_BALL_SENSOR);
	this->intakeBallSensorTwo		= new DigitalInput(INTAKE_BALL_SENSOR_TWO);
	this->intakeOpenLimitSwitch		= new DigitalInput(INTAKE_OPEN_LIMIT_SWICH);
	
	this->intakeBallSensorPower	= new Solenoid(LED_MODULE, INTAKE_BALL_SENSOR_POWER);
	this->intakeBallSensorTwoPower = new Solenoid(LED_MODULE, INTAKE_BALL_SENSOR_TWO_POWER);
	
	this->throwerRangeFinder = new AnalogChannel(THROWER_RANGE_FINDER);
	
	this->horizontalGyro = new Gyro(GYRO_HORIZONTAL);
}
    
void SensorSubsystem::InitDefaultCommand() {
	SetDefaultCommand(new SensorUpdateCommand());
}


// Put methods for controlling this subsystem
// here. Call these from Commands.

void SensorSubsystem::Start() {
	if(this->leftDriveEncoder != NULL) {
		this->leftDriveEncoder->Start();
	}
	if(this->rightDriveEncoder != NULL) {
		this->rightDriveEncoder->Start();
	}
	if(this->intakeBallSensorTwoPower != NULL) {
		this->intakeBallSensorTwoPower->Set(true);
	}
	if (this->intakeBallSensorPower != NULL) {
		this->intakeBallSensorPower->Set(true);
	}
}

void SensorSubsystem::Stop() {
	if(this->leftDriveEncoder != NULL) {
		this->leftDriveEncoder->Stop();
	}
	if(this->rightDriveEncoder != NULL) {
		this->rightDriveEncoder->Stop();
	}
}

Encoder *SensorSubsystem::GetLeftDriveEncoder() {
	return this->leftDriveEncoder;
}
int SensorSubsystem::GetLeftDriveEncoderCount() {
	return this->leftDriveEncoder->Get();
}
Encoder *SensorSubsystem::GetRightDriveEncoder() {
	return this->rightDriveEncoder;
}
int SensorSubsystem::GetRightDriveEncoderCount() {
	return this->rightDriveEncoder->Get();
}

Gyro *SensorSubsystem::GetHorizontalGyro() {
	return this->horizontalGyro;
}

//Todo Using this function might crash the robot.
float SensorSubsystem::GetHorizontalGyroAngle() {
	return this->horizontalGyro->GetAngle();
}

bool SensorSubsystem::GetThrowerLowLimt() {
	return this->throwerLowLimtSwitch->Get() == 0;
}
bool SensorSubsystem::GetThrowerHighLimit() {
	return this->throwerHighLimitSwitch->Get() == 0;
}
bool SensorSubsystem::GetIntakeLowLimit() {
	return this->intakeLowLimitSwitch->Get() == 0;
}

bool SensorSubsystem::GetIntakeHighLimit() {
	return this->intakeHighLimitSwitch->Get() == 0;
}
bool SensorSubsystem::GetIntakeStandbyLimit() {
	return this->intakeStandbyLimitSwitch->Get() == 0;
}
bool SensorSubsystem::GetIntakeBallSensor() {
	return this->intakeBallSensor->Get() == 0;
}

bool SensorSubsystem::GetIntakeOpenLimit() {
	return this->intakeOpenLimitSwitch->Get() == 0;
}

float SensorSubsystem::GetRangeFinderDistance(){
	float distance = 0;
	float voltage = this->throwerRangeFinder->GetVoltage();
	distance = (voltage / (5.0 / 512));
	return distance;
}

bool SensorSubsystem::GetIntakeBallTwoSensor() {
	return this->intakeBallSensorTwo->Get() == 0;
}
