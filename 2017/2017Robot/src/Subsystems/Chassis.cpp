#include "Chassis.h"
#include "../RobotMap.h"

#include <LiveWindow/LiveWindow.h>

#include <RobotDrive.h>
#include <CANSpeedController.h>
#include "../Commands/DriveWithJoystickCommand.h"
#include "../Util/utils.hpp"
#include "../RobotConstants.h"
#include "../Commands/TurnCommand.h"

#ifndef PRACTICE_BOT
#include <CANTalon.h>
#else
#include <CANJaguar.h>
#endif

Chassis::Chassis() : Subsystem("Chassis") {
#ifndef PRACTICE_BOT
	leftMaster = new CANTalon(CHASSIS_LEFT_MASTER);
	leftSlave = new CANTalon(CHASSIS_LEFT_SLAVE);
	rightMaster = new CANTalon(CHASSIS_RIGHT_MASTER);
	rightSlave = new CANTalon(CHASSIS_RIGHT_SLAVE);
#else
	leftMaster = new CANJaguar(CHASSIS_LEFT_MASTER);
	leftSlave = new CANJaguar(CHASSIS_LEFT_SLAVE);
	rightMaster = new CANJaguar(CHASSIS_RIGHT_MASTER);
	rightSlave = new CANJaguar(CHASSIS_RIGHT_SLAVE);
#endif

	leftMaster->SetControlMode(CANSpeedController::ControlMode::kPercentVbus);
	leftMaster->Set(0);
	leftMaster->SetInverted(false);

	rightMaster->SetControlMode(CANSpeedController::ControlMode::kPercentVbus);
	rightMaster->Set(0);
	rightMaster->SetInverted(true);

#ifndef PRACTICE_BOT
	leftSlave->SetControlMode(CANTalon::ControlMode::kFollower);
	leftSlave->Set(CHASSIS_LEFT_MASTER);

	rightSlave->SetControlMode(CANTalon::ControlMode::kFollower);
	rightSlave->Set(CHASSIS_RIGHT_MASTER);
#else
	leftSlave->SetControlMode(CANSpeedController::ControlMode::kPercentVbus);
	leftSlave->Set(0);
	leftSlave->SetInverted(false);

	rightSlave->SetControlMode(CANSpeedController::ControlMode::kPercentVbus);
	rightSlave->Set(0);
	rightSlave->SetInverted(true);

	leftMaster->EnableControl();
	leftSlave->EnableControl();
	rightMaster->EnableControl();
	rightSlave->EnableControl();

#endif

	LiveWindow::GetInstance()->AddActuator("Chassis", "Left", leftMaster);
	LiveWindow::GetInstance()->AddActuator("Chassis", "Right", rightMaster);

	this->EnableBrake();
}

void Chassis::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	SetDefaultCommand(new TurnCommand());
//	SetDefaultCommand(new DriveWithJoystickCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

CANSpeedController* Chassis::GetLeftMaster() {
	return leftMaster;
}

CANSpeedController* Chassis::GetRightMaster() {
	return rightMaster;
}

CANSpeedController* Chassis::GetLeftSlave() {
	return leftSlave;
}
CANSpeedController* Chassis::GetRightSlave() {
	return rightSlave;
}


void Chassis::Stop() {
	this->TankDrive(0.0,0.0);
}

void Chassis::ArcadeDrive(Joystick* stick, bool squared) {
	double x = HandleDeadband(stick->GetX(), kJOYSTICK_DEADBAND);
	double y = HandleDeadband(stick->GetY(), kJOYSTICK_DEADBAND);

//	double x_sense = (fabs(stick->GetRawAxis(3) - 1) * 0.35 * 0.5 + 0.3);
//	SmartDashboard::PutNumber("x_sense", x_sense);
//	printf("x_sense: %f\n", x_sense);
//	x *= x_sense;

	this->ArcadeDrive(y,x);
}

void Chassis::ArcadeDrive(double y, double x, bool squared) {
	SmartDashboard::PutNumber("Arcade Y", y);
	SmartDashboard::PutNumber("Arcade X", x);

	if(squared) {
		if(x < 0) {
			x *= -x;
		} else {
			x *= x;
		}
		if(y < 0) {
			y *= -y;
		} else {
			y *= y;
		}
	}

	y *= -1;

	double left  = y + x;
	double right = y - x;

	if(left > 1) {
		left = 1;
	} else if(left < -1) {
		left = -1;
	}

	if(right > 1) {
		right = 1;
	} else if(right < -1) {
		right = -1;
	}

	if(reverse) {
		right = -right;
		left = -left;
	}
	this->TankDrive(left, right);
}

void Chassis::TankDrive(double left, double right) {
//	printf("L%f, R%f\n", left, right);

#ifdef PRACTICE_BOT
//	if(fabs(left) > 0.05) {
//		double sign = 1.0;
//		if(left < 0) sign = -1.0;
//		left = 0.9612 * fabs(left) + 0.0347;
//		left *= sign;
//	} else {
//		left  = 0.0;
//	}
//
//	if(fabs(right) > 0.05) {
//		double sign = 1.0;
//		if(right < 0) sign = -1.0;
//		right = 0.7521 * fabs(right) + 0.0465;
//		right *= sign;
//	} else {
//		right = 0.0;
//	}
//	printf("L%f, R%f\n", left, right);
#else
	//Do Nothing for now
#endif


	leftMaster->Set(left);
	rightMaster->Set(right);

#ifdef PRACTICE_BOT
	leftSlave->Set(left);
	rightSlave->Set(right);
#endif
}

void Chassis::ToggeleReverseDrive() {
	reverse = !reverse;
	printf("reverse value = %d\n",reverse);
}

void Chassis::SetReversed(bool reversed) {
	reverse = reversed;
}

bool Chassis::IsReversed() {
	return reverse;
}


void Chassis::EnableBrake() {
	leftMaster->ConfigNeutralMode(CANSpeedController::NeutralMode::kNeutralMode_Brake);
	rightMaster->ConfigNeutralMode(CANSpeedController::NeutralMode::kNeutralMode_Brake);

#ifdef PRACTICE_BOT
	leftSlave->ConfigNeutralMode(CANSpeedController::NeutralMode::kNeutralMode_Brake);
	rightSlave->ConfigNeutralMode(CANSpeedController::NeutralMode::kNeutralMode_Brake);
#endif
}

void Chassis::DisableBrake() {
	leftMaster->ConfigNeutralMode(CANSpeedController::NeutralMode::kNeutralMode_Coast);
	rightMaster->ConfigNeutralMode(CANSpeedController::NeutralMode::kNeutralMode_Coast);
#ifdef PRACTICE_BOT
	leftSlave->ConfigNeutralMode(CANSpeedController::NeutralMode::kNeutralMode_Coast);
	rightSlave->ConfigNeutralMode(CANSpeedController::NeutralMode::kNeutralMode_Coast);
#endif
}

