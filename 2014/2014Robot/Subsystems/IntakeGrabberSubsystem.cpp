#include "IntakeGrabberSubsystem.h"
#include "../Robotmap.h"

IntakeGrabberSubsystem::IntakeGrabberSubsystem() : Subsystem("IntakeGrabberSubsystem") {
	printf("[IntakeGrabberSubsystem] Starting Construction\n");
	this->grabberSolenoid = new DoubleSolenoid(SOLENOID_MODULE, INTAKE_SOLENOID_OUT, INTAKE_SOLENOID_IN);
	printf("[IntakeGrabberSubsystem] Finished Construction\n");
}
    
void IntakeGrabberSubsystem::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}


// Put methods for controlling this subsystem
// here. Call these from Commands.

void IntakeGrabberSubsystem::Open() {
	this->grabberSolenoid->Set(DoubleSolenoid::kForward);
}

void IntakeGrabberSubsystem::Close() {
	this->grabberSolenoid->Set(DoubleSolenoid::kReverse);
}


void IntakeGrabberSubsystem::Stop() {
	this->grabberSolenoid->Set(DoubleSolenoid::kOff);
}
