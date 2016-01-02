#include "ResetLowerCarManipulatorEncoderCommand.h"

ResetLowerCarManipulatorEncoderCommand::ResetLowerCarManipulatorEncoderCommand()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void ResetLowerCarManipulatorEncoderCommand::Initialize()
{
	sensorSubsystem->GetLowerCarManipulatorEncoder()->Reset();
}

// Called repeatedly when this Command is scheduled to run
void ResetLowerCarManipulatorEncoderCommand::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool ResetLowerCarManipulatorEncoderCommand::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void ResetLowerCarManipulatorEncoderCommand::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ResetLowerCarManipulatorEncoderCommand::Interrupted()
{

}
