/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "IntakeReleaseCubeCommand.h"

const double kSpeed = -0.7;

IntakeReleaseCubeCommand::IntakeReleaseCubeCommand() {
	// Use Requires() here to declare subsystem dependencies
	Requires(intake.get());
}

// Called just before this Command runs the first time
void IntakeReleaseCubeCommand::Initialize() {
	intake->SetBoth(kSpeed);
}

// Called repeatedly when this Command is scheduled to run
void IntakeReleaseCubeCommand::Execute() {
	intake->SetBoth(kSpeed);
}

// Make this return true when this Command no longer needs to run execute()
bool IntakeReleaseCubeCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void IntakeReleaseCubeCommand::End() {
	intake->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void IntakeReleaseCubeCommand::Interrupted() {
	this->End();
}
