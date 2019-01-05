#ifndef IntakeSubsystem_H
#define IntakeSubsystem_H

#include <ctre/Phoenix.h>
#include <Encoder.h>
#include <DigitalInput.h>
#include <Timer.h>
#include <Commands/Subsystem.h>

class IntakeSubsystem : public frc::Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

	TalonSRX* leftMotor_;
	TalonSRX* rightMotor_;
public:
	IntakeSubsystem();
	void InitDefaultCommand();

	void Periodic() override;


	void SetBoth(double value);
	void SetLeft(double value);
	void SetRight(double value);

	TalonSRX* GetLeftMotor() { return leftMotor_; }
	TalonSRX* GetRightMotor() { return rightMotor_; }

	void Stop();

};

#endif  // IntakeSubsystem_H
