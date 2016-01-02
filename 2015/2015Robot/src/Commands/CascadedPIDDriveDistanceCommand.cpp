#include "CascadedPIDDriveDistanceCommand.h"
#include "../Util/PIDLinker.h"
#include "../Util/PIDSourceEncoderDistance.h"
#include "../Util/PIDSourceEncoderRate.h"

const float TOLLERANCE = 1.0;

const float ANGLE_P_GAIN = 0.02;

const float P_GAIN_ZERO = 0.01;
const float I_GAIN_ZERO = 0.00;
const float D_GAIN_ZERO = 0.00;
const float FF_ZERO = 0.00;

const float P_GAIN_ONE = 0.01;
const float I_GAIN_ONE = 0.00;
const float D_GAIN_ONE = 0.00;
const float FF_ONE = 0.00;


CascadedPIDDriveDistanceCommand::CascadedPIDDriveDistanceCommand(float distance)
{
	Requires(chassis);
	this->distance = distance;
	this->controller1 = new PIDController(
			P_GAIN_ONE, I_GAIN_ONE, D_GAIN_ONE, FF_ONE,
			new PIDSourceEncoderRate(sensorSubsystem->GetLeftDriveEncoder()), this);
	this->controller0 = new PIDController(
			P_GAIN_ZERO, I_GAIN_ZERO, D_GAIN_ZERO, FF_ZERO,
			new PIDSourceEncoderDistance(sensorSubsystem->GetLeftDriveEncoder()), new PIDLinker(this->controller1));

	this->controller0->SetInputRange(-20.0, 20.0); //Todo This is numbers are place holders
	this->controller0->SetOutputRange(-8.0, 8.0);
	this->controller1->SetInputRange(-8.0, 8.0);
	this->controller1->SetOutputRange(-1.0, 1.0);

	this->controller0->SetAbsoluteTolerance(TOLLERANCE);
}

// Called just before this Command runs the first time
void CascadedPIDDriveDistanceCommand::Initialize()
{
	this->controller1->Disable();
	this->controller0->Disable();

	this->controller0->Reset();
	this->controller1->Reset();

	sensorSubsystem->GetIMU()->ZeroYaw();

	this->controller0->SetSetpoint(this->distance);
}

// Called repeatedly when this Command is scheduled to run
void CascadedPIDDriveDistanceCommand::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool CascadedPIDDriveDistanceCommand::IsFinished()
{
	return this->controller0->OnTarget();
}

// Called once after isFinished returns true
void CascadedPIDDriveDistanceCommand::End()
{
	this->cleanUp();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CascadedPIDDriveDistanceCommand::Interrupted()
{
	this->cleanUp();
}

void CascadedPIDDriveDistanceCommand::PIDWrite(float output) {
	float angle = sensorSubsystem->GetIMU()->GetYaw();
	float rotate = ANGLE_P_GAIN * angle;
	chassis->GetDrive()->ArcadeDrive(output, rotate);
}

void CascadedPIDDriveDistanceCommand::cleanUp() {
	this->controller1->Disable();
	this->controller0->Disable();
	chassis->Stop();
}
