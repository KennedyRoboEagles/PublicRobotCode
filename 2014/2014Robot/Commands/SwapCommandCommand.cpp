#include "SwapCommandCommand.h"

SwapCommandCommand::SwapCommandCommand(Command *commandOne, Command *commandTwo) {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	this->commandOne = commandOne;
	this->commandTwo = commandTwo;
	//False for command one
	//True for command Two
	this->swapState = false;
	this->runCount = 0;
	this->runningCommand = NULL;

}

// Called just before this Command runs the first time
void SwapCommandCommand::Initialize() {
	this->runCount = 0;
	if(swapState) {
		printf("[SwapCommandCommand] Scheduling Command two\n");
		this->runningCommand = commandTwo;
	} else {
		this->runningCommand = commandOne;
		printf("[SwapCommandCommand] Scheduling Command One\n");
	}
	this->runningCommand->Start();
}

// Called repeatedly when this Command is scheduled to run
void SwapCommandCommand::Execute() {
	/* 
	 * We count the number of times the execute method is called,
	 * to allow the command to be scheduled and to be ran by the scheduler.
	 * This is is done to prevent this command from ending before the selected command has had a chance to run.
	 */
	
	if(this->runCount <= 2) {
		this->runCount++;
	}
}

// Make this return true when this Command no longer needs to run execute()
bool SwapCommandCommand::IsFinished() {
	return !runningCommand->IsRunning() && this->runCount >= 3;
}

// Called once after isFinished returns true
void SwapCommandCommand::End() {
	printf("[SwapCommandCommand] The command has finished\n");
	swapState = !swapState;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SwapCommandCommand::Interrupted() {
	printf("[SwapCommandCommand] Interrupted canceling command\n");
	this->runningCommand->Cancel();
}

void SwapCommandCommand::Reset() {
	this->swapState = false;
}
