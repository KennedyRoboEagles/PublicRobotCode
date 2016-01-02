#include "TurnSpecifiedDegreesEncoderCountCommand.h"

#define TURN_TOLERANCE_DEGREES (5)
#define TURN_FEEDFORWARD (0.5)
#define TURN_MAX_SPEED (0.8)
#define TURN_LEFT_RIGHT_DISTANCE (28)
TurnSpecifiedDegreesEncoderCountCommand::TurnSpecifiedDegreesEncoderCountCommand(float degreesToTurn) {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(chassis);
	this->degreesToTurn = degreesToTurn;
}

// Called just before this Command runs the first time
void TurnSpecifiedDegreesEncoderCountCommand::Initialize() {
	float setPoint = this->calcSetpont();
	printf("[TurnSpecifiedDegreesEncoderCountCommand] Going to turn %f degress, Setpoint:%f \n", this->degreesToTurn, setPoint);
	PIDSource *pidSource = NULL;
	switch (rotationCenter) {
	case kLeft:
		pidSource = sensorSubsystem->GetRightDriveEncoder();
	case kRight:
		pidSource = sensorSubsystem->GetLeftDriveEncoder();
	case kCenter:
		//Todo Avg the two encoders together?
		pidSource = sensorSubsystem->GetLeftDriveEncoder();
		
	}
	this->controller = new PIDController(0.0, 0.0, 0.0, 0.0, pidSource, this);
	float range = this->clacInputRange();
	this->controller->SetInputRange(-range,range);
	this->controller->SetOutputRange(-1.0, 1.0);
	this->controller->SetAbsoluteTolerance(TURN_TOLERANCE_DEGREES);
	float pGain = this->calcPTerm();
	this->controller->SetPID(pGain, 0.0,0.0, TURN_FEEDFORWARD);
	this->controller->Reset();
	this->controller->Enable();
	this->controller->SetSetpoint(setPoint);
}

// Called repeatedly when this Command is scheduled to run
void TurnSpecifiedDegreesEncoderCountCommand::Execute() {
	
}

// Make this return true when this Command no longer needs to run execute()
bool TurnSpecifiedDegreesEncoderCountCommand::IsFinished() {
	return this->controller->OnTarget();
}

// Called once after isFinished returns true
void TurnSpecifiedDegreesEncoderCountCommand::End() {
	printf("[TurnSpecifiedDegreesEncoderCountCommand] The robot has reached the SetPoint\n");
	this->cleanUp();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TurnSpecifiedDegreesEncoderCountCommand::Interrupted() {
	printf("[TurnSpecifiedDegreesEncoderCountCommand] Interrupted stopping chassis\n");
	this->cleanUp();	
}

float TurnSpecifiedDegreesEncoderCountCommand::calcSetpont() {
	float setPoint = 0;
	float raduis = this->getRaduis();
	setPoint = (raduis * this->degreesToTurn * CHASSIS_TICKS_PER_INCH) / (180 * CHASSIS_WHEEL_DIAMETER);
	return setPoint;
}
float TurnSpecifiedDegreesEncoderCountCommand::calcPTerm() {
	float p = 0;
	int radius = this->getRaduis();
	p = TURN_MAX_SPEED / (CHASSIS_PI * radius * CHASSIS_TICKS_PER_INCH);
	return p;
}

float TurnSpecifiedDegreesEncoderCountCommand::clacInputRange() {
	float range = 0;
	range = CHASSIS_PI * this->getRaduis() * CHASSIS_TICKS_PER_INCH;
	return range;
}

int TurnSpecifiedDegreesEncoderCountCommand::getRaduis() {
	switch (this->rotationCenter) {
	case kLeft:
	case kRight:
		return TURN_LEFT_RIGHT_DISTANCE;
		break;
	case kCenter:
		return TURN_LEFT_RIGHT_DISTANCE / 2;
		break;
	default:
		return 0;
		break;
	}
}
void TurnSpecifiedDegreesEncoderCountCommand::cleanUp() {
	if(this->controller != NULL) {
		this->controller->Disable();
		delete this->controller;
	}
}

void TurnSpecifiedDegreesEncoderCountCommand::PIDWrite(float output) {
	switch(rotationCenter) {
	case kLeft:
		chassis->TankDrive(0.0, output);
		break;
	case kRight:
		chassis->TankDrive(output, 0.0);
		break;
	case kCenter:
		chassis->TankDrive(output, -output);
		break;
	default:
		chassis->Stop();
		break;
	}
}
