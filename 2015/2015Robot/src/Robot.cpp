#include "WPILib.h"
#include "Commands/Command.h"
#include "Commands/ExampleCommand.h"
#include "CommandBase.h"
#include "INS/INS.h"
#include "Commands/AutonomousCommandGroup.h"
#include "Commands/DriveForwardTimeCommand.h"
#include "Commands/SharonCommand.h"

class Robot: public IterativeRobot
{
private:
	//SendableChooser *autonomousChooser;
	Command *autonomousCommand;
	LiveWindow *lw;

	void RobotInit()
	{
		CommandBase::init();
		//autonomousChooser = new SendableChooser();
		autonomousCommand = new AutonomousCommandGroup();

		//autonomousChooser->AddDefault("Print Command", new PrintCommand("Autonomous!"));
		//autonomousChooser->AddDefault("Print Command 2", new PrintCommand("Autonomus 2!"));

		lw = LiveWindow::GetInstance();
	}
	
	void DisabledPeriodic()
	{
		Scheduler::GetInstance()->Run();
	}

	void AutonomousInit()
	{
		printf("AutonomousInit starting.\n");
		printf("Running program %d", CommandBase::autonomousProgram);

		if (CommandBase::autonomousProgram == NO_STEP_DRIVE_FORWARD) {
			this->autonomousCommand = new AutonomousCommandGroup();
		} else if (CommandBase::autonomousProgram == STEP_DRIVE_FORWARD){
			this->autonomousCommand = new DriveForwardTimeCommand(5.0, 1.00);
		} else if (CommandBase::autonomousProgram == DO_NOTHING){
			this->autonomousCommand = new SharonCommand();
		}

		//autonomousCommand->Start();
		printf("AutonomousInit completing.\n");
	}

	void AutonomousPeriodic()
	{
		Scheduler::GetInstance()->Run();
	}

	void TeleopInit()
	{
		// This makes sure that the autonomous stops running when
		// teleop starts running. If you want the autonomous to 
		// continue until interrupted by another command, remove
		// this line or comment it out.
		if (autonomousCommand != NULL) {
			autonomousCommand->Cancel();
		}
	}

	void TeleopPeriodic()
	{
		Scheduler::GetInstance()->Run();
	}

	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot);

