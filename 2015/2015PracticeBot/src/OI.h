#ifndef OI_H
#define OI_H

#include "WPILib.h"

class OI
{
private:
	Joystick *stick;
	JoystickButton *turn90Button;
	JoystickButton *turnneg90Button;
	JoystickButton *move24ftButton;
	JoystickButton *moveNeg24FtButton;
	JoystickButton *move48inButton;
	JoystickButton *moveNeg48inButton;
public:
	OI();
	Joystick *GetDriverStick();
};

#endif
