#include "ElevatorSubsystem.h"
#include "../RobotMap.h"
#include <ctre/Phoenix.h>
#include <SmartDashboard/SmartDashboard.h>
#include <DriverStation.h>
#include <Timer.h>
#include <Spark.h>
#include "debug.h"

using namespace frc;

constexpr int kTimeoutMS = 10;

constexpr double kIntakeGoalAngle = 75;

constexpr double kUpMoveSpeed = -0.6;
constexpr double kDownMoveSpeed = 0.6;
constexpr double kStallSpeed = 0;

constexpr double kHeightOffset = 3;


constexpr double kInchPerRot = 3.118 * M_PI * (12.0/36.0);
constexpr double kDistancePerTick = kInchPerRot / 120;
constexpr double kMaxHeight = 6 * 12 + 8;

constexpr bool kEnableCalibration = true;

ElevatorSubsystem::ElevatorSubsystem() : ElevatorSubsystem(nullptr) {
	printf("[Elevator] !!!!!!NOT USING INTAKE FOR ELEVATOR!!!!!\n");
}

ElevatorSubsystem::ElevatorSubsystem(std::shared_ptr<IntakeSubsystem> intakePtr) : Subsystem("ElevatorSubsystem") {
	intakePtr_ = intakePtr;
	motorMaster_ = new TalonSRX(kElevatorMasterID);

	motorMaster_->ConfigContinuousCurrentLimit(5, kTimeoutMS);
	motorMaster_->ConfigPeakCurrentLimit(7, kTimeoutMS);
	motorMaster_->ConfigPeakCurrentDuration(100, kTimeoutMS);
	motorMaster_->EnableCurrentLimit(true);

	motorSlave_ = new TalonSRX(kElevatorSlaveID);
	motorSlave_->Set(ControlMode::Follower, motorMaster_->GetDeviceID());
	motorSlave_->ConfigContinuousCurrentLimit(5, kTimeoutMS);
	motorSlave_->ConfigPeakCurrentLimit(7, kTimeoutMS);
	motorSlave_->ConfigPeakCurrentDuration(100, kTimeoutMS);
	motorSlave_->EnableCurrentLimit(true);

	motorMaster_->SetNeutralMode(NeutralMode::Brake);
	motorSlave_->SetNeutralMode(NeutralMode::Brake);

	low1stStageLimit_ = new DigitalInput(kElevatorLow1stStageLimitChannel);
	low3rdStageLimit_ = new DigitalInput(kElevatorLow3rdStageLimitChannel);
	startingPosLimit_ = new DigitalInput(kElevatorStartingConfigChannel);
	highLimit_ = new DigitalInput(kElevatorHighLimitChannel);
	encoder_ = new Encoder(kElevatorEncoderAChannel, kElevatorEncoderBChannel);
	encoder_->SetDistancePerPulse(kDistancePerTick);

	calibrated_ = false;
	disabled_ = false;
	firstPeriodic_ = true;
	intakeInPosition_ = false;
	timer_.Reset();
}

void ElevatorSubsystem::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

void ElevatorSubsystem::Periodic() {
	// No intake
	intakeInPosition_ = true;

	if(DriverStation::GetInstance().IsEnabled() && intakeInPosition_ && kEnableCalibration && !calibrated_) {
		if(firstPeriodic_) {
			timer_.Start();
			firstPeriodic_ = false;
		}

#ifdef DEBUG_PRINTF
		printf("[Elevator] Calibrating\n");
#endif
		if(disabled_ || timer_.HasPeriodPassed(10) /* || this->IsAtBottom() */) {
			// The elevator is not in position, disable
			disabled_ = true;
			this->Stop();
#ifdef DEBUG_PRINTF
			printf("[Elevator] Calibrate timeout - disabled\n");
#endif
		} else if(this->IsAtStartingConfig()) {
			calibrated_ = true;
			encoder_->Reset();
			this->Stop();
		} else {
			this->_Down();
		}
	}

	Faults faults;
	motorMaster_->GetFaults(faults);
	SmartDashboard::PutString("Faults",faults.ToString());

#ifdef DEBUG_PRINTF
	SmartDashboard::PutNumber("Elevator Master Current", motorMaster_->GetOutputCurrent());
	SmartDashboard::PutNumber("Elevator Slave Current", motorSlave_->GetOutputCurrent());
	SmartDashboard::PutBoolean("Elevator Disabled", disabled_);
	SmartDashboard::PutBoolean("Elevator Calibrated", calibrated_);
	SmartDashboard::PutBoolean("Elevator Stage 1 Bottom", this->Is1stStageAtBottom());
	SmartDashboard::PutBoolean("Elevator Stage 3 Bottom", this->Is3rdStageAtBottom());
	SmartDashboard::PutBoolean("Elevator At Bottom", this->IsAtBottom());
	SmartDashboard::PutBoolean("Elevator At Top", this->IsAtTop());
	SmartDashboard::PutBoolean("Elevator At Starting Pos", this->IsAtStartingConfig());
	SmartDashboard::PutNumber("Elevator Height", this->GetPosition());
	SmartDashboard::PutNumber("Elevator Height Raw", encoder_->GetRaw());
#endif
}
// Put methods for controlling this subsystem
// here. Call these from Commands.

double ElevatorSubsystem::GetPosition() {
	return encoder_->GetDistance() + kHeightOffset;
}

void ElevatorSubsystem::_Up() {
	motorMaster_->Set(ControlMode::PercentOutput, kUpMoveSpeed);
}

void ElevatorSubsystem::_Down() {
	motorMaster_->Set(ControlMode::PercentOutput, kDownMoveSpeed);
}

void ElevatorSubsystem::Up() {
	if(kEnableCalibration  && !calibrated_) {
#ifdef DEBUG_PRINTF
		printf("[Elevator] Ignoring up command - calibrating\n");
#endif
	} else if(disabled_) {
		// We have reached a error state, stop the elevator
#ifdef DEBUG_PRINTF
		printf("[Elevator] Disabled\n");
#endif
		disabled_ = true;
		this->Stop();
	} /* else if(this->IsAtBottom()) {
		// Hit the bottom limit just stop the elevator
		// We should never hit this limit when going up
		printf("[Elevator] Hit Bottom Limit stopping\n");
		disabled_ = true;
		this->Stop();
		this->Stop();
	} */else if(this->IsAtTop()) {
		// We have hit the top limit switch
#ifdef DEBUG_PRINTF
		printf("[Elevator] Hit top limit\n");
#endif
		this->Stop();
	} else if(this->GetPosition() > kMaxHeight) {
		// We have hit the top allowed limit of the elevator
		// This should be before the mechanical limit of the elevator
#ifdef DEBUG_PRINTF
		printf("[Elevator] Reached artificial top limit\n");
#endif
		this->Stop();
	} else {
#ifdef DEBUG_PRINTF
		printf("[Elevator] Moving up");
#endif
		this->_Up();
	}
}

void ElevatorSubsystem::Down() {
	if(kEnableCalibration  && !calibrated_) {
#ifdef DEBUG_PRINTF
		printf("[Elevator] Ignoring down command - calibrating\n");
#endif
	} else if(this->IsAtBottom()) {
		// Hit the bottom limit just stop the elevator
#ifdef DEBUG_PRINTF
		printf("[Elevator] Hit Bottom Limit stopping\n");
#endif
		this->Stop();
	} else if(disabled_) {
#ifdef DEBUG_PRINTF
		printf("[Elevator] Disabled\n");
#endif
		this->Stop();
	} /*else if(this->IsAtTop()) {

		// We have hit the top limit switch
		// This limit should never be hit in any situation
		printf("[Elevator] Hit top limit Disabling\n");
		disabled_ = true;
		this->Stop();
	} */ else {
#ifdef DEBUG_PRINTF
		printf("[Elevator] Moving down\n");
#endif
		this->_Down();
	}
}

void ElevatorSubsystem::Stall() {
	// Use this to keep the elevator in place when it is raised up
	// Apply just enough power to the motors so the elevator does not creep back down
	motorMaster_->Set(ControlMode::PercentOutput, kStallSpeed);
	motorSlave_->Set(ControlMode::PercentOutput, kStallSpeed);
}

void ElevatorSubsystem::Stop() {
	motorMaster_->NeutralOutput();
}
