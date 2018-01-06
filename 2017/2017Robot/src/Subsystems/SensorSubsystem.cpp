#include "SensorSubsystem.h"
#include "../RobotMap.h"
#include "../RobotConstants.h"

#include <DigitalInput.h>
#include <math.h>
#include "Chassis.h"

#include "Commands/SensorUpdateCommand.h"
#include <AHRS.h>

SensorSubsystem::SensorSubsystem() : Subsystem("SensorSubsystem") {

	pdp = new PowerDistributionPanel();

	climberIndex = new DigitalInput(CLIMBER_INDEX);

	chassisLeftEncoder = new Encoder(CHASSIS_LEFT_ENCODER_A, CHASSIS_LEFT_ENCODER_B, Encoder::k4X);
	chassisLeftEncoder->SetPIDSourceType(PIDSourceType::kDisplacement);
	chassisLeftEncoder->SetDistancePerPulse(kCHASSIS_DISTANCE_PER_PULSE);
	chassisLeftEncoder->SetReverseDirection(true);
	chassisLeftEncoder->Reset();

	chassisRightEncoder = new Encoder(CHASSIS_RIGHT_ENCODER_A, CHASSIS_RIGHT_ENCODER_B, Encoder::k4X);
	chassisRightEncoder->SetPIDSourceType(PIDSourceType::kDisplacement);
	chassisRightEncoder->SetDistancePerPulse(kCHASSIS_DISTANCE_PER_PULSE);
	chassisRightEncoder->SetReverseDirection(false);
	chassisRightEncoder->Reset();

	gyro = new AnalogGyro(1);

#ifdef ENABLE_IMU
	try {
		imu = new AHRS(SerialPort::Port::kUSB);
		DriverStation::ReportWarning("The MXP is initialized, we think.");
	} catch(std::exception &ex) {
		std::string err_string = "Error instantiating navX MXP:  ";
		err_string += ex.what();
		DriverStation::ReportError(err_string.c_str());
	}

#else
	imu = NULL;
#endif
}

void SensorSubsystem::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
	SetDefaultCommand(new SensorUpdateCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
AHRS* SensorSubsystem::GetIMU() {
	return imu;
}

PowerDistributionPanel* SensorSubsystem::GetPDP() {
	return this->pdp;
}

Encoder* SensorSubsystem::GetChassisLeftEncoder() {
	return chassisLeftEncoder;
}

Encoder* SensorSubsystem::GetChassisRightEncoder() {
	return chassisRightEncoder;
}

double SensorSubsystem::GetChassisLeftCurrent() {
	return (pdp->GetCurrent(PDP_CHASSIS_LEFT_FRONT)+ pdp->GetCurrent(PDP_CHASSIS_LEFT_FRONT))/2.0;
}

double SensorSubsystem::GetChassisRightCurrent() {
	return (pdp->GetCurrent(PDP_CHASSIS_RIGHT_FRONT)+ pdp->GetCurrent(PDP_CHASSIS_RIGHT_FRONT))/2.0;
}

bool SensorSubsystem::GetClimberIndex() {
	return !climberIndex->Get();
}

double SensorSubsystem::GetYaw() {
#ifdef SELECT_NAVX
	return imu->GetYaw();
#else
	return gyro->GetAngle();
#endif
}

double SensorSubsystem::GetYawRate() {
#ifdef SELECT_NAVX
	return imu->GetRate();
#else
	return gyro->GetRate();
#endif
}

void SensorSubsystem::ZeroYaw() {
#ifdef SELECT_NAVX
	return imu->ZeroYaw();
#else
	return gyro->Reset();
#endif
}

PIDSource* SensorSubsystem::GetYawSource() {
#ifdef SELECT_NAVX
	return imu;
#else
	return gyro;
#endif

}

void SensorSubsystem::ResetPhysicalPose() {
	chassisLeftEncoder->Reset();
	chassisRightEncoder->Reset();
	this->ZeroYaw();
}

Pose SensorSubsystem::GetPhysicalPose() {
	return Pose(chassisLeftEncoder->GetDistance(), chassisRightEncoder->GetDistance(),
			chassisLeftEncoder->GetRate(), chassisRightEncoder->GetRate(),
			this->GetYaw(), this->GetYawRate());
}
