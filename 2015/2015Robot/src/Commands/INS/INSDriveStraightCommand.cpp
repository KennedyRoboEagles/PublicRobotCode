#include "INSDriveStraightCommand.h"
#include "INS/INS.h"
#include <math.h>

const float GAIN = 0.005;

INSDriveStraightCommand::INSDriveStraightCommand(float distance)
{
	Requires(chassis);
	this->distance = distance;
}

// Called just before this Command runs the first time
void INSDriveStraightCommand::Initialize()
{
	chassis->Stop();
	this->targetAngle = sensorSubsystem->GetIMUYawRad();
	this->xInit = INS::GetInstance()->GetPositionX();
	this->yInit = INS::GetInstance()->GetPositionY();

}

// Called repeatedly when this Command is scheduled to run
void INSDriveStraightCommand::Execute()
{
	float error = sensorSubsystem->GetIMU()->GetYaw() - this->targetAngle;
	float pGain = error * GAIN;
	if(this->distance > 0) {
		chassis->FilteredArcade(0.75, -pGain, false);
	} else {
		chassis->FilteredArcade(-0.75, -pGain, false);
	}

}

// Make this return true when this Command no longer needs to run execute()
bool INSDriveStraightCommand::IsFinished()
{
	float travledX = INS::GetInstance()->GetPositionX() - this->xInit;
	float travledY = INS::GetInstance()->GetPositionY() - this->yInit;
	float travledDistnace = std::sqrt(travledX * travledX + travledY * travledY);
	return travledDistnace > this->distance;
}

// Called once after isFinished returns true
void INSDriveStraightCommand::End()
{
	chassis->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void INSDriveStraightCommand::Interrupted()
{
	chassis->Stop();
}
