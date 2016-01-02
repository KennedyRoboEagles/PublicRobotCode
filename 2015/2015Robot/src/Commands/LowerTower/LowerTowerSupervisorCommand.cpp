#include "LowerTowerSupervisorCommand.h"
#include <math.h>
#include <string>

/*
 * The Supervisor command that runs the tower. A supervisor command is an command that controls all
 * aspects of a subsystem of the robot, and its state is altered by smaller commands.
 *
 * This command has two diffent states that control it.
 * 	1. Lower Tower state - this is the overall state, such as Running, Stopped. This is altered internally.
 * 	2. Lower Tower Position State - this is the deseried position of the tower. THIs state is altered by other commands
 *
 * The states are held in the LowerTowerSubsystem
 */

const float INITAL_ABSOLUTE_TOLERANCE = 1.0;
const float POST_ABSOLUTE_TOLERANCE = 2.0;
const float CALIBRATION_TIMEOUT = 5.0;

const float UP_SPEED = 0.75;
const float DOWN_SPEED = 0.5;

const float LOOSE_ROPE_VOLTAGE = 0.535;

//Setpoints for the positions
const float SETPOINT_BOTTOM = kTowerOffset;
const float SETPOINT_PICKUP = 9.5;
const float SETPOINT_STACK = 26;
const float SETPOINT_PICKED_UP_BIN = 30; 					//TODO Find Setpoint
const float SETPOINT_ACQUIERED_SECOND_TOTE_POSITION = 21.5;	//TODO Find Setpoint
const float SETPOINT_CLEAR_PLAYER_STATION_CHUTE = 47;		//TODO Find Setpoint
const float SETPOINT_BOTTOM_TOTE_MOVEMENT_POSITION = kTowerOffset; //TODO FIND Setpoint
const float SETPOINT_BIN_CLEAR_FOUR_STACK = 58.5;

LowerTowerSupervisorCommand::LowerTowerSupervisorCommand() {
	Requires(lowerTowerSubsystem);
	this->timer = new Timer();

	this->paused = false;
	this->inPosition = false;

	this->isCalibrated = false;
	this->setpoint = 0;

	this->towerForceVotlageFilter = DaisyFilter::MovingAverageFilter(5);

	this->towerSD = new TowerSD();
	SmartDashboard::PutData(this->towerSD);
	this->towerSD->Update("Unknown Position", 0.0, false, 0.0, 0.0, 0.0);
	this->towerSD->UpdateState("Unknown State");
	this->towerSD->UpdateLimits(false, false);

}

// Called just before this Command runs the first time
void LowerTowerSupervisorCommand::Initialize()
{
	printf("[LowerTowerSupervisorCommand] Initializing\n");
	if(!this->isStopped) {
		if(!this->isCalibrated) {
			printf("[LowerTowerSupervisorCommand] Not Calibrated\n");
			lowerTowerSubsystem->SetState(LowerTowerSubsystem::EnterCalibration);
		} else {
			printf("[LowerTowerSupervisorCommand] Already Calibrated\n");
			lowerTowerSubsystem->SetState(LowerTowerSubsystem::Running);
		}
	} else {
		printf("[LowerTowerSupervisorCommand] Was Stopped\n");
		lowerTowerSubsystem->SetState(LowerTowerSubsystem::Stopped);
	}
	this->timer->Reset();
	lowerTowerSubsystem->DogGearStop();
	lowerTowerSubsystem->DogGearRun();
	printf("[LowerTowerSupervisorCommand] Initialized\n");
}

// Called repeatedly when this Command is scheduled to run
void LowerTowerSupervisorCommand::Execute()
{
	std::string currentState = "";
	//Lower Tower and bottom are treated the same.
	this->bottomPosition = (lowerTowerSubsystem->GetPosition() == LowerTowerSubsystem::BottomPosition) || (lowerTowerSubsystem->GetPosition() == LowerTowerSubsystem::LowerTotePosition);
	switch(lowerTowerSubsystem->GetState()) {
	//Start the tower Calibration process
	case LowerTowerSubsystem::EnterCalibration:
		printf("[LowerTowerSupervisorCommand] Entering calibration\n");
		currentState = "Enter Calibration";
		if(this->isCalibrated) {
			lowerTowerSubsystem->SetState(LowerTowerSubsystem::Running);
		}

		lowerTowerSubsystem->DogGearStop();
		if(towerSubsystem->GetBottomLimit()) {
			printf("[LowerTowerSupervisorCommand] At Bottom limit\n");
			lowerTowerSubsystem->SetState(LowerTowerSubsystem::CalibrationReached);
			//lowerTowerSubsystem->GetEncoder()->Reset();
			break;
		}
		this->timer->Reset();
		this->timer->Start();
		lowerTowerSubsystem->SetState(LowerTowerSubsystem::Calibration);
		break;
	//Waiting for the tower to home itself
	case LowerTowerSubsystem::Calibration:
		printf("[LowerTowerSupervisorCommand] Calibration Time %f\n", this->timer->Get());
		currentState = "Calibration";
		if(towerSubsystem->GetBottomLimit()) {
			printf("[LowerTowerSupervisorCommand] At bottom limit\n");
			lowerTowerSubsystem->SetState(LowerTowerSubsystem::CalibrationReached);
			break;
		}
		if(CALIBRATION_TIMEOUT < this->timer->Get()) {
			printf("[LowerTowerSupervisorCommand] Calibration Timed out\n");
			lowerTowerSubsystem->SetState(LowerTowerSubsystem::Stopped);
			this->isCalibrated = false;
			break;
		}

		if(lowerTowerSubsystem->GetTopLimit()) {
			printf("[LowerTowerSupervisorCommand] Reached Top limit Stopping\n");
			lowerTowerSubsystem->SetState(LowerTowerSubsystem::Stopped);
			lowerTowerSubsystem->DogGearStop();
			this->isStopped = true;
		} else {
			lowerTowerSubsystem->DogGearForward();
		}

		break;

	case LowerTowerSubsystem::CalibrationReached:
		printf("[LowerTowerSupervisorCommand] Calibration Reached\n");
		currentState = "Calibration Reached";
		lowerTowerSubsystem->DogGearStop();
		lowerTowerSubsystem->ResetEncoder();
		this->isCalibrated = true;
		this->isStopped = false;
		lowerTowerSubsystem->SetState(LowerTowerSubsystem::Running);
		lowerTowerSubsystem->PositionBottom();
		break;
	//The normal running state of the Tower, this is where positions are applied.
	case LowerTowerSubsystem::Running:
		currentState = "Running";
		if(towerSubsystem->GetBottomLimit() && bottomPosition) {
			//printf("[LowerTowerSupervisorCommand] At bottom Limit Disabling Tower\n");
			lowerTowerSubsystem->DogGearStop();
			lowerTowerSubsystem->SetAtPosition(true);
		} else if(lowerTowerSubsystem->GetTopLimit()) {
			printf("[LowerTowerSupervisorCommand] At top limit Stopping tower\n");
			lowerTowerSubsystem->DogGearStop();
			this->lowerTowerSubsystem->SetState(LowerTowerSubsystem::Stopped);
		} else {
			printf("[LowerTowerSupervisorCommand] Running\n");
			this->run();
		}

		break;
	case LowerTowerSubsystem::Stopped:
		printf("[LowerTowerSupervisorCommand] Stopped\n");
		currentState = "Stopped";
		lowerTowerSubsystem->DogGearStop();
		this->isStopped = true;
		break;
	default:
		printf("[LowerTowerSupervisorCommand] Default\n");
		lowerTowerSubsystem->DogGearStop();
		currentState = "Unknown";
	}

	lowerTowerSubsystem->DogGearRun();
	SmartDashboard::PutBoolean("LT At Position", lowerTowerSubsystem->IsAtPosition());
	SmartDashboard::PutNumber("LT Jaguar Current", lowerTowerSubsystem->GetVerticalJaguar()->GetOutputCurrent());
	SmartDashboard::PutString("LT State", currentState);

	this->towerSD->UpdateState(currentState);
	this->towerSD->UpdateLimits(lowerTowerSubsystem->GetTopLimit(), towerSubsystem->GetBottomLimit());
}

// Make this return true when this Command no longer needs to run execute()
bool LowerTowerSupervisorCommand::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void LowerTowerSupervisorCommand::End() {
	printf("[LowerTowerSupervisorCommand] Ending\n");
	this->cleanUp();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LowerTowerSupervisorCommand::Interrupted() {
	printf("[LowerTowerSupervisorCommand] Interrupted\n");
	this->cleanUp();
}

/*
 * Here is all the logic for allowing the tower to move to the desired position.
 */
void LowerTowerSupervisorCommand::run() {
	std::string positionString = "";
	switch(lowerTowerSubsystem->GetPosition()) {
	case LowerTowerSubsystem::LowerTotePosition:
		this->setpoint = SETPOINT_BOTTOM;
		positionString = "Lower Tote";
		break;
	case LowerTowerSubsystem::BottomPosition:
		this->setpoint = SETPOINT_BOTTOM;
		positionString = "Bottom";
		break;
	case LowerTowerSubsystem::StackPosition:
		this->setpoint = SETPOINT_STACK;
		positionString = "Stack";
		this->paused = false;
		break;
	case LowerTowerSubsystem::PickUpPosition:
		this->setpoint = SETPOINT_PICKUP;
		positionString = "Pick Up";
		this->paused = false;
		break;
	case LowerTowerSubsystem::PickedUpBinPosition:
		this->setpoint = SETPOINT_PICKED_UP_BIN;
		positionString = "Picked Up Bin";
		this->paused = false;
		break;
	case LowerTowerSubsystem::SecondToteAcquisitionPosition:
		this->setpoint = SETPOINT_ACQUIERED_SECOND_TOTE_POSITION;
		positionString = "Acquired Second Tote";
		this->paused = false;
		break;
	case LowerTowerSubsystem::ClearPlayerStationPosition:
		this->setpoint = SETPOINT_CLEAR_PLAYER_STATION_CHUTE;
		positionString = "Clear Player Station";
		this->paused = false;
		break;
	case LowerTowerSubsystem::BottomToteMovementPosition:
		//TODO Find out if this state could be replaced  with Bottom
		this->setpoint = SETPOINT_BOTTOM_TOTE_MOVEMENT_POSITION;
		positionString = "Bottom Movement Postion";
		this->paused = false;
		break;
	case LowerTowerSubsystem::BinClear4StackPosition:
		this->setpoint = SETPOINT_BIN_CLEAR_FOUR_STACK;
		positionString = "BIN_CLEAR_FOUR_STACK ";
		this->paused = false;
		break;
	default:
		break;
	}

	float currentPosition = lowerTowerSubsystem->GetEncoderDistance();
	float delta = currentPosition - this->setpoint;
	float forceVoltage = sensorSubsystem->GetLowerCarForceInput()->GetAverageVoltage();
	float avgForceVoltage = this->towerForceVotlageFilter->Calculate(forceVoltage);
	if(avgForceVoltage < LOOSE_ROPE_VOLTAGE && !towerSubsystem->GetBottomLimit() && lowerTowerSubsystem->GetPosition() != LowerTowerSubsystem::StackPosition) {
		//Stop the tower if the rope is loose.
		printf("Lower Tower rope is loose with voltage %f, avg %f\n", forceVoltage, avgForceVoltage);
		lowerTowerSubsystem->DogGearStop();
		lowerTowerSubsystem->SetAtPosition(true);
		if(lowerTowerSubsystem->GetPosition() != LowerTowerSubsystem::LowerTotePosition) {
			//Unpause if going to different state.
			this->paused = false;
		} else {
			//Remain in the the current position if lowering
			this->paused = true;
		}
	} else {
		if(this->paused && lowerTowerSubsystem->GetPosition() == LowerTowerSubsystem::LowerTotePosition) {
			//Have the tower stay in the same position as when it was stopped.
			lowerTowerSubsystem->DogGearStop();
			lowerTowerSubsystem->SetAtPosition(true);
		} else {
			if((!this->inPosition) && lowerTowerSubsystem->DidStateChange()) {
				//The initial tolerance for the grabber
				if(delta > INITAL_ABSOLUTE_TOLERANCE) {
					//We are over, lower
					//Wait for the dog gear to be ready
					if(lowerTowerSubsystem->DogGearReady()) {
						lowerTowerSubsystem->DogGearForward();
					}
					lowerTowerSubsystem->SetAtPosition(false);
				} else if(delta < -INITAL_ABSOLUTE_TOLERANCE) {
					//We are under, raise up
					//Wait for the dog gear to be ready
					if(lowerTowerSubsystem->DogGearReady()) {
						lowerTowerSubsystem->DogGearBackward();
					}
					lowerTowerSubsystem->SetAtPosition(false);
				} else if(this->bottomPosition) {
					//This means we are moving to the bottom position,
					//and are within tolerance since it was not handled above.
					//However the tower can not stop now since we are above the bottom limit.
					if(lowerTowerSubsystem->DogGearReady()) {
						lowerTowerSubsystem->DogGearForward();
					}
					//The tower should stop if you look at the logic in the execute function.
				} else {
					//We are within our tolerance, stop
					lowerTowerSubsystem->DogGearStop();
					lowerTowerSubsystem->SetAtPosition(true);
					lowerTowerSubsystem->SetStateChange(false);
					this->inPosition = true;
				}
				this->paused = false;
			} else {
				if(fabs(delta) > POST_ABSOLUTE_TOLERANCE) {
					printf("In Position\n");
				} else {
					this->inPosition = false;
					printf("Not In Position\n");
				}
				lowerTowerSubsystem->DogGearStop();
			}
		}
	}

	SmartDashboard::PutString("LTower Position String", positionString);
	SmartDashboard::PutBoolean("LTower Paused", this->paused);
	SmartDashboard::PutNumber("LTower Setpoint", this->setpoint);
	SmartDashboard::PutNumber("LTower Delta", delta);
	SmartDashboard::PutNumber("LTower Position", delta);
	SmartDashboard::PutBoolean("LTower Post Tolerance", this->inPosition);
	SmartDashboard::PutBoolean("LTower At Position", lowerTowerSubsystem->IsAtPosition());
	printf("[LowerTowerSupervisorCommand] Position %i, Setpoint %f, Error %f\n", this->lowerTowerSubsystem->GetPosition(), this->setpoint, delta);

	this->towerSD->Update(positionString, avgForceVoltage, lowerTowerSubsystem->IsAtPosition(), this->setpoint, currentPosition, delta);
}

void LowerTowerSupervisorCommand::cleanUp() {
	printf("[LowerTowerSupervisorCommand] Clean UP\n");
	this->timer->Reset();
	this->paused = false;
	lowerTowerSubsystem->DogGearStop();
	lowerTowerSubsystem->DogGearRun();
}
