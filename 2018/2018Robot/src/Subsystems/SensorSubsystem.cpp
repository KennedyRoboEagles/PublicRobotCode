#include "SensorSubsystem.h"
#include "../RobotMap.h"
#include <Timer.h>
#include <thread>
#include <unistd.h>
#include <HAL/cpp/SerialHelper.h>
#include <iostream>
#include "debug.h"

using namespace frc;


SensorSubsystem::SensorSubsystem() : Subsystem("ExampleSubsystem") {
	hal::SerialHelper helper;
	int status;
	std::string name = helper.GetOSSerialPortName(HAL_SerialPort::HAL_SerialPort_USB1, &status);
	std::cout << "Status: " << status << "USB 1: " << name << std::endl;
	name = helper.GetVISASerialPortName(HAL_SerialPort::HAL_SerialPort_USB1, &status);
	std::cout << "Status: " << status << "VISA: " << name << std::endl;
	try {
		/***********************************************************************
		 * navX-MXP:
		 * - Communication via RoboRIO MXP (SPI, I2C, TTL UART) and USB.
		 * - See http://navx-mxp.kauailabs.com/guidance/selecting-an-interface.
		 *
		 * navX-Micro:
		 * - Communication via I2C (RoboRIO MXP or Onboard) and USB.
		 * - See http://navx-micro.kauailabs.com/guidance/selecting-an-interface.
		 *
		 * Multiple navX-model devices on a single robot are supported.
		 ************************************************************************/
		usleep(100);
		imu_ = new AHRS(SerialPort::Port::kUSB);
	} catch (std::exception& ex ) {
		std::string err_string = "Error instantiating navX MXP:  ";
		err_string += ex.what();
		DriverStation::ReportError(err_string.c_str());
	}


}

void SensorSubsystem::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

void SensorSubsystem::Periodic() {
	// printf("IMU bytes %i, Connected %i, Cal %i\n", (int) imu_->GetByteCount(), imu_->IsConnected(), imu_->IsCalibrating());
	SmartDashboard::PutNumber("IMU Angle", imu_->GetAngle());
	SmartDashboard::PutNumber("IMU Rate", imu_->GetRate());

#ifdef DEBUG_SMARTDASHBOARD
	SmartDashboard::PutBoolean("IMU Connected", imu_->IsConnected());
	SmartDashboard::PutBoolean("IMU Calibrating", imu_->IsCalibrating());

	SmartDashboard::PutNumber("IMU Displacement X", imu_->GetDisplacementX());
	SmartDashboard::PutNumber("IMU Displacement Y", imu_->GetDisplacementY());
	SmartDashboard::PutNumber("IMU Displacement Z", imu_->GetDisplacementZ());
#endif
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
