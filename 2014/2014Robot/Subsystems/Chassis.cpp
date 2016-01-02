#include "Chassis.h"
#include "../Robotmap.h"
#include "../Commands/DriveWithJoystickCommand.h"

Chassis::Chassis() : Subsystem("Chassis") {
	printf("[Chassis] Starting Construction\n");
	
	this->leftFrontMotor = new Jaguar(DRIVE_LEFT_FRONT_MOTOR);
	this->leftBackMotor = new Jaguar(DRIVE_LEFT_BACK_MOTOR);
	this->rightFrontMotor = new Jaguar(DRIVE_RIGHT_FRONT_MOTOR);
	this->rightBackMotor = new Jaguar(DRIVE_RIGHT_BACK_MOTOR);
	
	this->drive = new RobotDrive(this->leftFrontMotor,this->leftBackMotor, this->rightFrontMotor, this->rightBackMotor);
	//Todo Find out which motors need to be inverted.
	this->drive->SetInvertedMotor(RobotDrive::kFrontLeftMotor, true);
	this->drive->SetInvertedMotor(RobotDrive::kRearLeftMotor, true);
	this->drive->SetInvertedMotor(RobotDrive::kFrontRightMotor, true);
	this->drive->SetInvertedMotor(RobotDrive::kRearRightMotor, true);
	
	this->drive->SetSafetyEnabled(false);
	
	printf("[Chassis] Finished Construction\n");
}
    
void Chassis::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
	SetDefaultCommand(new DriveWithJoystickCommand());
}


// Put methods for controlling this subsystem
// here. Call these from Commands.

void Chassis::Stop() {
	this->drive->ArcadeDrive(0.0,0.0);
}

void Chassis::ArcadeDrive(Joystick *stick) {
	this->drive->ArcadeDrive(stick);
}

void Chassis::ArcadeDrive(float move, float rotate) {
	this->drive->ArcadeDrive(move,rotate);
}

void Chassis::TankDrive(float left, float right) {
	this->drive->TankDrive(left, right);
}

void Chassis::TurnLeft(float rate) {
	this->drive->ArcadeDrive(0, rate);
}
void Chassis::TurnRight(float rate) {
	this->drive->ArcadeDrive(0, -rate);
}
RobotDrive *Chassis::GetRobotDrive() {
	return this->drive;
}
SpeedController *Chassis::GetLeftFrontMotor() {
	return this->leftFrontMotor;
}
SpeedController *Chassis::GetLeftBackMotor() {
	return this->leftBackMotor;
}
SpeedController *Chassis::GetRightFrontMotor() {
	return this->rightFrontMotor;
}
SpeedController *Chassis::GetRightBackMotor() {
	return this->rightBackMotor;
}

float Chassis::InchesToTicks(int inches) {
	//float grearRatio = 1.0;
	float wheelSize = 4.0;
	float ticksPerInch = 120.0 / (3.14 * wheelSize);
	return ticksPerInch * inches;
}
