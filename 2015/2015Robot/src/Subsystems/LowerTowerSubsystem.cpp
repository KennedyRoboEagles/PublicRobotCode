#include "LowerTowerSubsystem.h"
#include "../Commands/LowerTower/LowerTowerSupervisorCommand.h"
#include "../RobotMap.h"

LowerTowerSubsystem::LowerTowerSubsystem(SensorSubsystem *sensorSubsystem) : Subsystem("LowerTowerSubsystem") {
	this->sensorSubsystem = sensorSubsystem;

	this->lowerTowerJaguar = new CANJaguar(TOWER_LCAR_JAGUAR);
	this->lowerTowerJaguar->SetPercentMode();
	this->lowerTowerJaguar->EnableControl();

	this->lowerTowerJaguar->Set(0.0);

	this->dgTimer = new Timer();
	this->dgServo = new Servo(LOWER_TOWER_DOG_GEAR_SERVO);

	this->state = EnterCalibration;
	this->atPosition = false;
	this->dogGearReady = false;
	this->dgState = DG_Stop;
	this->dgForwardSubState = DGF_Start;
	this->dgBackwardSubState = DGR_Start;
	this->dgGearSpeed = 0.0;

	this->stateChange = false;
}

void LowerTowerSubsystem::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
	//SetDefaultCommand(new LowerTowerSupervisorCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

//SpeedController *LowerTowerSubsystem::GetVerticalJaguar() {
//	return this->lowerTowerJaguar;
//}

//Value should be positive
void LowerTowerSubsystem::DogGearForward(float speed) {
	if(this->dgState != DG_Forward) {
		this->dgForwardSubState = DGF_Start;
	}
	this->dgState = DG_Forward;
	//Force the speed to be Positive, as it could destroy the dog gear if otherwise
	this->dgGearSpeed = fabs(speed);
}

Servo *LowerTowerSubsystem::GetDogGearServo() {
	return this->dgServo;
}

void LowerTowerSubsystem::DogGearBackward() {
	this->DogGearBackward(kBackwardSpeed);
}

//Value should be negative
void LowerTowerSubsystem::DogGearBackward(float speed) {
	if(this->dgState != DG_Backward) {
		this->dgBackwardSubState = DGR_Start;
	}
	this->dgState = DG_Backward;
	//Force the speed to be negative, as it could destroy the dog gear if otherwise
	this->dgGearSpeed = -fabs(speed);
}

void LowerTowerSubsystem::DogGearStop() {
	this->dgState = DG_Stop;
}

void LowerTowerSubsystem::DogGearRun() {
	switch(this->dgState) {
	case DG_Forward:
		switch(this->dgForwardSubState) {
		case DGF_Start:
			this->dogGearReady = false;
			printf("DGF Start\n");
			this->ServoDown();
			this->MoveBackward();
			this->dgTimer->Reset();
			this->dgTimer->Start();
			this->dgForwardSubState = DGF_MoveBackward;
			break;
		case DGF_MoveBackward:
			this->dogGearReady = false;
			printf("DFG Moving Backward %f\n", this->dgTimer->Get());
			if(kDGFBackwardTime < this->dgTimer->Get()) {
				this->dgTimer->Reset();
				this->dgForwardSubState = DGF_MoveForward;
			}
			this->MoveBackward();
			break;
		case DGF_MoveForward:
			this->dogGearReady = true;
			printf("DFG Moving Forward\n");
			this->MoveForward(this->dgGearSpeed);
			break;
		}
		break;
	case DG_Backward:
		switch(this->dgBackwardSubState) {
		case DGR_Start:
			printf("DGR Start\n");
			this->dogGearReady = false;
			this->ServoDown();
			this->dgBackwardSubState = DGR_Backward;
			break;
		case DGR_Backward:
			this->dogGearReady = true;
			printf("DGR Moving Backward	\n");
			this->MoveBackward(this->dgGearSpeed);
			break;
		}
		break;
	case DG_Stop:
		//printf("DG Stop\n");
		this->StopMotor();
		this->ServoUp();
		this->dogGearReady = true;
	}

	this->UpdateDogGearStateToSD();
}

bool LowerTowerSubsystem::DogGearReady() {
	return this->dogGearReady;
}

CANJaguar *LowerTowerSubsystem::GetVerticalJaguar() {
	return this->lowerTowerJaguar;
}

float LowerTowerSubsystem::GetForce() {
	return this->sensorSubsystem->GetLowerCarForce();
}


bool LowerTowerSubsystem::GetTopLimit() {
	return this->sensorSubsystem->GetLowerCarTopLimit();
}

int LowerTowerSubsystem::GetEncoderCount() {
	return this->GetEncoder()->Get();
}

float LowerTowerSubsystem::GetEncoderDistance() {
	return this->GetEncoder()->GetDistance() +  kTowerOffset;
}

Encoder *LowerTowerSubsystem::GetEncoder() {
	return this->sensorSubsystem->GetLowerCarVerticalPositionEncoder();
}

void LowerTowerSubsystem::ResetEncoder() {
	this->GetEncoder()->Reset();
}

void LowerTowerSubsystem::MoveBackward() {
	this->lowerTowerJaguar->Set(kBackwardSpeed);
}

void LowerTowerSubsystem::MoveBackward(float speed) {
	this->lowerTowerJaguar->Set(speed);
}

void LowerTowerSubsystem::MoveForward() {
	this->lowerTowerJaguar->Set(kForwardSpeed);
}

void LowerTowerSubsystem::MoveForward(float speed) {
	this->lowerTowerJaguar->Set(speed);
}

void LowerTowerSubsystem::StopMotor() {
	this->lowerTowerJaguar->Set(0.0);
}

LowerTowerSubsystem::LowerTowerState LowerTowerSubsystem::GetState() {
	return this->state;
}

void LowerTowerSubsystem::SetState(LowerTowerState state) {
	this->state = state;
}

LowerTowerSubsystem::LowerTowerPosition LowerTowerSubsystem::GetPosition() {
	return this->position;
}

void LowerTowerSubsystem::ReEnable() {
	this->state = EnterCalibration;
}

void LowerTowerSubsystem::PositionPickUpTote() {
	this->position = PickUpPosition;
	this->atPosition = false;
	this->stateChange = true;
}

void LowerTowerSubsystem::PositionStackTote() {
	this->position = StackPosition;
	this->atPosition = false;
	this->stateChange = true;
}

void LowerTowerSubsystem::PositionBottom() {
	this->position = BottomPosition;
	this->atPosition = false;
	this->stateChange = true;
}

void LowerTowerSubsystem::PositionLowerTote() {
	this->position = LowerTotePosition;
	this->atPosition = false;
	this->stateChange = true;
}

void LowerTowerSubsystem::PositionPickedUpBin() {
	this->position = PickedUpBinPosition;
	this->atPosition = false;
	this->stateChange = true;
}

void LowerTowerSubsystem::PositionSecondToteAcquisition() {
	this->position = SecondToteAcquisitionPosition;
	this->atPosition = false;
	this->stateChange = true;
}

void LowerTowerSubsystem::PositionClearPlayerStation() {
	this->position = ClearPlayerStationPosition;
	this->atPosition = false;
	this->stateChange = true;
}

void LowerTowerSubsystem::PositionBottomToteMovementPosition() {
	this->position = BottomToteMovementPosition;
	this->atPosition = false;
	this->stateChange = true;
}

void LowerTowerSubsystem::PositionBinClear4Stack() {
	this->position = BinClear4StackPosition;
	this->atPosition = false;
	this->stateChange = true;
}

bool LowerTowerSubsystem::IsAtPosition() {
	return this->atPosition;
}

void LowerTowerSubsystem::SetAtPosition(bool val) {
	this->atPosition = val;
}

void LowerTowerSubsystem::ServoDown() {
	this->dgServo->Set(kDGServoDownPosition);
}

void LowerTowerSubsystem::ServoUp() {
	this->dgServo->Set(kDGServoUpPosition);
}

void LowerTowerSubsystem::DogGearForward() {
	this->DogGearForward(kForwardSpeed);
}

void LowerTowerSubsystem::UpdateDogGearStateToSD() {
	std::string state = "";
	std::string forwardSubstate = "";
	std::string backwardSubstate = "";

	switch(this->dgState) {
	case DG_Forward:
		state = "Forward";
		break;
	case DG_Backward:
		state = "Backward";
		break;
	case DG_Stop:
		state = "Stop";
		break;
	default:
		state = "Unknown";
	}

	switch(this->dgForwardSubState) {
	case DGF_Start:
		forwardSubstate = "Start";
		break;
	case DGF_MoveBackward:
		forwardSubstate = "Move Backward";
		break;
	case DGF_MoveForward:
		forwardSubstate = "Move Forward";
		break;
	default:
		forwardSubstate = "Unknown";
	}

	switch(this->dgBackwardSubState) {
	case DGR_Start:
		backwardSubstate = "Start";
		break;
	case DGR_Backward:
		backwardSubstate = "Backward";
		break;
	default:
		backwardSubstate = "Unknown";
	}

	SmartDashboard::PutString("Dog Gear State", state);
	SmartDashboard::PutString("Dog Gear Forward SubState", forwardSubstate);
	SmartDashboard::PutString("Dog Gear Backward SubState", backwardSubstate);
	SmartDashboard::PutNumber("Dog Gear Motor Output", this->lowerTowerJaguar->Get());
}

bool LowerTowerSubsystem::DidStateChange() {
	return this->stateChange;
}

void LowerTowerSubsystem::SetStateChange(bool changed) {
	this->stateChange = changed;
}
