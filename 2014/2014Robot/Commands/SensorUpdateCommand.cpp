#include "SensorUpdateCommand.h"


SensorUpdateCommand::SensorUpdateCommand() : CommandBase("SensorUpdateCommand") {
	Requires(sensorSubsystem);
}

// Called just before this Command runs the first time
void SensorUpdateCommand::Initialize() {
	sensorSubsystem->Start();
}

// Called repeatedly when this Command is scheduled to run
void SensorUpdateCommand::Execute() {
	SmartDashboard::PutNumber("Left Drive Encoder", sensorSubsystem->GetLeftDriveEncoderCount());
	SmartDashboard::PutNumber("Right Drive Encoder", sensorSubsystem->GetRightDriveEncoderCount());
	//SmartDashboard::PutNumber("Horizontal Gyro Angle", sensorSubsystem->GetHorizontalGyroAngle());
	SmartDashboard::PutBoolean("Thrower Low limit", sensorSubsystem->GetThrowerLowLimt());
	SmartDashboard::PutBoolean("Thrower High limit", sensorSubsystem->GetThrowerHighLimit());
	SmartDashboard::PutBoolean("Intake Low limit", sensorSubsystem->GetIntakeLowLimit());
	SmartDashboard::PutBoolean("Intake High limit", sensorSubsystem->GetIntakeHighLimit());
	SmartDashboard::PutBoolean("Intake Standby limit", sensorSubsystem->GetIntakeStandbyLimit());
	SmartDashboard::PutBoolean("Intake Ball sensor", sensorSubsystem->GetIntakeBallSensor());
	SmartDashboard::PutBoolean("Intake Open Limit", sensorSubsystem->GetIntakeOpenLimit());
	SmartDashboard::PutBoolean("Ball Sensor Two", sensorSubsystem->GetIntakeBallTwoSensor());
	SmartDashboard::PutNumber("Thrower Distance", sensorSubsystem->GetRangeFinderDistance());
	SmartDashboard::PutNumber("Gyro", sensorSubsystem->GetHorizontalGyro()->GetAngle());
	
	/*
	 * Update internal buttons
	 */
	oi->SetBallSensorButton(sensorSubsystem->GetIntakeBallSensor() && !sensorSubsystem->GetIntakeHighLimit());
	//oi->SetBallSensorButton(false);
}

// Make this return true when this Command no longer needs to run execute()
bool SensorUpdateCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void SensorUpdateCommand::End() {
	sensorSubsystem->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SensorUpdateCommand::Interrupted() {
	sensorSubsystem->Stop();
}
