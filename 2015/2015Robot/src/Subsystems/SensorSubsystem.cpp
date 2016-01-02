#include "SensorSubsystem.h"
#include "../RobotMap.h"
#include "../Commands/SensorUpdateCommand.h"
#include "../INS/INS.h"

const uint8_t IMU_UPDATE_RATE_HZ = 50;
const float FORCE_SLOPE = 83.568;
const float FORCE_Y_INTERCEPT = -24.404;

const float ULTRASONIC_SENSOR_SCALE = 113.0291799396;
const float ULTRASONIC_SENSOR_SCALE_MB1013 = 40.3149606299;

const float LOWER_CAR_MANIPULATOR_COUNTS_PER_INCH = 730.0;
const float LOWER_CAR_MANIPULATOR_OPEN_DISTANCE_WHEN_CLOSED = 12.375;

const float LOWER_TOWER_COUNTS_PER_INCH = 40.425355545341415285296475896619;

const float DRIVE_INCH_PER_COUNT = 0.1570796327;

const float PI = 3.14159265359;

SensorSubsystem::SensorSubsystem() : Subsystem("SensorSubsystem") {
	this->powerDistributionPanel = new PowerDistributionPanel();

	this->toteDetector = new DigitalInput(TOTE_DETECTION);

	this->chassisUltrasonicLeft = new AnalogInput(CHASSIS_ULTRASONIC_LEFT);
	this->chassisUltrasonicRight = new AnalogInput(CHASSIS_ULTRASONIC_RIGHT);
	this->chassisUltrasonicCenter = new AnalogInput(CHASSIS_ULTRASONIC_CENTER);

	this->towerLowLimit = new DigitalInput(TOWER_LIMIT_LOW);

	this->lowerCarForceSensor = new AnalogInput(TOWER_LCAR_FORCE_SENSOR);
	this->lowerCarTopLimit = new DigitalInput(LOWER_CAR_VERTICAL_LIMIT_HIGH);
	this->lowerCarManipulatorEncoder = new Encoder(LOWER_CAR_MANIPULATOR_ENCODER_A,
			LOWER_CAR_MANIPULATOR_ENCODER_B, false, Encoder::k4X);
	this->lowerCarManipulatorEncoder->SetPIDSourceParameter(Encoder::kDistance);
	this->lowerCarManipulatorEncoder->SetDistancePerPulse(1.0 / LOWER_CAR_MANIPULATOR_COUNTS_PER_INCH);
	this->lowerCarManipulatorEncoder->SetMaxPeriod(1.0);
	this->lowerCarManipulatorEncoder->Reset();

	this->lowerCarVerticalPositionEncoder = new Encoder(LOWER_CAR_VERTICAL_POSITION_ENCODER_A,
			LOWER_CAR_VERTICAL_POSITION_ENCODER_B, false, Encoder::k4X);
	this->lowerCarVerticalPositionEncoder->SetPIDSourceParameter(Encoder::kDistance);
	this->lowerCarVerticalPositionEncoder->SetDistancePerPulse(1.0 / LOWER_TOWER_COUNTS_PER_INCH);
	this->lowerCarVerticalPositionEncoder->SetMaxPeriod(1.0);
	this->lowerCarVerticalPositionEncoder->Reset();

	this->upperCarForceSensor = new AnalogInput(TOWER_UCAR_FORCE_SENSOR);
	this->upperCarTopLimit = new DigitalInput(UPPER_CAR_VERTICAL_LIMIT_HIGH);
	this->upperCarEncoder = new Encoder(UPPER_CAR_VERTICAL_POSITION_ENCODER_A,
			UPPER_CAR_VERTICAL_POSITION_ENCODER_B,false, Encoder::k4X);
	this->upperCarEncoder->SetPIDSourceParameter(Encoder::kDistance);
	this->upperCarEncoder->SetDistancePerPulse(1);
	this->upperCarEncoder->SetMaxPeriod(1.0);
	this->upperCarEncoder->Reset();

	this->leftDriveEncoder = new Encoder(CHASSIS_LEFT_ENCODER_A, CHASSIS_LEFT_ENCODER_B , false, Encoder::k4X);
	this->leftDriveEncoder->SetPIDSourceParameter(Encoder::kRate);
	this->leftDriveEncoder->SetDistancePerPulse(DRIVE_INCH_PER_COUNT);
	this->leftDriveEncoder->SetMaxPeriod(1.0);
	this->leftDriveEncoder->Reset();

	this->rightDriveEncoder = new Encoder(CHASSIS_RIGHT_ENCODER_A, CHASSIS_RIGHT_ENCODER_B , false, Encoder::k4X);
	this->rightDriveEncoder->SetPIDSourceParameter(Encoder::kRate);
	this->rightDriveEncoder->SetDistancePerPulse(DRIVE_INCH_PER_COUNT);
	this->rightDriveEncoder->SetMaxPeriod(1.0);
	this->rightDriveEncoder->Reset();

	this->centerDriveEncoder = new Encoder(CHASSIS_CENTER_ENCODER_A, CHASSIS_CENTER_ENCODER_B, false, Encoder::k4X);
	this->centerDriveEncoder->SetPIDSourceParameter(Encoder::kDistance);
	this->centerDriveEncoder->SetDistancePerPulse(DRIVE_INCH_PER_COUNT);
	this->centerDriveEncoder->SetMaxPeriod(1.0);
	this->centerDriveEncoder->Reset();

	this->serialPort = new SerialPort(57600, SerialPort::kUSB);
	this->imu = new IMU(serialPort, IMU_UPDATE_RATE_HZ);
	if (imu) {
		LiveWindow::GetInstance()->AddSensor("IMU", "Gyro", imu);
	}

	INS::GetInstance()->Enable();
	INS::GetInstance()->Reset();

}

void SensorSubsystem::InitDefaultCommand() {
	SetDefaultCommand(new SensorUpdateCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

Encoder *SensorSubsystem::GetLowerCarVerticalPositionEncoder() {
	return this->lowerCarVerticalPositionEncoder;
}

IMU *SensorSubsystem::GetIMU() {
	return this->imu;
}


float SensorSubsystem::GetChassisUltrasonicCenterDistance() {
	return this->chassisUltrasonicCenter->GetAverageVoltage() * ULTRASONIC_SENSOR_SCALE;
}

float SensorSubsystem::GetChassisUltrasonicLeftDistance() {
	return this->chassisUltrasonicLeft->GetAverageVoltage() * ULTRASONIC_SENSOR_SCALE_MB1013;
}
float SensorSubsystem::GetChassisUltrasonicRightDistance() {
	return this->chassisUltrasonicRight->GetAverageVoltage() * ULTRASONIC_SENSOR_SCALE_MB1013;
}

bool SensorSubsystem::TowerLowLimit() {
	return this->towerLowLimit->Get();
}

bool SensorSubsystem::GetUpperCarTopLimit() {
	return this->upperCarTopLimit;
}

bool SensorSubsystem::GetLowerCarTopLimit() {
	return !this->lowerCarTopLimit->Get();
}

Encoder *SensorSubsystem::GetUpperCarVerticalPositionEncoder() {
	return this->upperCarEncoder;
}

AnalogInput *SensorSubsystem::GetLowerCarForceInput() {
	return this->lowerCarForceSensor;
}

AnalogInput *SensorSubsystem::GetUpperCarForceInput() {
	return this->upperCarForceSensor;
}

float SensorSubsystem::GetUpperCarForceInPounds() {
	float voltage  = this->upperCarForceSensor->GetAverageVoltage();
	//y = mx + b
	return (FORCE_SLOPE * voltage) + FORCE_Y_INTERCEPT;
}

float SensorSubsystem::GetLowerCarForce() {
	float voltage  = this->lowerCarForceSensor->GetAverageVoltage();
	//y = mx + b
	return (FORCE_SLOPE * voltage) + FORCE_Y_INTERCEPT;
}

Encoder* SensorSubsystem::GetLowerCarManipulatorEncoder()
{
	return this->lowerCarManipulatorEncoder;
}

double SensorSubsystem::GetChannelCurrent(uint8_t channel)
{
	return this->powerDistributionPanel->GetCurrent(channel);
}

float SensorSubsystem::GetLowerCarOpenDistance() {
	float distance = 2.0 * (-this->lowerCarManipulatorEncoder->GetDistance());
	return distance + LOWER_CAR_MANIPULATOR_OPEN_DISTANCE_WHEN_CLOSED;
}

bool SensorSubsystem::IsTotePresentAtChassis() {
	return this->toteDetector->Get();
}

float SensorSubsystem::GetIMUYawRad() {
	return this->imu->GetYaw() * PI / 180.0;
}

Encoder *SensorSubsystem::GetLeftDriveEncoder() {
	return this->leftDriveEncoder;
}

Encoder *SensorSubsystem::GetRightDriveEncoder() {
	return this->rightDriveEncoder;
}

Encoder *SensorSubsystem::GetCenterDriveEncoder() {
	return this->centerDriveEncoder;
}
