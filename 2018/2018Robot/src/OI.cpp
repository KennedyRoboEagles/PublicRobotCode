/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "OI.h"

#include <WPILib.h>
#include <SmartDashboard/SmartDashboard.h>

#include "Constants.h"
#include "Commands/Elevator/ElevatorUpCommand.h"
#include "Commands/Elevator/ElevatorDownCommand.h"
#include "Commands/Intake/IntakeCaptureCubeCommand.h"
#include "Commands/Intake/IntakeReleaseCubeCommand.h"

#include "Commands/Motion/DriveLinearForwardCommand.h"
#include "Commands/Motion/DriveLinearStrafeCommandV2.h"
#include "Commands/Motion/RotateToAngle.h"
#include "Commands/Sensors/ZeroEncodersCommand.h"
#include "Commands/Sensors/ZeroYawCommand.h"
#include "Commands/Test/TestSpeedCommand.h"
#include "Commands/Test/TestAutoCommandGroup.h"
#include "Triggers/XboxDPadTrigger.h"

enum XboxButton {
	kBumperLeft = 5,
	kBumperRight = 6,
	kStickLeft = 9,
	kStickRight = 10,
	kA = 1,
	kB = 2,
	kX = 3,
	kY = 4,
	kBack = 7,
	kStart = 8
};


enum DPad {
	kUp = 0,
	kRight = 90,
	kDown = 180,
	kLeft = 270
};

OI::OI() {
	// Process operator interface input here.
	revDigit_ = new RevDigit();
	revDigit_->Display("Gunr");

	stick_ = new XboxController(0);

	XboxDPadTrigger* elevatorUpTrigger = new XboxDPadTrigger(stick_, DPad::kUp);
	elevatorUpTrigger->WhileActive(new ElevatorUpCommand());

	XboxDPadTrigger* elevatorDownTrigger = new XboxDPadTrigger(stick_, DPad::kDown);
	elevatorDownTrigger->WhileActive(new ElevatorDownCommand());

	XboxDPadTrigger* openIntakeTrigger = new XboxDPadTrigger(stick_, DPad::kLeft);
	openIntakeTrigger->WhileActive(new IntakeReleaseCubeCommand());

	XboxDPadTrigger* grabIntakeTrigger = new XboxDPadTrigger(stick_, DPad::kRight);
	grabIntakeTrigger->WhileActive(new IntakeCaptureCubeCommand());


	if(false) {
		/*
		 * Test Joystick stuff
		 */

		test_ = new Joystick(1);
		Command* cmd = new DriveLinearForwardCommand(10, 0);
		JoystickButton* driveTestButton = new JoystickButton(test_, 1);
		driveTestButton->WhenPressed(cmd);
		JoystickButton* driveTestCancel = new JoystickButton(test_, 2);
		driveTestCancel->CancelWhenPressed(cmd);

		JoystickButton* autoBut = new JoystickButton(test_, 3);
		autoBut->WhenPressed(new TestAutoCommandGroup());


		JoystickButton* zeroEncoderButton = new JoystickButton(test_, 3);
		zeroEncoderButton->WhenPressed(new ZeroEncodersCommand());
	} else {
		test_ = nullptr;
	}

	if(false) {
		/*
		 * Smart Dashboard stuff
		 */

		SmartDashboard::PutData("Test Speed", new TestSpeedCommand());
		// SmartDashboard::PutData("Test Motor", new TestSpeedCommand());

		SmartDashboard::PutData("Rotate -90", new RotateToAngle(-90));
		SmartDashboard::PutData("Rotate 0", new RotateToAngle(0));
		SmartDashboard::PutData("Rotate 90", new RotateToAngle(90));

		SmartDashboard::PutData("Zero Encoders",  new ZeroEncodersCommand());

		SmartDashboard::PutData("Test Strafe", new DriveLinearStrafeCommandV2(0, -2, 0));
	}
	
	SmartDashboard::PutData("Test 10", new DriveLinearForwardCommand(10, 0));
	SmartDashboard::PutData("Zero IMU", new ZeroYawCommand());

}

double OI::GetStickStrafe() {
	return stick_->GetX(XboxController::JoystickHand::kLeftHand);
}

double OI::GetStickMove() {
	double left = stick_->GetTriggerAxis(XboxController::JoystickHand::kLeftHand);
	double right = stick_->GetTriggerAxis(XboxController::JoystickHand::kRightHand);

	if(left < right) {
		return right;
	} else {
		return -left;
	}
}

double OI::GetStickRotate() {
	return stick_->GetX(XboxController::JoystickHand::kRightHand);
}
