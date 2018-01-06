#include <memory>

#include <RobotConstants.h>

#include <Commands/Command.h>
#include <Commands/Scheduler.h>
#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include <CameraServer.h>
#include <string>

#include "AutoSelection.h"
#include "Commands/AutoSelection/AutoSelectorSupervisorCommand.h"
#include "CommandBase.h"

class Robot: public frc::IterativeRobot {
public:

	void RobotInit() override {
#ifndef PRACTICE_BOT
		printf("Welcome to the 2017 Robot Program\n");
#else
		printf("Welcome to the 2017 Practice Robot Program\n");
#endif
		CommandBase::InitSubsystems();

		AutoSelection::Initialize(CommandBase::oi->GetRevDigit());

		autonomousCommand = nullptr;

		cs::UsbCamera cam = CameraServer::GetInstance()->StartAutomaticCapture();
//		cs::UsbCamera *cam = new cs::UsbCamera("cam0", 0);
		cam.SetResolution(320, 240);
		cam.SetFPS(20);
//		CameraServer::GetInstance()->StartAutomaticCapture((*cam));
	}

	/**
	 * This function is called once each time the robot enters Disabled mode.
	 * You can use it to reset any subsystem information you want to clear when
	 * the robot is disabled.
	 */
	void DisabledInit() override {
	}

	void DisabledPeriodic() override {
		frc::Scheduler::GetInstance()->Run();
	}

	/**
	 * This autonomous (along with the chooser code above) shows how to select
	 * between different autonomous modes using the dashboard. The sendable
	 * chooser code works with the Java SmartDashboard. If you prefer the
	 * LabVIEW Dashboard, remove all of the chooser code and uncomment the
	 * GetString code to get the auto name from the text box below the Gyro.
	 *
	 * You can add additional auto modes by adding additional commands to the
	 * chooser code above (like the commented example) or additional comparisons
	 * to the if-else structure below with additional strings & commands.
	 */
	void AutonomousInit() override {
		/* std::string autoSelected = frc::SmartDashboard::GetString("Auto Selector", "Default");
		if (autoSelected == "My Auto") {
			autonomousCommand.reset(new MyAutoCommand());
		}
		else {
			autonomousCommand.reset(new ExampleCommand());
		} */

		printf("Starting auto %i", AutoSelection::GetInstance()->CurrentAuto());

		autonomousCommand = AutoSelection::GetInstance()->GetSelected();

		if (autonomousCommand != nullptr) {
			autonomousCommand->Start();
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
		if (autonomousCommand != nullptr) {
			autonomousCommand->Cancel();
		}
	}

	void TeleopPeriodic() override {
		frc::Scheduler::GetInstance()->Run();
	}

	void TestPeriodic() override {
		frc::LiveWindow::GetInstance()->Run();
	}

private:
	frc::Command* autonomousCommand;
};

START_ROBOT_CLASS(Robot)
