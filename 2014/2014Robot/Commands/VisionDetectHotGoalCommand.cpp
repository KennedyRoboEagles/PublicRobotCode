#include "VisionDetectHotGoalCommand.h"

VisionDetectHotGoalCommand::VisionDetectHotGoalCommand() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(visionSubsystem);
}

// Called just before this Command runs the first time
void VisionDetectHotGoalCommand::Initialize() {
	printf("[VisionDetectHotGoalCommand] Starting detection\n");
	visionSubsystem->DetectHotGoal();
	if(visionSubsystem->IsHotTargetPressent()) {
		printf("[VisionDetectHotGoalCommand] The Hot goal is present\n");
	} else {
		printf("[VisionDetectHotGoalCommand] No hot goal\n");
	}
}

// Called repeatedly when this Command is scheduled to run
void VisionDetectHotGoalCommand::Execute() {
	
}

// Make this return true when this Command no longer needs to run execute()
bool VisionDetectHotGoalCommand::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void VisionDetectHotGoalCommand::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void VisionDetectHotGoalCommand::Interrupted() {
}
