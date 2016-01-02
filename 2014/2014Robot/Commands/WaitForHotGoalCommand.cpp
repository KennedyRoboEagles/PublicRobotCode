#include "WaitForHotGoalCommand.h"

WaitForHotGoalCommand::WaitForHotGoalCommand() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(visionSubsystem);
	this->timer = new Timer();
	this->timeout = 3.0;
}


WaitForHotGoalCommand::WaitForHotGoalCommand(float timeout) {
	Requires(visionSubsystem);
	this->timer = new Timer();
	this->timeout = timeout;
}

// Called just before this Command runs the first time
void WaitForHotGoalCommand::Initialize() {
	this->timer->Reset();
	this->timer->Start();
	this->lastProcessTime = 0;
	visionSubsystem->Reset();
	this->timer->Reset();
	this->timer->Start();
	visionSubsystem->DetectHotGoal();
	this->lastProcessTime = this->timer->Get();
}

// Called repeatedly when this Command is scheduled to run
void WaitForHotGoalCommand::Execute() {
	float timeDelta = this->lastProcessTime - this->timer->Get();
	if(timeDelta >= 0.0) {
		visionSubsystem->DetectHotGoal();
	}
}

// Make this return true when this Command no longer needs to run execute()
bool WaitForHotGoalCommand::IsFinished() {
	return visionSubsystem->IsHotTargetPressent() || this->timer->Get() >= this->timeout;
}

// Called once after isFinished returns true
void WaitForHotGoalCommand::End() {
	printf("[WaitForHotGoalCommand] Timed out or hot gaol detected\n");
	this->timer->Stop();
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void WaitForHotGoalCommand::Interrupted() {
	printf("[WaitForHotGoalCommand] Interrupt\n");
	this->timer->Reset();
}
