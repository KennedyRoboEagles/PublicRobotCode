#ifndef SensorSubsystem_H
#define SensorSubsystem_H

#include <Commands/Subsystem.h>
#include <AHRS.h>

class SensorSubsystem : public frc::Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	AHRS* imu_;
public:
	SensorSubsystem();
	void InitDefaultCommand();
	void Periodic() override;

	AHRS* GetIMU() { return imu_; };
};

#endif  // SensorSubsystem_H
