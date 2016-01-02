#include "WPILib.h"
#include "Commands/Command.h"
#include "Commands/ExampleCommand.h"
#include "CommandBase.h"
#include "Commands/DriveForwardAutonomousCommandGroup.h"
#include "Commands/GrabAndThrowCommandGroup.h"
#include "Commands/GrabAndShootWithHotGoalDetectCommandGroup.h"
#include "Commands/DriveForwardTimeCommand.h"

class CommandBasedRobot : public IterativeRobot {
private:
	Command *autonomousCommand;
	LiveWindow *lw;
	
	virtual void RobotInit() {
		CommandBase::init();
		autonomousCommand = NULL;
		lw = LiveWindow::GetInstance();
		SmartDashboard::PutData(Scheduler::GetInstance());
	}
	
	virtual void AutonomousInit() {
		DriverStation *ds = DriverStation::GetInstance();
		int autoSelect = (ds->GetDigitalIn(1)) + (ds->GetDigitalIn(2) << 1) 
				+ (ds->GetDigitalIn(3) << 2);
		// Ensure there is some command for auto.
		autonomousCommand = new ExampleCommand();
		
		switch (autoSelect)
		{
		case 0:
			autonomousCommand = new DriveForwardTimeCommand(4,0.50);
			break;
		case 1:
			autonomousCommand = new GrabAndThrowCommandGroup();
			break;
		case 2:
			autonomousCommand = new GrabAndShootWithHotGoalDetectCommandGroup();
			break;
		case 3:
			autonomousCommand = new ExampleCommand();
			break;
		case 4:
			autonomousCommand = new ExampleCommand();
			break;
		case 5:
			autonomousCommand = new ExampleCommand();
			break;
		case 6:
			autonomousCommand = new ExampleCommand();
			break;
		case 7:
			autonomousCommand = new ExampleCommand();
			break;
		default:
			autonomousCommand = new ExampleCommand();
			break;
		}
		printf("Autonomous Command Selected: %i, Bit1:%i,Bit2:%i,Bit3:%i\n",autoSelect,ds->GetDigitalIn(1),ds->GetDigitalIn(2),ds->GetDigitalIn(3));
		autonomousCommand->Start();
	}
	
	virtual void AutonomousPeriodic() {
		Scheduler::GetInstance()->Run();
	}
	
	virtual void TeleopInit() {
		// This makes sure that the autonomous stops running when
		// teleop starts running. If you want the autonomous to 
		// continue until interrupted by another command, remove
		// this line or comment it out.
		//if(autonomousCommand != NULL) {
		//	autonomousCommand->Cancel();
		//}
	}
	
	virtual void TeleopPeriodic() {
		Scheduler::GetInstance()->Run();
	}
	
	virtual void TestPeriodic() {
		lw->Run();
	}
};

START_ROBOT_CLASS(CommandBasedRobot);

