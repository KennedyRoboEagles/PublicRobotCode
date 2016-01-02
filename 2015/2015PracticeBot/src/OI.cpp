#include "OI.h"
#include "RobotMap.h"
#include "Commands/TurnSpecifiedDegreesCommand.h"
#include "Commands/DriveDistanceCommand.h"

OI::OI()
{
	this->stick = new Joystick(OI_JOYSTICK_DRIVER);

	this->turn90Button = new JoystickButton(this->stick, 7);
	this->turn90Button->WhenPressed(new TurnSpecifiedDegreesCommand(90.0));

	this->turnneg90Button = new JoystickButton(this->stick, 8);
	this->turnneg90Button->WhenPressed(new TurnSpecifiedDegreesCommand(-90.0));

	this->move24ftButton = new JoystickButton(this->stick, 9);
	this->move24ftButton->WhenPressed(new DriveDistanceCommand(24.0));

	this->moveNeg24FtButton = new JoystickButton(this->stick, 10);
	this->moveNeg24FtButton->WhenPressed(new DriveDistanceCommand(-24.0));

	this->move48inButton = new JoystickButton(this->stick, 5);
	this->move48inButton->WhenPressed(new DriveDistanceCommand(48.0));
	this->moveNeg48inButton = new JoystickButton(this->stick, 6);
	this->moveNeg48inButton->WhenPressed(new DriveDistanceCommand(-48.0));
}

Joystick *OI::GetDriverStick() {
	return this->stick;
}
