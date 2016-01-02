#include "ResetSwapCommandCommand.h"
#include "SwapCommandCommand.h"

ResetSwapCommandCommand::ResetSwapCommandCommand(SwapCommandCommand *swapCommand) {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	this->swapCommand = swapCommand;
}

// Called just before this Command runs the first time
void ResetSwapCommandCommand::Initialize() {
	this->swapCommand->Reset();
	
}

// Called repeatedly when this Command is scheduled to run
void ResetSwapCommandCommand::Execute() {
	
}

// Make this return true when this Command no longer needs to run execute()
bool ResetSwapCommandCommand::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void ResetSwapCommandCommand::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ResetSwapCommandCommand::Interrupted() {
}
