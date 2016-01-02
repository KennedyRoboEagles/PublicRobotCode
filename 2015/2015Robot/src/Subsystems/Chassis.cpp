#include "Chassis.h"
#include "../RobotMap.h"
#include "../Commands/HDriveWithJoystickCommand.h"
#include <cmath>

const float LEFT_FILTER_GAIN = 1.0;
const float RIGHT_FILTER_GAIN = 1.0;
const float CENTER_FILTER_GAIN = 1.0;

Chassis::Chassis() : Subsystem("Chassis") {
	this->leftSpeedController = new Talon(CHASSIS_LEFT_JAGUAR);
	this->rightSpeedController = new Talon(CHASSIS_RIGHT_JAGUAR);
	this->centerSpeedController = new Talon (CHASSIS_CENTER_JAGUAR);
	this->drive = new RobotDrive(leftSpeedController,rightSpeedController);
	this->drive->SetSafetyEnabled(false);

	this->leftFilter = DaisyFilter::SinglePoleIIRFilter(LEFT_FILTER_GAIN);
	this->rightFilter = DaisyFilter::SinglePoleIIRFilter(RIGHT_FILTER_GAIN);
	this->centerFilter = DaisyFilter::SinglePoleIIRFilter(CENTER_FILTER_GAIN);

	SmartDashboard::PutNumber("Chassis Left Gain", LEFT_FILTER_GAIN);
	SmartDashboard::PutNumber("Chassis Right Gain", RIGHT_FILTER_GAIN);
	SmartDashboard::PutNumber("Chassis Center Gain", CENTER_FILTER_GAIN);
}

void Chassis::InitDefaultCommand() {
	SetDefaultCommand(new HDriveWithJoystickCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void Chassis::Stop() {
	this->drive->TankDrive(0.0, 0.0);
}

RobotDrive *Chassis::GetDrive() {
	return this->drive;
}

SpeedController *Chassis::GetCenterSpeedController() {
	return this->centerSpeedController;
}

void Chassis::ResetFilters() {
	float leftGain = SmartDashboard::GetNumber("Chassis Left Gain", LEFT_FILTER_GAIN);
	float rightGain = SmartDashboard::GetNumber("Chassis Right Gain", RIGHT_FILTER_GAIN);
	float centerGain = SmartDashboard::GetNumber("Chassis Center Gain", CENTER_FILTER_GAIN);
	this->ResetFilters(leftGain, rightGain, centerGain);
}

void Chassis::ResetFilters(float leftGain, float rightGain, float centerGain)  {
	if(leftFilter != NULL) {
		delete leftFilter;
	}

	if(rightFilter != NULL) {
		delete rightFilter;
	}

	if(centerFilter != NULL) {
		delete centerFilter;
	}

	leftFilter = DaisyFilter::SinglePoleIIRFilter(leftGain);
	rightFilter = DaisyFilter::SinglePoleIIRFilter(rightGain);
	centerFilter = DaisyFilter::SinglePoleIIRFilter(centerGain);
}

void Chassis::FilteredLeft(float y) {
	this->leftSpeedController->Set(this->leftFilter->Calculate(y));
}

void Chassis::FilteredRight(float y) {
	this->rightSpeedController->Set(this->rightFilter->Calculate(y));
}

void Chassis::FilteredCenter(float x) {
	this->centerSpeedController->Set(this->centerFilter->Calculate(x));
}

//Modified WPI RobotDrive::ArcadeDrive
void Chassis::FilteredArcade(float moveValue, float rotateValue, bool squaredInputs) {
	float leftMotorOutput = 0.0;
	float rightMotorOutput = 0.0;

	moveValue = this->limit(moveValue);
	rotateValue = this->limit(rotateValue);

	if (squaredInputs) {
		// square the inputs (while preserving the sign) to increase fine control while permitting full power
		if (moveValue >= 0.0) {
			moveValue = (moveValue * moveValue);
		} else {
			moveValue = -(moveValue * moveValue);
		}
		if (rotateValue >= 0.0) {
			rotateValue = (rotateValue * rotateValue);
		} else {
			rotateValue = -(rotateValue * rotateValue);
		}
	}

	if (moveValue > 0.0) {
		if (rotateValue > 0.0) {
			leftMotorOutput = moveValue - rotateValue;
			rightMotorOutput = std::max(moveValue, rotateValue);
		} else {
			leftMotorOutput = std::max(moveValue, -rotateValue);
			rightMotorOutput = moveValue + rotateValue;
		}
	} else {
		if (rotateValue > 0.0) {
			leftMotorOutput = - std::max(-moveValue, rotateValue);
			rightMotorOutput = moveValue + rotateValue;
		} else {
			leftMotorOutput = moveValue - rotateValue;
			rightMotorOutput = - std::max(-moveValue, -rotateValue);
		}
	}

	this->FilteredLeft(leftMotorOutput);
	this->FilteredRight(rightMotorOutput);
}

float Chassis::limit(float val) {
	if (val > 1.0) {
		return 1.0;
	}
	if (val < -1.0) {
		return -1.0;
	}
	return val;
}
