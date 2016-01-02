#include "IntakeTiltSubsystem.h"
#include "../Robotmap.h"

IntakeTiltSubsystem::IntakeTiltSubsystem() : Subsystem("IntakeTiltSubsystem") {
	printf("[IntakeGrabberSubsystem] Starting Construction\n");
	this->tiltDoubleSolenoid = new DoubleSolenoid(SOLENOID_MODULE, INTAKE_SOLENOID_TILT_OUT, INTAKE_SOLENOID_TILT_IN);
	printf("[IntakeGrabberSubsystem] Finished Constrcution\n");
}
    
void IntakeTiltSubsystem::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}


// Put methods for controlling this subsystem
// here. Call these from Commands.

void IntakeTiltSubsystem::TiltDown() {
	this->tiltDoubleSolenoid->Set(DoubleSolenoid::kReverse);
}

void IntakeTiltSubsystem::TiltUp() {
	this->tiltDoubleSolenoid->Set(DoubleSolenoid::kForward);
}

void IntakeTiltSubsystem::Stop() {
	this->tiltDoubleSolenoid->Set(DoubleSolenoid::kOff);
}
