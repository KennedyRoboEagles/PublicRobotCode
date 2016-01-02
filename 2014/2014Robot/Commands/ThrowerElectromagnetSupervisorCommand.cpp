#include "ThrowerElectromagnetSupervisorCommand.h"

ThrowerElectromagnetSupervisorCommand::ThrowerElectromagnetSupervisorCommand() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(throwerElectromagnetSubsystem);
	this->timer = new Timer();
}

// Called just before this Command runs the first time
void ThrowerElectromagnetSupervisorCommand::Initialize() {
	printf("[T.E.S.Command] Initializing\n");
	throwerElectromagnetSubsystem->SetState(ThrowerElectromagnetSubsystem::Off);
}

// Called repeatedly when this Command is scheduled to run
void ThrowerElectromagnetSupervisorCommand::Execute() {
	if(sensorSubsystem->GetThrowerLowLimt()) {
		if(throwerElectromagnetSubsystem->GetState() == ThrowerElectromagnetSubsystem::Off) {
			throwerElectromagnetSubsystem->SetState(ThrowerElectromagnetSubsystem::On);
		}
	} else {
		if(throwerElectromagnetSubsystem->GetState() == ThrowerElectromagnetSubsystem::On){
			throwerElectromagnetSubsystem->SetState(ThrowerElectromagnetSubsystem::Off);
		}
	}
	
	switch (throwerElectromagnetSubsystem->GetState()) {
		case ThrowerElectromagnetSubsystem::BeginThrow:
			printf("[T.E.S.Command] Starting Throw\n");
			throwerElectromagnetSubsystem->TurnOn();
			this->timer->Reset();
			this->timer->Start();
			throwerElectromagnetSubsystem->SetState(ThrowerElectromagnetSubsystem::Throwing);
			break;
		case ThrowerElectromagnetSubsystem::Throwing:
			if(this->timer->Get() >= throwerElectromagnetSubsystem->GetElectromagetTime()) {
				throwerElectromagnetSubsystem->SetState(ThrowerElectromagnetSubsystem::EndThrow);
			}
			break;
		case ThrowerElectromagnetSubsystem::EndThrow:
			printf("[T.E.S.Command] Throw Finished\n");
			this->timer->Stop();
			this->timer->Reset();
			throwerElectromagnetSubsystem->TurnOff();
			throwerElectromagnetSubsystem->SetState(ThrowerElectromagnetSubsystem::Off);
			break;
		case ThrowerElectromagnetSubsystem::On:
			throwerElectromagnetSubsystem->TurnOn();
			break;
		case ThrowerElectromagnetSubsystem::Off:
			throwerElectromagnetSubsystem->TurnOff();
			break;
		default:
			throwerElectromagnetSubsystem->SetState(ThrowerElectromagnetSubsystem::Off);
			break;
	}
}

// Make this return true when this Command no longer needs to run execute()
bool ThrowerElectromagnetSupervisorCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void ThrowerElectromagnetSupervisorCommand::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ThrowerElectromagnetSupervisorCommand::Interrupted() {
	throwerElectromagnetSubsystem->TurnOff();
}
