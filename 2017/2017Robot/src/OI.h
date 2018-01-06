#ifndef OI_H
#define OI_H
#include <Joystick.h>
#include <Buttons/JoystickButton.h>
#include <Buttons/InternalButton.h>
#include <util/RevDigit.h>
#include <XboxController.h>
#include <Triggers/ThrottleTrigger.h>
#include <Triggers/ReverseTrigger.h>

class OI {
public:
	OI();

	Joystick* GetDriverJoystick();
	Joystick* GetClimberJoystick();

	Joystick* GetController();
	RevDigit* GetRevDigit();

	void UpdateAutoButtons();
private:

	Joystick *driver;
	Joystick *climber;

	JoystickButton *turn180Button;
	JoystickButton *cancel80Button;
	/*
	JoystickButton *climbButton;
	JoystickButton *climbIndexButton;
	JoystickButton *reverseJoystick;
	JoystickButton *jerkForward;
	JoystickButton *shoot;
*/

	RevDigit *revDigit;

	Joystick *controller;

	Trigger *throttle;
	Trigger *reverse;

	Trigger *matchTimeTrigger;
};

#endif  // OI_H
