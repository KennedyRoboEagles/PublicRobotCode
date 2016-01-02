#ifndef OI_H
#define OI_H

#include "WPILib.h"
#include "Robotmap.h"
#include "Subsystems/SensorSubsystem.h"
//#include "Commands/SwapCommandCommand.h"

class OI {
private:
	Joystick *driverJoystick;
	Joystick *driver2Joystick;
	Joystick *testJoystick;
	Joystick *test2Joystick;
	
	KinectStick *leftStick;
	KinectStick *rightStick;
	
	JoystickButton *driverThrowButton;
	JoystickButton *driverThrowResetButton;
	JoystickButton *driverTiltIntakeDownButton;
	JoystickButton *driverTiltIntakeUpButton;
	JoystickButton *driverOpenIntakeButton;
	JoystickButton *driverCloseIntakeButton;
	JoystickButton *driverSoftThrowButton;
	JoystickButton *driverLoadAndThrowButton;
	
	/*JoystickButton *driver2TwoCommandTestButton;
	JoystickButton *driver2TwoCommandTestResetButton;
	JoystickButton *driver2ThrowButton;
	JoystickButton *driver2ThrowResetButton;
	JoystickButton *driver2ThrowWithElectromagnetButton;
	JoystickButton *driver2TestElectromagnetButton;
	*/
	JoystickButton *driver2RetractButton;
	JoystickButton *driver2ResetThrowButton;
	
	JoystickButton *testDriveForward3ftButton;
	JoystickButton *testDriveBack3ftButton;
	JoystickButton *testTurn90PidButton;
	JoystickButton *testTurnNeg90PidButton;
	JoystickButton *testTurn90Button;
	JoystickButton *testTurnNeg90Button;
	JoystickButton *testSoftThrowButton;
	JoystickButton *testSofterThrowButton;
	//JoystickButton *testTiltDownV2Button;
	JoystickButton *testMoveForwardTimeButton;
	
	JoystickButton *test2TiltUpButton;
	JoystickButton *test2TiltDownButton;
	JoystickButton *test2OpenGrabberButton;
	JoystickButton *test2CloseGrabberButton;
	JoystickButton *test2EnterStartConfigButton;
	JoystickButton *test2ExitStartConfigButton;
	JoystickButton *test2ThrowButton;
	JoystickButton *test2RetractButton;
	JoystickButton *test2ThrowAndRetractButton;
	JoystickButton *test2MoveStraight3ftButton;
	JoystickButton *test2MoveStraight5ftButton;
	JoystickButton *test2MoveBackward3ftButton;
	
	InternalButton *ballSensorButton;
	
	//SwapCommandCommand *swapCommand;
public:
	OI();
	Joystick *GetDriverJoystick();
	Joystick *GetDriverTwoJoystick();
	void SetBallSensorButton(bool pressed);
	KinectStick *GetLeftKinectStick();
	KinectStick *GetRightKinectStick();
};

#endif
