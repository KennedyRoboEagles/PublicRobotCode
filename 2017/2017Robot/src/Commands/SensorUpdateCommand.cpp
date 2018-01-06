#include "SensorUpdateCommand.h"
#include <SmartDashboard/SmartDashboard.h>
#include "../RobotMap.h"

SensorUpdateCommand::SensorUpdateCommand() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(sensorSubsystem.get());
}

// Called just before this Command runs the first time
void SensorUpdateCommand::Initialize() {
}

// Called repeatedly when this Command is scheduled to run
void SensorUpdateCommand::Execute() {

	SmartDashboard::PutNumber("Chassis Left Distance", sensorSubsystem->GetChassisLeftEncoder()->GetDistance());
	SmartDashboard::PutNumber("Chassis Right Distance", sensorSubsystem->GetChassisRightEncoder()->GetDistance());

	SmartDashboard::PutNumber("Chassis Left Raw", sensorSubsystem->GetChassisLeftEncoder()->GetRaw());
	SmartDashboard::PutNumber("Chassis Right Raw", sensorSubsystem->GetChassisRightEncoder()->GetRaw());

	SmartDashboard::PutNumber("Chassis Left Rate",  sensorSubsystem->GetChassisLeftEncoder()->GetRate());
	SmartDashboard::PutNumber("Chassis Right Rate", sensorSubsystem->GetChassisRightEncoder()->GetRate());

	//SmartDashboard::PutNumber("Left Out", chassis->GetLeftMaster()->Get());
	SmartDashboard::PutNumber("Right Out", chassis->GetRightMaster()->Get());

//	SmartDashboard::PutNumber("Chassis Left Current", sensorSubsystem->GetChassisLeftCurrent());
//	SmartDashboard::PutNumber("Chassis Right Current", sensorSubsystem->GetChassisRightCurrent());
	SmartDashboard::PutNumber("Left Master Voltage", chassis->GetLeftMaster()->GetOutputVoltage());
	SmartDashboard::PutNumber("Right Master Voltage", chassis->GetRightMaster()->GetOutputVoltage());
	SmartDashboard::PutNumber("Left Slave Voltage", chassis->GetLeftSlave()->GetOutputVoltage());
	SmartDashboard::PutNumber("Right Slave Voltage", chassis->GetRightSlave()->GetOutputVoltage());

	SmartDashboard::PutNumber("Left Master Current", chassis->GetLeftMaster()->GetOutputCurrent());
	SmartDashboard::PutNumber("Right Master Current", chassis->GetRightMaster()->GetOutputCurrent());
	SmartDashboard::PutNumber("Left Slave Current", chassis->GetLeftSlave()->GetOutputCurrent());
	SmartDashboard::PutNumber("Right Slave Current", chassis->GetRightSlave()->GetOutputCurrent());

	SmartDashboard::PutNumber("Climber 0 Current", sensorSubsystem->GetPDP()->GetCurrent(PDP_CLIMBER_0));
	SmartDashboard::PutNumber("Climber 1 Current", sensorSubsystem->GetPDP()->GetCurrent(PDP_CLIMBER_1));

	SmartDashboard::PutBoolean("Climber At Index", sensorSubsystem->GetClimberIndex());

	auto imu = sensorSubsystem->GetIMU();
	if (NULL != imu)
	{
		SmartDashboard::PutNumber("IMU Yaw", sensorSubsystem->GetIMU()->GetYaw());
		SmartDashboard::PutNumber("IMU Rate", sensorSubsystem->GetIMU()->GetRate());
		SmartDashboard::PutBoolean("IMU Connected", sensorSubsystem->GetIMU()->IsConnected());
		SmartDashboard::PutBoolean("IMU Calibrating", sensorSubsystem->GetIMU()->IsCalibrating());
	}

	SmartDashboard::PutBoolean("A", oi->GetRevDigit()->GetA());
	SmartDashboard::PutBoolean("B", oi->GetRevDigit()->GetB());
	SmartDashboard::PutNumber("Pot", oi->GetRevDigit()->GetPotVoltage());


	SmartDashboard::PutNumber("Yaw", sensorSubsystem->GetYaw());
}

// Make this return true when this Command no longer needs to run execute()
bool SensorUpdateCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void SensorUpdateCommand::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SensorUpdateCommand::Interrupted() {

}
