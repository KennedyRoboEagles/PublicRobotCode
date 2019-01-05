#ifndef ElevatorSubsystem_H
#define ElevatorSubsystem_H

#include <Commands/Subsystem.h>
#include <SpeedController.h>
#include <DigitalInput.h>
#include <Encoder.h>
#include <Timer.h>
#include <ctre/Phoenix.h>
#include "Subsystems/IntakeSubsystem.h"

class ElevatorSubsystem : public frc::Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	TalonSRX* motorMaster_;
	TalonSRX* motorSlave_;

	frc::DigitalInput* low1stStageLimit_;
	frc::DigitalInput* low3rdStageLimit_;
	frc::DigitalInput* startingPosLimit_;
	frc::DigitalInput* highLimit_;
	frc::Encoder* encoder_;

	frc::Timer timer_;

	bool calibrated_;
	bool disabled_;
	bool firstPeriodic_;
	bool intakeInPosition_;

	std::shared_ptr<IntakeSubsystem> intakePtr_;

	void _Up();
	void _Down();

public:
	ElevatorSubsystem();
	ElevatorSubsystem(std::shared_ptr<IntakeSubsystem> intakePtr);
	void InitDefaultCommand();

	void Periodic() override;

	void Up();
	void Down();
	void Stop();

	void Stall();

	bool IsCalibrated() { return calibrated_ && !disabled_; }

	bool IsAtStartingConfig() { return startingPosLimit_->Get(); }
	bool Is1stStageAtBottom() { /*return low1stStageLimit_->Get(); */ return this->IsAtStartingConfig(); }
	bool Is3rdStageAtBottom() { return low3rdStageLimit_->Get(); }
	bool IsAtBottom() { return this->Is1stStageAtBottom() && this->Is3rdStageAtBottom(); }
	bool IsAtTop() { return highLimit_->Get(); }

	double GetPosition();
};

#endif  // ElevatorSubsystem_H
