#include "TestSpeedCommand.h"
#include <SmartDashboard/SmartDashboard.h>

TestSpeedCommand::TestSpeedCommand() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(chassis.get());
	SmartDashboard::PutNumber("Test Setpoint", 0);
}

// Called just before this Command runs the first time
void TestSpeedCommand::Initialize() {
	chassis->Stop();
	SmartDashboard::PutNumber("Talon Num", -1);
}

// Called repeatedly when this Command is scheduled to run
void TestSpeedCommand::Execute() {
	TalonSRX *t = nullptr;
	int i = SmartDashboard::GetNumber("Talon Num", -1);
	switch(i) {
	case 0:
		t = chassis->GetLeftFront();
		break;
	case 1:
		t = chassis->GetLeftBack();
		break;
	case 2:
		t = chassis->GetRightFront();
		break;
	case 3:
		t = chassis->GetRightBack();
		break;
	default:
		t = nullptr;
	}

	if(t == nullptr) {
		chassis->Stop();
		return;
	}

	double speed = SmartDashboard::GetNumber("Test Setpoint", 0);
	t->Set(ControlMode::Velocity, speed);
}

// Make this return true when this Command no longer needs to run execute()
bool TestSpeedCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void TestSpeedCommand::End() {
	chassis->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TestSpeedCommand::Interrupted() {
	chassis->Stop();
}
