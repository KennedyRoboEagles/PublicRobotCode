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

	this->serialPort = new SerialPort(57600, SerialPort::kUSB);
	this->imu = new IMU(serialPort, IMU_UPDATE_RATE_HZ);
	if (imu) {
		LiveWindow::GetInstance()->AddSensor("IMU", "Gyro", imu);
	}

	this->leftDriveEncoder = new Encoder(0, 1 , false, Encoder::k4X);
	this->leftDriveEncoder->SetPIDSourceParameter(Encoder::kRate);
	this->leftDriveEncoder->SetDistancePerPulse(DRIVE_INCH_PER_COUNT);
	this->leftDriveEncoder->SetMaxPeriod(1.0);
	this->leftDriveEncoder->Reset();

	this->rightDriveEncoder = new Encoder(2, 3 , false, Encoder::k4X);
	this->rightDriveEncoder->SetPIDSourceParameter(Encoder::kRate);
	this->rightDriveEncoder->SetDistancePerPulse(DRIVE_INCH_PER_COUNT);
	this->rightDriveEncoder->SetMaxPeriod(1.0);
	this->rightDriveEncoder->Reset();

	this->centerDriveEncoder = new Encoder(4, 5 , false, Encoder::k4X);
	this->centerDriveEncoder->SetPIDSourceParameter(Encoder::kDistance);
	this->centerDriveEncoder->SetDistancePerPulse(DRIVE_INCH_PER_COUNT);
	this->centerDriveEncoder->SetMaxPeriod(1.0);
	this->centerDriveEncoder->Reset();


	INS::GetInstance()->Enable();
	INS::GetInstance()->Reset();

}

void SensorSubsystem::InitDefaultCommand() {
	SetDefaultCommand(new SensorUpdateCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.


IMU *SensorSubsystem::GetIMU() {
	return this->imu;
}

double SensorSubsystem::GetChannelCurrent(uint8_t channel)
{
	return this->powerDistributionPanel->GetCurrent(channel);
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
