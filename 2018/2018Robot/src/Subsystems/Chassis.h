#ifndef Chassis_H
#define Chassis_H

#include <Commands/Subsystem.h>
#include <SpeedController.h>
#include <SmartDashboard/SendableBase.h>
#include <support/deprecated.h>
#include <Drive/MecanumDrive.h>
#include <memory>
#include <PIDController.h>

#include <ctre/Phoenix.h>

#include "Util/SRXWrapper.h"

class Chassis : public frc::Subsystem {
public:
	struct PIDF {
		double p;
		double i;
		double d;
		double f;

		PIDF(double p, double i, double d, double f)
			: p(p), i(i), d(d), f(f) {}
	};
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	TalonSRX* leftFront_;
	TalonSRX* leftBack_;
	TalonSRX* rightFront_;
	TalonSRX* rightBack_;

	SRXWrapper* srxWrapper[4];

	frc::MecanumDrive* drive_;

	void configTalonSRX(TalonSRX* talon, PIDF s);
public:
	Chassis();
	void InitDefaultCommand();
	void Periodic();

	void SetBreak(bool state);
	void ZeroEncoders();

	void SetMotionMagicParams(double cruiseVel, double accel);

	void MecanumOpenLoop(double x, double y, double z, bool squareInputs = true);
	void MecanumClosedLoop(double x, double y, double z, bool squareInputs = true);
	void FieldOrientedDrive(double x, double y, double z, bool squareInputs = true);

	void MotionMagicFeet(double left, double right);
	void Stop();

	double GetLeftFrontRealOutput();
	double GetLeftBackRealOutput();
	double GetRightFrontRealOutput();
	double GetRightBackRealOutput();

	double GetLFPosition();
	double GetLBPosition();
	double GetRFPosition();
	double GetRBPosition();

	double GetLinearX();
	double GetLinearY();

	int GetLeftFrontClosedLoopError();
	int GetLeftBackClosedLoopError();
	int GetRightFrontClosedLoopError();
	int GetRightBackClosedLoopError();

	TalonSRX* GetLeftFront() { return leftFront_; }
	TalonSRX* GetLeftBack() { return leftBack_; }
	TalonSRX* GetRightFront() { return rightFront_; }
	TalonSRX* GetRightBack() { return rightBack_; }

};

#endif  // Chassis_H
