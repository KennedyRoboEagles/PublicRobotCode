#include <Buttons/InternalButton.h>

#include <Commands/AutoSelection/SelectNextAutoCommand.h>
#include <Commands/AutoSelection/SelectPreviousCommand.h>

#include <Commands/MotionProfiling/PathFinderCommand.h>
#include <Commands/MotionProfiling/TurnSpecifiedDegreesCommand.h>
#include <Commands/MotionProfiling/TurnSpecifiedDegrees2Command.h>

#include <Commands/ClimberIndexCommand.h>
#include <Commands/ClimberControlCommand.h>
#include <Commands/JerkForwardCommand.h>
#include <Commands/ResetChassisEncodersCommand.h>
#include <Commands/ResetIMU.h>
#include <Commands/ReverseCommand.h>
#include <Commands/ReverseDriveCommand.h>
#include <Commands/RumbleControllerCommand.h>
#include <Commands/ShooterCommand.h>
#include <Commands/ThrottleCommand.h>
#include <Triggers/MatchEndGameTrigger.h>

#include <Triggers/ThrottleTrigger.h>
#include "JoystickMap.h"
#include "OI.h"
#include <Commands/MotionProfiling/ArcTurnCommand.h>

#include "XboxJoystickMapping.h"

using namespace frc;

OI::OI() {
	// Process operator interface input here.
	this->driver = new Joystick(kJOY_DRIVER);
	this->climber = new Joystick(kJOY_CLIMBER);
	this->revDigit = new RevDigit();

	this->revDigit->Display("3081");

	this->controller = new Joystick(0);

	this->throttle = new ThrottleTrigger(controller);
	this->reverse = new ReverseTrigger(controller);
/*
#if 0
	this->climbButton = new JoystickButton(climber, kJOY_CLIMBER_CLIMB);
	this->climbButton->WhileHeld(new ClimberControlCommand(climber, false));
#else
	this->climbButton = new JoystickButton(driver, kJOY_CLIMBER_CLIMB);
	this->climbButton->WhileHeld(new ClimberControlCommand(driver, true));
#endif

	this->climbIndexButton = new JoystickButton(driver, kJOY_CLIMBER_INDEX);
	this->climbIndexButton->WhenPressed(new ClimberIndexCommand());

	this->reverseJoystick = new JoystickButton(driver, kJOY_DRIVER_REVERSE);
	this->reverseJoystick->WhenPressed(new ReverseDriveCommand());

	this->shoot = new JoystickButton(driver, kJOY_DRIVER_SHOOT);
	this->shoot->WhileHeld(new ShooterCommand());

	jerkForward = new JoystickButton(driver, kJOY_DRIVER_JERK);
	jerkForward->WhenPressed(new JerkForwardCommand());
*/

	Command *turnCommand = new TurnSpecifiedDegreesCommand(180);
	turn180Button = new JoystickButton(controller, A);
	turn180Button->WhenPressed(turnCommand);

	cancel80Button = new JoystickButton(controller, B);
	cancel80Button->CancelWhenPressed(turnCommand);


	throttle->WhileActive(new ThrottleCommand());
	reverse->WhileActive(new ReverseCommand());


	matchTimeTrigger = new MatchEndGameTrigger();
	matchTimeTrigger->WhenActive(new RumbleControllerCommand(1.5));

	SmartDashboard::PutData("Reset Chassis Encoder", new ResetChassisEncodersCommand());
//	double i  = 88.5/12 - 8.08/12.0- (kWHEELBASE_LENGTH/2.0 + kWHEELBASE_BUMBER);
	SmartDashboard::PutData("Run Motion Profiling", new PathFinderCommand(5.0, 0, 0));
	SmartDashboard::PutData("Zero Yaw", new ResetIMU());
	SmartDashboard::PutData("Turn 90Left", new ArcTurnCommand(90, true));
	SmartDashboard::PutData("Turn 90Right", new ArcTurnCommand(90, false));
//	SmartDashboard::PutData("Turn -90", new ArcTurnCommand(-90,true));
//	SmartDashboard::PutData("Turn 45", new ArcTurnCommand(45,true));
	SmartDashboard::PutData("Turn 60Right", new ArcTurnCommand(60, false));

}


Joystick* OI::GetDriverJoystick() {
	return this->driver;
}

Joystick* OI::GetClimberJoystick() {
	return this->climber;
}

Joystick* OI::GetController() {
	return this->controller;
}

RevDigit* OI::GetRevDigit() {
	return this->revDigit;
}


void OI::UpdateAutoButtons() {
//	nextAutoButton->SetPressed(revDigit->GetA());
//	previousAutoButton->SetPressed(revDigit->GetB());
}

