#include "OI.h"
#include "RobotMap.h"

#include "Commands/Test/TestLowerTowerMoveUpCommand.h"
#include "Commands/Test/TestLowerTowerMoveDownCommand.h"
#include "Commands/Test/TestLowerCarManipulatorMoveOutwardCommand.h"
#include "Commands/Test/TestLowerCarManipulatorMoveInwardCommand.h"
#include "Commands/Test/TestDaisyFIlterJoystickCommand.h"
#include "Commands/Test/DogGearServoTestCommand.h"

#include "Commands/LowerTower/LowerTowerMoveToStackUpCommand.h"
#include "Commands/LowerTower/LowerTowerMoveToPickUpPositionCommand.h"
#include "Commands/LowerTower/LowerTowerSupervisorCommand.h"
#include "Commands/LowerTower/LowerTowerMoveToBottomCommand.h"
#include "Commands/LowerTower/LowerTowerReEnableCommand.h"
#include "Commands/LowerTower/ResetLowerTowerEncoder.h"
#include "Commands/LowerTower/LowerTowerLowerToteCommand.h"
#include "Commands/LowerTower/LowerTowerClearPlayerStationCommand.h"
#include "Commands/LowerTower/LowerTowerMoveToBottomToteMovementPositionCommand.h"
#include "Commands/LowerTower/LowerTowerMoveToPickupBinPositionCommand.h"
#include "Commands/LowerTower/LowerTowerMoveToSecondToteAqusitionPositionCommand.h"

#include "Commands/LowerCar/ResetLowerCarManipulatorEncoderCommand.h"
#include "Commands/LowerCar/LowerCarManipulatorAcquireToteCommand.h"
#include "Commands/LowerCar/LowerCarManipulatorOpenForNarrowToteCommand.h"
#include "Commands/LowerCar/LowerCarManipulatorOpenForWideToteCommand.h"
#include "Commands/LowerCar/LowerCarManipulatorReleaseToteCommand.h"
#include "Commands/LowerCar/LowerCarManipulatorDeathCommand.h"
#include "Commands/LowerCar/LowerCarManipulatorCloseForNarrowToteCommand.h"
#include "Commands/LowerCar/LowerCarManipulatorCloseForBinCommand.h"
#include "Commands/LowerTowerClear4ToteStackWithBinCommand.h"

#include "Commands/PickUpNextToteCommandGroup.h"
#include "Commands/PickUpLastToteCommandGroup.h"
#include "Commands/LoadRecycleBinCommandGroup.h"


#include "Commands/SetTotesDownCommandGroup.h"
#include "Commands/PickUpTotesCommnadGroup.h"
#include "Commands/TurnSpecifiedDegreesCommand.h"
#include "Commands/SelectAutonomousProgramCommand.h"



OI::OI()
{
	// Process operator interface input here.
	this->driverStick = new Joystick(OI_JOYSTICK_DRIVER);
	this->secondDriverStick = new Joystick(OI_JOYSTICK_SECOND_DRIVER);
	this->testTowerStick= new Joystick(OI_JOYSTICK_TEST_TOWER);
	this->testGrabberStick = new Joystick(OI_JOYSTICK_TEST_GRABBER);
	//Driver
	this->driverAutoSelectButton = new JoystickButton(this->driverStick, OI_BUTTON_DRIVER_AUTO_SELECT);
	this->driverAutoSelectButton->WhenPressed(new SelectAutonomousProgramCommand());

	//Second Driver
	this->secondDriverGrabberAcquireButton = new JoystickButton(this->secondDriverStick, OI_BUTTON_SECOND_DROVER_ACQUIRE);
	this->secondDriverGrabberAcquireButton->WhenPressed(new LowerCarManipulatorAcquireToteCommand());

	this->secondDriverGrabberLoadRecycleBinButton = new JoystickButton(this->secondDriverStick, OI_BUTTON_SECOND_DRIVER_LOAD_RECYLE_BIN);
	this->secondDriverGrabberLoadRecycleBinButton->WhenPressed(new LoadRecycleBinCommandGroup());

	this->secondDriverGrabberOpenForNarrowButton = new JoystickButton(this->secondDriverStick, OI_BUTTON_SECOND_DRIVER_OPEN_NARROW);
	this->secondDriverGrabberOpenForNarrowButton->WhenPressed(new  LowerCarManipulatorOpenForNarrowToteCommand());

	this->secondDriverGrabberOpenWideButton = new JoystickButton(this->secondDriverStick, OI_BUTTON_SECOND_DRIVER_OPEN_WIDE);
	this->secondDriverGrabberOpenWideButton->WhenPressed(new LowerCarManipulatorOpenForWideToteCommand());

	this->secondDriverGrabberPickNextToteButton = new JoystickButton(this->secondDriverStick, OI_BUTTON_SECOND_DRIVER_PICK_NEXT_TOTE);
	this->secondDriverGrabberPickNextToteButton->WhenPressed(new PickUpNextToteCommandGroup());

	this->secondDriverGrabberPickUpLastToteButton = new JoystickButton(this->secondDriverStick, OI_BUTTON_SECOND_DRICER_PICK_UP_LAST_TOTE);
	this->secondDriverGrabberPickUpLastToteButton->WhenPressed(new PickUpLastToteCommandGroup(1.0, 100));

	this->secondDriverLowerTowerButton = new JoystickButton(this->secondDriverStick, OI_BUTTON_SECOND_DRIVER_LOWER);
	//this->secondDriverLowerTowerButton->WhenPressed(new LowerTowerLowerToteCommand());
	this->secondDriverLowerTowerButton->WhileHeld(new TestLowerTowerMoveDownCommand());

	this->secondDriverTower2ndToteButton = new JoystickButton(this->secondDriverStick, OI_BUTTON_SECOND_DRIVER_2ND_TOTE);
	this->secondDriverTower2ndToteButton->WhenPressed(new LowerTowerMoveToSecondToteAqusitionPositionCommand());

	this->secondDriverStackTowerButton = new JoystickButton(this->secondDriverStick, OI_BUTTON_SECOND_DRIVER_STACK);
	//this->secondDriverStackTowerButton->WhenPressed(new LowerTowerMoveToStackUpCommand());
	this->secondDriverStackTowerButton->WhileHeld(new TestLowerTowerMoveUpCommand());

	this->secondDriverTowerClearPlayerStationButton = new JoystickButton(this->secondDriverStick, OI_BUTTON_SECOND_DRIVER_CLEAR_PLAYER_STATION);
	this->secondDriverTowerClearPlayerStationButton->WhenPressed(new LowerTowerClearPlayerStationCommand());

	this->secondDriverBinClear4StackButton = new JoystickButton(this->secondDriverStick, OI_BUTTON_SECOND_DRIVER_BIN_CLEAR_4_STACK);
	this->secondDriverBinClear4StackButton->WhenPressed(new LowerTowerClear4ToteStackWithBinCommand());

	/*
	 * Test Tower
	 */
	this->testTowerClearPlayerStationButton = new JoystickButton(this->testTowerStick, OI_BUTTON_TEST_TOWER_CLEAR_PLAYERSTATION);
	this->testTowerClearPlayerStationButton->WhenPressed(new LowerTowerClearPlayerStationCommand());
	this->testTowerLowerToteButton = new JoystickButton(this->testTowerStick, OI_BUTTON_TEST_TOWER_LOWER_TOTE);
	this->testTowerLowerToteButton->WhenPressed(new LowerTowerLowerToteCommand());
	this->testTowerMoveToBottomBottomButton = new JoystickButton(this->testTowerStick, OI_BUTTON_TEST_TOWER_MOVE_TO_BOTTOM);
	this->testTowerMoveToBottomBottomButton->WhenPressed(new LowerTowerMoveToBottomCommand());
	this->testTowerMoveToBottomMovementButton = new JoystickButton(this->testTowerStick, OI_BUTTON_TEST_TOWER_MOVE_TO_BOTTOM_MOVEMENT);
	this->testTowerMoveToBottomMovementButton->WhenPressed(new LowerTowerMoveToBottomToteMovementPositionCommand());
	this->testTowerMoveToPickUpButton = new JoystickButton(this->testTowerStick, OI_BUTTON_TEST_TOWER_MOVE_TO_PICK_UP);
	this->testTowerMoveToPickUpButton->WhenPressed(new LowerTowerMoveToPickUpPositionCommand());
	this->testTowerMoveTo2NDToteButton = new JoystickButton(this->testTowerStick, OI_BUTTON_TEST_TOWER_MOVE_2ND_TOTE);
	this->testTowerMoveTo2NDToteButton->WhenPressed(new LowerTowerMoveToSecondToteAqusitionPositionCommand());
	this->testTowerMoveToStackButton = new JoystickButton(this->testTowerStick, OI_BUTTON_TEST_TOWER_MOVE_TO_STACK_POSITION);
	this->testTowerMoveToStackButton->WhenPressed(new LowerTowerMoveToStackUpCommand());

	/*
	 * Test Grabber
	 */

	this->testGrabberAcquireToteButton = new JoystickButton(this->testGrabberStick, OI_BUTTON_TEST_GRABBER_ACQUIRE_TOTE);
	this->testGrabberAcquireToteButton->WhenPressed(new LowerCarManipulatorAcquireToteCommand());

	this->testGrabberCloseForBin = new JoystickButton(this->testGrabberStick, OI_BUTTON_TEST_GRABBER_CLOSE_FOR_BIN);
	this->testGrabberCloseForBin->WhenPressed(new LowerCarManipulatorCloseForBinCommand());

	this->testGrabberCloseForNarrowToteButton = new JoystickButton(this->testGrabberStick, OI_BUTTON_TEST_GRABBER_CLOSE_FOR_NARROW_TOTE);
	this->testGrabberCloseForNarrowToteButton->WhenPressed(new LowerCarManipulatorCloseForNarrowToteCommand());

	this->testGrabberOpenForNarrowButton = new JoystickButton(this->testGrabberStick, OI_BUTTON_TEST_GRABBER_OPEN_FOR_NARROW_TOTE);
	this->testGrabberOpenForNarrowButton->WhenPressed(new LowerCarManipulatorOpenForNarrowToteCommand());

	this->testGrabberReleseToteButton = new JoystickButton(this->testGrabberStick, OI_BUTTON_TEST_GRABBER_RELEASE_TOTE);
	this->testGrabberReleseToteButton->WhenPressed(new LowerCarManipulatorReleaseToteCommand());

	this->testGrabberOpenForWideButton = new JoystickButton(this->testGrabberStick, OI_BUTTON_TEST_GRABBER_OPEN_FOR_WIDE);
	this->testGrabberOpenForWideButton->WhenPressed(new LowerCarManipulatorOpenForWideToteCommand());

	this->testGrabberMoveInwardButton = new JoystickButton(this->testGrabberStick, OI_BUTTON_TEST_GRABBER_MOVE_INWARD);
	this->testGrabberMoveInwardButton->WhileHeld(new TestLowerCarManipulatorMoveInwardCommand());

	this->testGrabberMoveOutwardButton = new JoystickButton(this->testGrabberStick, OI_BUTTON_TEST_GRABBER_MOVE_OUTWARD);
	this->testGrabberMoveOutwardButton->WhileHeld(new TestLowerCarManipulatorMoveOutwardCommand());

	//Test Two

	SmartDashboard::PutData("Reset Encoder", new ResetLowerCarManipulatorEncoderCommand());
	SmartDashboard::PutData("Reset Lower Tower Encoder", new ResetLowerTowerEncoder());
	SmartDashboard::PutData("Move To Pickup", new LowerTowerMoveToPickUpPositionCommand());
	SmartDashboard::PutData("Move OT Bottom", new LowerTowerMoveToBottomCommand());
	SmartDashboard::PutData("Lower Tower ReEnable", new LowerTowerReEnableCommand());
	SmartDashboard::PutData("Turn 90", new TurnSpecifiedDegreesCommand(90));
	SmartDashboard::PutData("Turn Neg 90", new TurnSpecifiedDegreesCommand(-90));
}

Joystick *OI::GetDriverStick() {
	return this->driverStick;
}

Joystick *OI::GetTestStick() {
	return this->testTowerStick;
}
