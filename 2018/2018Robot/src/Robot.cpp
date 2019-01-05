/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <Commands/Command.h>
#include <Commands/Scheduler.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include "Commands/Motion/DriveLinearForwardCommand.h"
#include <TimedRobot.h>
#include "AutoSelection.h"

#include "CommandBase.h"
#include "OI.h"

#include <CameraServer.h>
#include <unistd.h>
#include "Commands/Test/TestAutoCommandGroup.h"

class Robot : public frc::TimedRobot {
public:
	void RobotInit() override {

		CommandBase::InitSubsystems();

		AutoSelection::Initialize(CommandBase::oi->GetRevDigit());

//
//		/*
//		 * Do not remove the following sleep statement. It is needed to prevent
//		 * some weird interaction between the USB camera and NavX over serial.
//		 * The issue could be related to: https://github.com/kauailabs/navxmxp/issues/60
//		 */
//		printf("Sleeping\n");
//		sleep(2);
//		printf("Done\n");
//
//		cs::UsbCamera camera = CameraServer::GetInstance()->StartAutomaticCapture();
//		camera.SetResolution(320, 240);
////		camera.SetExposureAuto();
//		camera.SetBrightness(50);
//		camera.SetWhiteBalanceAuto();
//		camera.SetFPS(20);

		autoCmd_ = nullptr;

	}

	/**
	 * This function is called once each time the robot enters Disabled
	 * mode.
	 * You can use it to reset any subsystem information you want to clear
	 * when
	 * the robot is disabled.
	 */
	void DisabledInit() override {}

	void DisabledPeriodic() override {
		frc::Scheduler::GetInstance()->Run();
	}

	/**
	 * This autonomous (along with the chooser code above) shows how to
	 * select
	 * between different autonomous modes using the dashboard. The sendable
	 * chooser code works with the Java SmartDashboard. If you prefer the
	 * LabVIEW Dashboard, remove all of the chooser code and uncomment the
	 * GetString code to get the auto name from the text box below the Gyro.
	 *
	 * You can add additional auto modes by adding additional commands to
	 * the
	 * chooser code above (like the commented example) or additional
	 * comparisons
	 * to the if-else structure below with additional strings & commands.
	 */
	void AutonomousInit() override {
		printf("Starting auto %i", AutoSelection::GetInstance()->CurrentAuto());

		autoCmd_ = AutoSelection::GetInstance()->GetSelected();

		if (autoCmd_ != nullptr) {
			autoCmd_->Start();
		}
	}

	void AutonomousPeriodic() override {
		frc::Scheduler::GetInstance()->Run();
	}

	void TeleopInit() override {
		// This makes sure that the autonomous stops running when
		// teleop starts running. If you want the autonomous to
		// continue until interrupted by another command, remove
		// this line or comment it out.
		if (autoCmd_ != nullptr) {
			autoCmd_->Cancel();
		}
	}

	void TeleopPeriodic() override { frc::Scheduler::GetInstance()->Run(); }

	void TestPeriodic() override {}

private:
	// Have it null by default so that if testing teleop it
	// doesn't have undefined behavior and potentially crash.
	frc::Command* autoCmd_;
};

START_ROBOT_CLASS(Robot)
