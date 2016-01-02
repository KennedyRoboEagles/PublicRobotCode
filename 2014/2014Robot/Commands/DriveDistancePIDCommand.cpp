#include "DriveDistancePIDCommand.h"

DriveDistancePIDCommand::DriveDistancePIDCommand(int distance) {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(chassis);
	this->controller = NULL;
	this->setpoint = 0;
	//this->speed = speed;
	this->distance = distance;
	// steve: consider changing RightDriveEncoder below to LeftDriveEncoder
	this->controller = new PIDController(0,0,0, sensorSubsystem->GetLeftDriveEncoder(), this);
		this->controller->SetPID(0.01,0,0,0.1);
		this->controller->SetOutputRange(-0.75,0.75);
		this->controller->SetAbsoluteTolerance(chassis->InchesToTicks(1));
		
}

// Called just before this Command runs the first time
void DriveDistancePIDCommand::Initialize() {
	float startingEncoderCount = sensorSubsystem->GetLeftDriveEncoderCount();
	printf("[DriveDistancePIDCommand] Encoder Count: %i", sensorSubsystem->GetLeftDriveEncoderCount());
	
	// (Encoder Ticks per Rev) / ( (Wheel diamater) * PI )
	//float distanceTicks = chassis->InchesToTicks(distance);
	float distanceTicks = 120 / (4.0 * 3.14);
	
	this->setpoint = startingEncoderCount - distanceTicks;
	
	printf("[DriveDistancePIDCommand] PidController- P:%f, I:%f, D:%f, F:%f\n", 
			this->controller->GetP(),
			this->controller->GetI(),
			this->controller->GetD(),
			this->controller->GetF()
			);
	printf("[DriveDistancePIDCommand] Setpoint:%f Distance: %i\n", setpoint, distance);
	
	this->controller->SetSetpoint(setpoint);
	
	this->controller->Reset();
	this->controller->Enable();
}

// Called repeatedly when this Command is scheduled to run
void DriveDistancePIDCommand::Execute() {
#ifdef DEBUG_PRINT
	printf("[DriveDistancePIDCommand] Error %f\n", this->controller->GetError());
#endif
}

// Make this return true when this Command no longer needs to run execute()
bool DriveDistancePIDCommand::IsFinished() {
	float error = this->controller->GetError();
	if( error >= -10 && error <= 10) {
		return true;
	} else {
		return false;
	}
	//return this->controller->OnTarget();
}

// Called once after isFinished returns true
void DriveDistancePIDCommand::End() {
	printf("[DriveDistancePIDCommand] Reached the SetPont\n");
	this->cleanUp();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveDistancePIDCommand::Interrupted() {
	printf("[DriveDistancePIDCommand] Has been Interrupted\n");
	this->cleanUp();
}

void DriveDistancePIDCommand::cleanUp() {
	printf("[DriveDistancePIDCommand] Starting Clean Up\n");
	//if(this->controller != NULL) {
		this->controller->Disable();
		this->controller->Reset();
	//	delete this->controller;
	//	this->controller = NULL;
	//}
	chassis->Stop();
	printf("[DriveDistancePIDCommand] Clean Up finished\n");
}

void DriveDistancePIDCommand::PIDWrite(float output) {
	//chassis->TankDrive(output,output);
	chassis->GetRobotDrive()->ArcadeDrive(output, 0);
}
