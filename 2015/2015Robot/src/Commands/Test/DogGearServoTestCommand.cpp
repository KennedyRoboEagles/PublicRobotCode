#include "DogGearServoTestCommand.h"

DogGearServoTestCommand::DogGearServoTestCommand()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(lowerTowerSubsystem);
}

// Called just before this Command runs the first time
void DogGearServoTestCommand::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void DogGearServoTestCommand::Execute()
{
	lowerTowerSubsystem->GetDogGearServo()->Set(oi->GetTestStick()->GetY());
	printf("Servo %f\n", oi->GetTestStick()->GetY());
}

// Make this return true when this Command no longer needs to run execute()
bool DogGearServoTestCommand::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void DogGearServoTestCommand::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DogGearServoTestCommand::Interrupted()
{

}
