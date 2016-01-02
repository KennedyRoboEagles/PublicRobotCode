#include "SensorUpdateCommand.h"
#include <INS/INS.h>

SensorUpdateCommand::SensorUpdateCommand()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(sensorSubsystem);
	this->imuInit = false;
}

// Called just before this Command runs the first time
void SensorUpdateCommand::Initialize() {
	this->imuInit = false;
}

// Called repeatedly when this Command is scheduled to run
void SensorUpdateCommand::Execute() {
	if(!imuInit) {
		//printf("[SensorUpdateCommand] Waiting for IMU Calibration\n");
		if(!sensorSubsystem->GetIMU()->IsCalibrating()) {
			printf("[SensorUpdateCommand] IMU Calibrated\n");
			sensorSubsystem->GetIMU()->ZeroYaw();
			INS::GetInstance()->Enable();
			imuInit = true;
		}
	}

	SmartDashboard::PutBoolean("IMU_Connected", sensorSubsystem->GetIMU()->IsConnected());
	SmartDashboard::PutNumber("IMU_Yaw", sensorSubsystem->GetIMU()->GetYaw());
	SmartDashboard::PutNumber("IMU_Pitch", sensorSubsystem->GetIMU()->GetPitch());
	SmartDashboard::PutNumber("IMU_Roll", sensorSubsystem->GetIMU()->GetRoll());
	SmartDashboard::PutNumber("IMU_CompassHeading", sensorSubsystem->GetIMU()->GetCompassHeading());
	SmartDashboard::PutNumber("IMU_Update_Count", sensorSubsystem->GetIMU()->GetUpdateCount());
	SmartDashboard::PutNumber("IMU_Byte_Count", sensorSubsystem->GetIMU()->GetByteCount());
	SmartDashboard::PutBoolean("IMU_IsCalibrating", sensorSubsystem->GetIMU()->IsCalibrating());
	
	SmartDashboard::PutNumber("INS X", INS::GetInstance()->GetPositionX());
	SmartDashboard::PutNumber("INS Y", INS::GetInstance()->GetPositionY());
	SmartDashboard::PutNumber("INS Velocity X", INS::GetInstance()->GetVelocityX());
	SmartDashboard::PutNumber("INS Velocity Y", INS::GetInstance()->GetVelocityX());
	SmartDashboard::PutBoolean("INS Moving", INS::GetInstance()->IsMoving());

	SmartDashboard::PutNumber("Left Encoder Count", sensorSubsystem->GetLeftDriveEncoder()->Get());
	SmartDashboard::PutNumber("Right Encoder Count", sensorSubsystem->GetRightDriveEncoder()->Get());
	SmartDashboard::PutNumber("Center Encoder Count", sensorSubsystem->GetCenterDriveEncoder()->Get());

	SmartDashboard::PutNumber("Left Encoder Distance", sensorSubsystem->GetLeftDriveEncoder()->GetDistance());
	SmartDashboard::PutNumber("Right Encoder Distance", sensorSubsystem->GetRightDriveEncoder()->GetDistance());
	SmartDashboard::PutNumber("Center Encoder Distance", sensorSubsystem->GetCenterDriveEncoder()->GetDistance());
}

// Make this return true when this Command no longer needs to run execute()
bool SensorUpdateCommand::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void SensorUpdateCommand::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SensorUpdateCommand::Interrupted()
{

}
