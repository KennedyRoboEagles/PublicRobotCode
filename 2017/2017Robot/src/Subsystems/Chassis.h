#ifndef Chassis_H
#define Chassis_H

#include <WPILib.h>
#include <Commands/Subsystem.h>
#include <RobotConstants.h>

#ifndef PRACTICE_BOT
#include <CANTalon.h>
#else
#include <CANJaguar.h>
#endif

class Chassis : public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

#ifndef PRACTICE_BOT
	CANTalon *leftMaster;
	CANTalon *leftSlave;

	CANTalon *rightMaster;
	CANTalon *rightSlave;
#else
	CANJaguar *leftMaster;
	CANJaguar *leftSlave;

	CANJaguar *rightMaster;
	CANJaguar *rightSlave;
#endif

	bool reverse = false;
public:
	Chassis();
	void InitDefaultCommand();
	void Stop();
	void ArcadeDrive(double y, double x, bool squared=false);
	void ArcadeDrive(Joystick* stick, bool squared=false);
	void TankDrive(double left, double right);
	CANSpeedController* GetLeftMaster();
	CANSpeedController* GetRightMaster();
	CANSpeedController* GetLeftSlave();
	CANSpeedController* GetRightSlave();

	void ToggeleReverseDrive();
	void SetReversed(bool reversed);
	bool IsReversed();

	void EnableBrake();
	void DisableBrake();
};

#endif  // Chassis_H
