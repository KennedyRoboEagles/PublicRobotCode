#ifndef CHASSIS_H
#define CHASSIS_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

#define CHASSIS_WHEEL_DIAMETER (4)
//TODO Find the number of teeth each gear has
#define CHASSIS_DRIVE_GEAR_TEETH (16)
#define CHASSIS_WHEEL_GEAR_TEETH (26)
#define CHASSIS_GEAR_RATIO (CHASSIS_DRIVE_GEAR_TEETH / CHASSIS_WHEEL_GEAR_TEETH)
#define CHASSIS_ENCODER_TICKS_PER_REVOLUTION (120)
#define CHASSIS_PI (3.14159265359)
#define CHASSIS_TICKS_PER_INCH ((CHASSIS_ENCODER_TICKS_PER_REVOLUTION * CHASSIS_GEAR_RATIO) / (CHASSIS_PI * CHASSIS_WHEEL_DIAMETER))

/**
 *
 *
 * @author nowireless
 */
class Chassis: public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	SpeedController *leftFrontMotor;
	SpeedController *leftBackMotor;
	SpeedController *rightFrontMotor;
	SpeedController *rightBackMotor;
	
	RobotDrive *drive;
public:
	Chassis();
	void InitDefaultCommand();
	void Stop();
	void ArcadeDrive(Joystick *stick);
	void ArcadeDrive(float move, float rotate);
	void TankDrive(float left, float right);
	void TurnLeft(float rate);
	void TurnRight(float rate);
	RobotDrive *GetRobotDrive();
	SpeedController *GetLeftFrontMotor();
	SpeedController *GetLeftBackMotor();
	SpeedController *GetRightFrontMotor();
	SpeedController *GetRightBackMotor();
	float InchesToTicks(int inches);
};
#endif
