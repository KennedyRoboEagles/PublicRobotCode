/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "LEDCommand.h"

LEDCommand::LEDCommand() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(leds.get());
	SetRunWhenDisabled(true);
	step_ = 0;
}

// Called just before this Command runs the first time
void LEDCommand::Initialize() {
	timer_.Reset();
	timer_.Start();
	step_ = 0;
}

// Called repeatedly when this Command is scheduled to run
void LEDCommand::Execute() {
	leds->SetRGB(1.0, 1.0, 1.0);
}

// Make this return true when this Command no longer needs to run execute()
bool LEDCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void LEDCommand::End() {
	leds->SetRGB(0, 0, 0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LEDCommand::Interrupted() {
	leds->SetRGB(0, 0, 0);
}
