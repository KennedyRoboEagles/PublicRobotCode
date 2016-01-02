#include "WaitForHotGoalKinectCommand.h"

#define HOTGOAL_TIMEOUT (2)
#define KINECT_Y_THRESHOLD (0.75)

WaitForHotGoalKinectCommand::WaitForHotGoalKinectCommand() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	this->timer = new Timer();
}

// Called just before this Command runs the first time
void WaitForHotGoalKinectCommand::Initialize() {
	this->timer->Reset();
	this->timer->Start();
}

// Called repeatedly when this Command is scheduled to run
void WaitForHotGoalKinectCommand::Execute() {
}

// Make this return true when this Command no longer needs to run execute()
bool WaitForHotGoalKinectCommand::IsFinished() {
	if(this->timer->Get() >= HOTGOAL_TIMEOUT) {
		return true;
	} else if(oi->GetRightKinectStick()->GetY() >= KINECT_Y_THRESHOLD) {
		return true;
	} else if(oi->GetLeftKinectStick()->GetY() >= KINECT_Y_THRESHOLD) {
		return true;
	} else {
		return false;
	}
}

// Called once after isFinished returns true
void WaitForHotGoalKinectCommand::End() {
	this->timer->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void WaitForHotGoalKinectCommand::Interrupted() {
	this->timer->Stop();
}
