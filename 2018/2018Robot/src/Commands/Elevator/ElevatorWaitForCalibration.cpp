/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <Commands/Elevator/ElevatorWaitForCalibration.h>

ElevatorWaitForCalibration::ElevatorWaitForCalibration() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
//	Requires(intake.get());
//	Requires(elevator.get());
}

// Called just before this Command runs the first time
void ElevatorWaitForCalibration::Initialize() {
	printf("Waiting for Robot calibration");
}

// Called repeatedly when this Command is scheduled to run
void ElevatorWaitForCalibration::Execute() {
#ifdef DEBUG_PRINTF
	printf("Waiting for Robot calibration");
#endif
}

// Make this return true when this Command no longer needs to run execute()
bool ElevatorWaitForCalibration::IsFinished() {
//	return intake->IsCalibrated() && elevator->IsCalibrated();
//	return intake->IsCalibrated();
	return elevator->IsCalibrated();
}

// Called once after isFinished returns true
void ElevatorWaitForCalibration::End() {
	printf("Robot is calibrated, Lets win");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ElevatorWaitForCalibration::Interrupted() {
	printf("INTERRUPTED FOR SOME REASON");
}
