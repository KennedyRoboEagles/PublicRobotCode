#ifndef OI_H
#define OI_H

#include "WPILib.h"

class OI
{
private:
	Joystick *driverStick;
	Joystick *secondDriverStick;
	Joystick *testTowerStick;
	Joystick *testGrabberStick;

	JoystickButton *driverAutoSelectButton;

	JoystickButton *secondDriverLowerTowerButton;
	JoystickButton *secondDriverStackTowerButton;
	JoystickButton *secondDriverTower2ndToteButton;
	JoystickButton *secondDriverGrabberOpenForNarrowButton;
	JoystickButton *secondDriverGrabberAcquireButton;
	JoystickButton *secondDriverGrabberOpenWideButton;
	JoystickButton *secondDriverGrabberLoadRecycleBinButton;
	JoystickButton *secondDriverGrabberPickNextToteButton;
	JoystickButton *secondDriverGrabberPickUpLastToteButton;
	JoystickButton *secondDriverTowerClearPlayerStationButton;
	JoystickButton *secondDriverBinClear4StackButton;

	JoystickButton *testTowerClearPlayerStationButton;
	JoystickButton *testTowerLowerToteButton;
	JoystickButton *testTowerMoveToBottomBottomButton;
	JoystickButton *testTowerMoveToBottomMovementButton;
	JoystickButton *testTowerMoveToPickUpButton;
	JoystickButton *testTowerMoveTo2NDToteButton;
	JoystickButton *testTowerMoveToStackButton;

	JoystickButton *testGrabberAcquireToteButton;
	JoystickButton *testGrabberCloseForBin;
	JoystickButton *testGrabberCloseForNarrowToteButton;
	JoystickButton *testGrabberOpenForNarrowButton;
	JoystickButton *testGrabberReleseToteButton;
	JoystickButton *testGrabberOpenForWideButton;

	JoystickButton *testGrabberMoveInwardButton;
	JoystickButton *testGrabberMoveOutwardButton;

public:
	OI();
	Joystick *GetDriverStick();
	Joystick *GetTestStick();
};

#endif
