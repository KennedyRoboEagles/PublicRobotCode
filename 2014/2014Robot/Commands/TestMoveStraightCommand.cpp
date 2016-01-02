#include "TestMoveStraightCommand.h"

#define TEST_FORWARD_SPEED (0.30)

TestMoveStraightCommand::TestMoveStraightCommand(float inches) : CommandBase("TestMoveStraightCommand") {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	printf("[TestMoveStraightCommand] Starting Construction\n");
	Requires(chassis);
	this->distance = inches;
	this->distanceTicks = this->distance * CHASSIS_TICKS_PER_INCH;
	printf("[TestMoveStraightCommand] Finished Construciton\n");
}

// Called just before this Command runs the first time
void TestMoveStraightCommand::Initialize() {
	printf("[TestMoveStraightCommand] Starting, Distance:%f, Ticks:%f\n", this->distance, this->distanceTicks);
	this->leftStartingCount = sensorSubsystem->GetLeftDriveEncoderCount();
	this->rightStartingCount = sensorSubsystem->GetRightDriveEncoderCount();
	printf("[TestMoveStraightCommand] L Start:%i, R Start:%i\n", leftStartingCount, rightStartingCount);
	this->leftSetPoint = this->leftStartingCount - this->distanceTicks;
	this->rightSetPoint = this->rightStartingCount + this->distanceTicks;
	printf("[TestMoveStraightCommand] L SetPoint:%f R SetPoint:%f\n", this->leftSetPoint, this->rightSetPoint);
	this->isLeftDone = false;
	this->isRightDone = false;
}

// Called repeatedly when this Command is scheduled to run
void TestMoveStraightCommand::Execute() {
	float leftError = this->leftSetPoint + sensorSubsystem->GetLeftDriveEncoderCount();
	float rightError = this->rightSetPoint - sensorSubsystem->GetRightDriveEncoderCount();
	if(leftError <= 0.0) {
		this->isLeftDone = false;
	}
	if(rightError <= 0.0) {
		this->isRightDone = false;
	}
	
	float leftPower = 0.0;
	float rightPower = 0.0;
	if(!isLeftDone) {
		leftPower = TEST_FORWARD_SPEED;
	}
	if(!isRightDone) {
		rightPower = TEST_FORWARD_SPEED;
	}
#ifdef DEBUG_PRINT
	printf("[TestMoveStraightCommand] Left Error:%f, Right Error:%f, Left Power: %f, Right Power:%f\n", leftError, rightError, leftPower, rightPower);
#endif
	chassis->TankDrive(leftPower, rightPower);
}

// Make this return true when this Command no longer needs to run execute()
bool TestMoveStraightCommand::IsFinished() {
	return isLeftDone && isRightDone;
}

// Called once after isFinished returns true
void TestMoveStraightCommand::End() {
	printf("[TestMoveStraightCommand] Robot has reached the target distance\n");
	chassis->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TestMoveStraightCommand::Interrupted() {
	printf("[TestMoveStraightCommand] Interrupted: Stopping the chassis\n");
	chassis->Stop();
}
