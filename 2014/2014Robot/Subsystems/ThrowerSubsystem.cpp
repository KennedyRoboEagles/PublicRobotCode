#include "ThrowerSubsystem.h"
#include "../Robotmap.h"
//#include "../Commands/ThrowerSupervisiorCommand.h"

ThrowerSubsystem::ThrowerSubsystem() : Subsystem("ThrowerSubsystem") {
	printf("[ThrowerSubsystem] Starting Construction\n");
	this->leftSolenoidIn	= new Solenoid(SOLENOID_MODULE, THROWER_SOLENOID_LEFT_IN);
	this->leftSolenoidOut	= new Solenoid(SOLENOID_MODULE, THROWER_SOLENOID_LEFT_OUT);
	this->rightSolenoidIn	= new Solenoid(SOLENOID_MODULE, THROWER_SOLENOID_RIGHT_IN);
	this->rightSolenoidOut	= new Solenoid(SOLENOID_MODULE, THROWER_SOLENOID_RIGHT_OUT);
	
	printf("[ThrowerSubsystem] Finished Construction\n");
}
    
void ThrowerSubsystem::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new ThrowerSupervisiorCommand());
}


// Put methods for controlling this subsystem
// here. Call these from Commands.

void ThrowerSubsystem::setInSide(bool open) {
	this->leftSolenoidIn->Set(open);
	this->rightSolenoidIn->Set(open);
}
void ThrowerSubsystem::setOutSide(bool open) {
	this->leftSolenoidOut->Set(open);
	this->rightSolenoidOut->Set(open);
}

void ThrowerSubsystem::startThrow() {
	this->setInSide(false);
	this->setOutSide(true);
	
}
void ThrowerSubsystem::stopThrow() {
	this->setOutSide(false);
}
void ThrowerSubsystem::startRetract() {
	this->setInSide(true);
	this->setOutSide(false);
}
void ThrowerSubsystem::stopRetract() {
	this->setInSide(false);
}
void ThrowerSubsystem::stop() {
	this->setInSide(false);
	this->setOutSide(false);
}

void ThrowerSubsystem::SetInSolenoids(bool open) {
	this->setInSide(open);
}
void ThrowerSubsystem::SetOutSolenois(bool open) {
	this->setOutSide(open);
}

void ThrowerSubsystem::Throw() {
	this->startThrow();
}
void ThrowerSubsystem::Retract() {
	this->startRetract();
}
void ThrowerSubsystem::Stop() {
	this->stop();
}

void ThrowerSubsystem::TurnOnElectromagenet() {
	//this->electromagnet->Set(Relay::kOn);
}

void ThrowerSubsystem::TurnOffElectromagnet() {
	//this->electromagnet->Set(Relay::kOff);
}
