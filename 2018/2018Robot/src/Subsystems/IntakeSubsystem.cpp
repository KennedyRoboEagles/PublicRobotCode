#include "IntakeSubsystem.h"
#include "../RobotMap.h"
#include <DriverStation.h>
#include <Timer.h>
#include <ctre/Phoenix.h>
#include <SmartDashboard/SmartDashboard.h>
#include "debug.h"

using namespace frc;


constexpr int kPidId = 0;
constexpr int kSlot = 0;
constexpr int kTimeoutMS = 10;

constexpr bool kInvertLeft = true;
constexpr bool kInvertRight = false;

IntakeSubsystem::IntakeSubsystem() : Subsystem("ExampleSubsystem") {

	// Note: will probably need to invert on the encoder
	// Positive set values move inward
	// Negative set values move outward

	ErrorCode err;

	leftMotor_ = new TalonSRX(kIntakeLeftId);
	leftMotor_->SetInverted(kInvertLeft);
	leftMotor_->SetNeutralMode(NeutralMode::Brake);

	rightMotor_ = new TalonSRX(kIntakeRightId);
	rightMotor_->SetInverted(kInvertRight);
	rightMotor_->SetNeutralMode(NeutralMode::Brake);
}

void IntakeSubsystem::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
//	SetDefaultCommand(new IntakePrepareForCubeCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void IntakeSubsystem::Periodic() {
#ifdef DEBUG_SMARTDASHBOARD
	SmartDashboard::PutNumber("Intake Left Current", leftMotor_->GetOutputCurrent());
	SmartDashboard::PutNumber("Intake Right Current", rightMotor_->GetOutputCurrent());
#endif
}

void IntakeSubsystem::SetBoth(double value) {
	this->SetLeft(value);
	this->SetRight(value);
}

void IntakeSubsystem::SetLeft(double value) {
	leftMotor_->Set(ControlMode::PercentOutput, value);
}

void IntakeSubsystem::SetRight(double value) {
	rightMotor_->Set(ControlMode::PercentOutput, -value);
}

void IntakeSubsystem::Stop() {
	leftMotor_->NeutralOutput();
	rightMotor_->NeutralOutput();
}
