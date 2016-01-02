#include "UpperTowerSubsystem.h"
#include "../RobotMap.h"

UpperTowerSubsystem::UpperTowerSubsystem(SensorSubsystem *sensorSubsystem) : Subsystem("UpperTowerSubsystem") {
	this->sensorSubsystem = sensorSubsystem;

	this->upperTowerJaguar = new CANJaguar(TOWER_UCAR_JAGUAR);
	this->upperTowerJaguar->SetPercentMode();
	this->upperTowerJaguar->EnableControl();
	this->upperTowerJaguar->Set(0.0);

	this->state = EnterCalibration;
}

void UpperTowerSubsystem::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

CANJaguar *UpperTowerSubsystem::GetVerticalJaguar() {
	return this->upperTowerJaguar;
}

float UpperTowerSubsystem::GetForce() {
	return this->sensorSubsystem->GetUpperCarForceInPounds();
}


bool UpperTowerSubsystem::GetTopLimit() {
	return this->sensorSubsystem->GetUpperCarTopLimit();
}

int UpperTowerSubsystem::GetEncoderCount() {
	return this->GetEncoder()->Get();
}

Encoder *UpperTowerSubsystem::GetEncoder() {
	return this->sensorSubsystem->GetUpperCarVerticalPositionEncoder();
}

void UpperTowerSubsystem::ResetEncoder() {
	this->GetEncoder()->Reset();
}

void UpperTowerSubsystem::MoveDown() {
	this->upperTowerJaguar->Set(kDownSpeed);
}

void UpperTowerSubsystem::MoveUp() {
	this->upperTowerJaguar->Set(kUpSpeed);
}

void UpperTowerSubsystem::StopMotor() {
	this->upperTowerJaguar->Set(0.0);
}

UpperTowerSubsystem::UpperTowerState UpperTowerSubsystem::GetState() {
	return this->state;
}

void UpperTowerSubsystem::SetState(UpperTowerState state) {
	this->state = state;
}

UpperTowerSubsystem::UpperTowerPosition UpperTowerSubsystem::GetPosition() {
	return this->position;
}

void UpperTowerSubsystem::PickUpBin() {
	this->position = PickUpPosition;
}

void UpperTowerSubsystem::StackBin() {
	this->position = StackPosition;
}

void UpperTowerSubsystem::Top() {
	this->position = TopPosition;
}

void UpperTowerSubsystem::StopAtCurrentPosition() {
	this->position = StoppedAtCurrentPosition;
}
