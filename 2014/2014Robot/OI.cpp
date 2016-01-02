#include "OI.h"
#include "Commands/TestRetractCommand.h"
#include "Commands/TestThrowCommand.h"
#include "Commands/TestIntakeCloseCommand.h"
#include "Commands/TestIntakeOpenCommand.h"
#include "Commands/TestIntakeTiltUpCommand.h"
#include "Commands/TestIntakeTiltDownCommand.h"
#include "Commands/TestMoveStraightCommand.h"
//#include "Commands/ThrowCommand.h"
//#include "Commands/AdjustThrowerPowerCommand.h"
#include "Commands/TiltIntakeDownCommand.h"
#include "Commands/TiltIntakeUpCommand.h"
#include "Commands/OpenIntakeCommand.h"
#include "Commands/CloseIntakeCommand.h"
#include "Commands/EnterStartingConfigurationCommandGroup.h"
#include "Commands/ExitStartingConfigurationCommandGroup.h"
//#include "Commands/ThrowerStartCalibrationCommand.h"
#include "Commands/MoveForwardCommand.h"
#include "Commands/ThrowAndRetractCommandGroup.h"
#include "Commands/ThrowCommand.h"
#include "Commands/RetractCommand.h"
#include "Commands/TurnSpecifiedDegreesCommand.h"
//#include "Commands/ThrowerEnterStartingConfigurationCommand.h"
#include "Commands/MoveBackwardCommand.h"
#include "Commands/GrabAndThrowCommandGroup.h"
#include "Commands/DriveDistancePIDCommand.h"
#include "Commands/TurnSpecifiedDegreesPIDCommand.h"
#include "Commands/CaptureCameraImageCommand.h"
#include "Commands/VisionDetectHotGoalCommand.h"
#include "Commands/TiltIntakeDownV2Command.h"
#include "Commands/DriveForwardTimeCommand.h"
#include "Commands/LoadAndThrowCommandGroup.h"
#include "Commands/SwapCommandCommand.h"
#include "Commands/ResetSwapCommandCommand.h"
#include "Commands/ThrowWithElectromagnetCommand.h"
#include "Commands/TurnElectromagnetCommand.h"
#include "Commands/ThrowWithElectromagnetCommandV2.h"


OI::OI() {
	// Process operator interface input here.
	/*
	 * Driver Joystick
	 */
	this->driverJoystick = new Joystick(JOYSTICK_PORT_DRIVER);
	
	SwapCommandCommand *throwerSwapCommand = new SwapCommandCommand(new TiltIntakeUpCommand(), new LoadAndThrowCommandGroup());
	
	this->driverThrowButton = new JoystickButton(this->driverJoystick, BUTTON_DRIVER_THROW);
	//this->driverThrowButton->WhenPressed(new ThrowAndRetractCommandGroup());
	this->driverThrowButton->WhenPressed(throwerSwapCommand);
	
	this->driverThrowResetButton = new JoystickButton(this->driverJoystick, BUTTON_DRIVER_THROW_RESET);
	this->driverThrowResetButton->WhenPressed(new ResetSwapCommandCommand(throwerSwapCommand));
	
	this->driverTiltIntakeUpButton = new JoystickButton(this->driverJoystick, BUTTON_DRIVER_TILT_INTAKE_UP);
	this->driverTiltIntakeUpButton->WhenPressed(new TiltIntakeUpCommand());
	
	this->driverTiltIntakeDownButton = new JoystickButton(this->driverJoystick, BUTTON_DRIVER_TILT_INTAKE_DOWN);
	this->driverTiltIntakeDownButton->WhenPressed(new TiltIntakeDownCommand());
	
	this->driverOpenIntakeButton = new JoystickButton(this->driverJoystick, BUTTON_DRIVER_OPEN_INTAKE);
	this->driverOpenIntakeButton->WhenPressed(new OpenIntakeCommand());
	
	this->driverCloseIntakeButton = new JoystickButton(this->driverJoystick, BUTTON_DRIVER_CLOSE_INTAKE);
	this->driverCloseIntakeButton->WhenPressed(new CloseIntakeCommand());
	
	this->driverSoftThrowButton = new JoystickButton(this->driverJoystick, BUTTON_DRIVER_SOFT_THROW);
	this->driverSoftThrowButton->WhenPressed(new ThrowAndRetractCommandGroup(0.073));
	
	this->driverLoadAndThrowButton = new JoystickButton(this->driverJoystick, BUTTON_DRIVER_LOAD_AND_THROW);
	this->driverLoadAndThrowButton->WhenPressed(new LoadAndThrowCommandGroup());
	
	/*
	 * Shooter
	 */
	this->driver2Joystick = new Joystick(JOYSTICK_PORT_DRIVER_TWO);
	
	this->driver2RetractButton = new JoystickButton(this->driver2Joystick, BUTTON_DRIVER_TWO_RETRACT);
	this->driver2RetractButton->WhenPressed(new RetractCommand());
	
	this->driver2ResetThrowButton = new JoystickButton(this->driver2Joystick, BUTTON_DRIVER_TWO_RESET);
	this->driver2ResetThrowButton->WhenPressed(new ResetSwapCommandCommand(throwerSwapCommand));
	
	/*SwapCommandCommand *swapTestCommand = new SwapCommandCommand(new PrintCommand("Command #1\n"), new PrintCommand("Command #2\n"));
	this->driver2TwoCommandTestButton = new JoystickButton(this->driver2Joystick, BUTTON_DRIVER_TWO_TEST_SWAP);
	this->driver2TwoCommandTestButton->WhenPressed(swapTestCommand);
	
	this->driver2TwoCommandTestResetButton = new JoystickButton(this->driver2Joystick,BUTTON_DRIVER_TWO_TEST_SWAP_RESET);
	this->driver2TwoCommandTestResetButton->WhenPressed(new ResetSwapCommandCommand(swapTestCommand));
	
	SwapCommandCommand *swapThrowCommand = new SwapCommandCommand(new TiltIntakeUpCommand(),new LoadAndThrowCommandGroup());
	this->driver2ThrowButton = new JoystickButton(this->driver2Joystick, BUTTON_DRIVER_TWO_THROW);
	this->driver2ThrowButton->WhenPressed(swapThrowCommand);
	
	this->driver2ThrowResetButton = new JoystickButton(this->driver2Joystick, BUTTON_DRIVER_TWO_THROW_RESET);
	this->driver2ThrowResetButton->WhenPressed(new ResetSwapCommandCommand(swapThrowCommand));
	
	this->driver2ThrowWithElectromagnetButton = new JoystickButton(this->driver2Joystick, BUTTON_DRIVER_TWO_ELECTROMAGNET_THROW);
	this->driver2ThrowWithElectromagnetButton->WhenPressed(new ThrowWithElectromagnetCommandV2());
	
	this->driver2TestElectromagnetButton = new JoystickButton(this->driver2Joystick, BUTTON_DRIVER_TWO_ELECTROMAGNET_TEST);
	this->driver2TestElectromagnetButton->WhileHeld(new TurnElectromagnetCommand());
	*/
	/*
	 * Test Joystick
	 */
	
	this->testJoystick = new Joystick(JOYSTICK_PORT_TEST);

	this->testDriveForward3ftButton = new JoystickButton(this->testJoystick, BUTTON_TEST_DRIVE_FORWARD_3FT);
	this->testDriveForward3ftButton->WhenPressed(new DriveDistancePIDCommand(36));
	
	this->testDriveBack3ftButton = new JoystickButton(this->testJoystick, BUTTON_TEST_DRIVE_BACK_3FT);
	this->testDriveBack3ftButton->WhenPressed(new DriveDistancePIDCommand(-36));
	
	this->testTurn90PidButton = new JoystickButton(this->testJoystick, BUTTON_TEST_TURN_90_PID);
	this->testTurn90PidButton->WhenPressed(new TurnSpecifiedDegreesPIDCommand(90));
	
	this->testTurnNeg90PidButton = new JoystickButton(this->testJoystick, BUTTON_TEST_TURN_NEG_90_PID);
	this->testTurnNeg90PidButton->WhenPressed(new TurnSpecifiedDegreesPIDCommand(-90));
	
	this->testTurn90Button = new JoystickButton(this->testJoystick, BUTTON_TEST_TURN_90);
	this->testTurn90Button->WhenPressed(new TurnSpecifiedDegreesCommand(90.0));
	
	this->testTurnNeg90Button = new JoystickButton(this->testJoystick, BUTTON_TEST_TURN_NEG_90);
	this->testTurnNeg90Button->WhenPressed(new TurnSpecifiedDegreesCommand(-90.0));
	
	this->testSoftThrowButton = new JoystickButton(this->testJoystick, BUTTON_TEST_SOFT_THROW);
	this->testSoftThrowButton->WhenPressed(new ThrowCommand(0.073));
	
	this->testSofterThrowButton = new JoystickButton(this->testJoystick, BUTTON_TEST_SOFTER_THROW);
	this->testSofterThrowButton->WhenPressed(new ThrowCommand(0.018));
	
	//this->testTiltDownV2Button = new JoystickButton(this->testJoystick, BUTTON_TEST_TILT_DOWN_V2);
	//this->testTiltDownV2Button->WhenPressed(new TiltIntakeDownV2Command());
	this->testMoveForwardTimeButton = new JoystickButton(this->testJoystick, BUTTON_TEST_MOVE_FORWARD_TIME);
	this->testMoveForwardTimeButton->WhenPressed(new DriveForwardTimeCommand(4,0.50));
	
	/*
	 * Test2 Buttons
	 */
	
	this->test2Joystick = new Joystick(JOYSTICK_PORT_TEST2);

	this->test2TiltUpButton = new JoystickButton(this->test2Joystick, BUTTON_TEST2_TILT_UP);
	this->test2TiltUpButton->WhenPressed(new TiltIntakeUpCommand());
	
	this->test2TiltDownButton = new JoystickButton(this->test2Joystick, BUTTON_TEST2_TILT_DOWN);
	this->test2TiltDownButton->WhenPressed(new TiltIntakeDownCommand());
	
	this->test2OpenGrabberButton = new JoystickButton(this->test2Joystick, BUTTON_TEST2_OPEN_GRABBER);
	this->test2OpenGrabberButton->WhenPressed(new OpenIntakeCommand());
	
	this->test2CloseGrabberButton = new JoystickButton(this->test2Joystick, BUTTON_TEST2_CLOSE_GRABBER);
	this->test2CloseGrabberButton->WhenPressed(new CloseIntakeCommand());
	
	this->test2EnterStartConfigButton = new JoystickButton(this->test2Joystick, BUTTON_TEST2_ENTER_START_CONFIG);
	this->test2EnterStartConfigButton->WhenPressed(new EnterStartingConfigurationCommandGroup());
	
	this->test2ExitStartConfigButton = new JoystickButton(this->test2Joystick, BUTTON_TEST2_EXIT_START_CONFIG);
	this->test2ExitStartConfigButton->WhenPressed(new ExitStartingConfigurationCommandGroup());
	
	this->test2ThrowButton = new JoystickButton(this->test2Joystick, BUTTON_TEST2_THROW);
	this->test2ThrowButton->WhenPressed(new ThrowCommand());
	
	this->test2RetractButton = new JoystickButton(this->test2Joystick, BUTTON_TEST2_RETRACT);
	this->test2RetractButton->WhenPressed(new RetractCommand());
	
	this->test2ThrowAndRetractButton = new JoystickButton(this->test2Joystick, BUTTON_TEST2_THROW_RETRACT);
	this->test2ThrowAndRetractButton->WhenPressed(new ThrowAndRetractCommandGroup());
	
	
	this->test2MoveStraight5ftButton = new JoystickButton(this->test2Joystick, BUTTON_TEST2_MOVE_STRAIGHT_5FT);
	this->test2MoveStraight5ftButton->WhenPressed(new MoveForwardCommand((5*12), 0.5));
			
	
	this->test2MoveStraight3ftButton = new JoystickButton(this->test2Joystick, BUTTON_TEST2_MOVE_STRAIGHT_3FT);
	this->test2MoveStraight3ftButton->WhenPressed(new MoveForwardCommand(36, 0.75));
	
	
	this->test2MoveBackward3ftButton = new JoystickButton(this->test2Joystick, BUTTON_TEST2_MOVE_BACKWARDS_3FT);
	this->test2MoveBackward3ftButton->WhenPressed(new MoveBackwardCommand(35, .5));
	
	
	/*
	 * Internal Buttons
	 */
	this->ballSensorButton = new InternalButton();
	this->ballSensorButton->WhenPressed(new CloseIntakeCommand());
	
	/*
	 * SmartDashboard Buttons
	 */
	//SmartDashboard::PutData("Enter Starting Config Button", new EnterStartingConfigurationCommandGroup());
	//SmartDashboard::PutData("Exit Starting Config Button", new ExitStartingConfigurationCommandGroup());
	SmartDashboard::PutData("Capture Camera Image", new CaptureCameraImageCommand());
	SmartDashboard::PutData("Detect Hot Goal", new VisionDetectHotGoalCommand());
	
	/*
	 * Kinect Sticks
	 */
	this->leftStick = new KinectStick(1);
	this->rightStick = new KinectStick(2);
}

Joystick *OI::GetDriverJoystick() {
	return this->driverJoystick;
}

Joystick *OI::GetDriverTwoJoystick() {
	return this->driver2Joystick;
}

void OI::SetBallSensorButton(bool pressed) {
	if (!this->driverJoystick->GetRawButton(BUTTON_PREVENT_AUTO_BALL_INTAKE) && !this->driver2Joystick->GetRawButton(BUTTON_DRIVER_TWO_DISABLE))
	{
		this->ballSensorButton->SetPressed(pressed);
	}
}

KinectStick *OI::GetLeftKinectStick() {
	return this->leftStick;
}
KinectStick *OI::GetRightKinectStick() {
	return this->rightStick;
}
