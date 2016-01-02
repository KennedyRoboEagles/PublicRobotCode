#include "ThrowerElectromagnetSubsystem.h"
#include "../Robotmap.h"
#include "../Commands/ThrowerElectromagnetSupervisorCommand.h"

ThrowerElectromagnetSubsystem::ThrowerElectromagnetSubsystem() : Subsystem("ThrowerElectromagnetSubsystem") {
	this->electromagnet = new Relay(THROWER_ELECTROMAGNET_RELAY_CHANNEL,Relay::kForwardOnly);
}
    
void ThrowerElectromagnetSubsystem::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
	SetDefaultCommand(new ThrowerElectromagnetSupervisorCommand());
}


// Put methods for controlling this subsystem
// here. Call these from Commands.
void ThrowerElectromagnetSubsystem::TurnOn() {
	this->electromagnet->Set(Relay::kOn);
}
void ThrowerElectromagnetSubsystem::TurnOff() {
	this->electromagnet->Set(Relay::kOff);
}
void ThrowerElectromagnetSubsystem::StartThrow(float electromagnetTime) {
	this->state = BeginThrow;
	this->electromagnetTime = electromagnetTime;
}

ThrowerElectromagnetSubsystem::ElectromagnetState ThrowerElectromagnetSubsystem::GetState() {
	return this->state;
}

void ThrowerElectromagnetSubsystem::SetState(ThrowerElectromagnetSubsystem::ElectromagnetState state) {
	this->state = state;
}

float ThrowerElectromagnetSubsystem::GetElectromagetTime() {
	return this->electromagnetTime;
}
