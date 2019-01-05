/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "ZeroEncodersCommand.h"

ZeroEncodersCommand::ZeroEncodersCommand() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	this->SetRunWhenDisabled(true);
}

// Called just before this Command runs the first time
void ZeroEncodersCommand::Initialize() {
	chassis->ZeroEncoders();
}

// Called repeatedly when this Command is scheduled to run
void ZeroEncodersCommand::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool ZeroEncodersCommand::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void ZeroEncodersCommand::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ZeroEncodersCommand::Interrupted() {

}
