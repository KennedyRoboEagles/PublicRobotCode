#include <Commands/Motion/DriveWithJoystickCommand.h>
#include "Chassis.h"
#include "../RobotMap.h"
#include <SmartDashboard/SmartDashboard.h>
#include "debug.h"

using namespace frc;

constexpr int kTimeoutMS = 10;
constexpr int kPidId = 0;
constexpr int kSlot = 0;

constexpr double kEncoderCounts = 120;
constexpr double kEncoderCodes = 4 * kEncoderCounts;

constexpr double kWheelDiameter = 6/12.0; // Feet
constexpr double kWheelCircumference = kWheelDiameter * M_PI;

constexpr double kMaxSpeed = 350;

constexpr double kRampRate = 0.15; //  Ramp expressed as seconds to go from neutral throttle to full throttle.

constexpr double kStrafeScrubFactor = 0.75;

static const Chassis::PIDF kLeftFrontPid  = {2, 0.0001,  0, 2.69};
static const Chassis::PIDF kLeftBackPid   = {2, 0.00005, 0, 2.85};
static const Chassis::PIDF kRightFrontPid = {2, 0.0001,  0, 2.69};
static const Chassis::PIDF kRightBackPid  = {2, 0.00005, 0, 2.85};

// Test Robot constants
// static const Chassis::PIDF kLeftFrontPid  = {3, 1.0E-55,  0, 2.3};
// static const Chassis::PIDF kLeftBackPid   = {2, 5.0E-56,  0, 2.21};
// static const Chassis::PIDF kRightFrontPid = {2, 1.0E-05,  0, 2.35};
// static const Chassis::PIDF kRightBackPid  = {2, 1.0E-06, 0, 2.85};

Chassis::Chassis() : Subsystem("Chassis") {
	leftFront_ = new TalonSRX(kChassisFrontLeftID);
	configTalonSRX(leftFront_, kLeftFrontPid);
	leftBack_ = new TalonSRX(kChassisRearLeftChannelID);
	configTalonSRX(leftBack_, kLeftBackPid);
	rightFront_ = new TalonSRX(kChassisFrontRightChannelID);
	configTalonSRX(rightFront_, kRightFrontPid);
	rightBack_ = new TalonSRX(kChassisRearRightChannelID);
	configTalonSRX(rightBack_, kRightBackPid);

	srxWrapper[0] = new SRXWrapper(leftFront_,  SRXWrapper::Mode::kPercentVoltage, kMaxSpeed);
	srxWrapper[0]->SetName("Left Front");
	srxWrapper[1] = new SRXWrapper(leftBack_,   SRXWrapper::Mode::kPercentVoltage, kMaxSpeed);
	srxWrapper[1]->SetName("Left Back");
	srxWrapper[2] = new SRXWrapper(rightFront_, SRXWrapper::Mode::kPercentVoltage, kMaxSpeed);
	srxWrapper[2]->SetName("Right Front");
	srxWrapper[3] = new SRXWrapper(rightBack_,  SRXWrapper::Mode::kPercentVoltage, kMaxSpeed);
	srxWrapper[3]->SetName("Right Back");

	for(int i = 0; i < 4; i++) {
		this->AddChild(srxWrapper[i]);
	}

	// Note: In MecanumDrive the right speed controllers are already inverted
	drive_ = new MecanumDrive(*srxWrapper[0], *srxWrapper[1], *srxWrapper[2], *srxWrapper[3]);
	drive_->SetDeadband(0.02);
	drive_->SetSafetyEnabled(false);

	// Configure Motion magic
	SetMotionMagicParams(200, 200);
}

void Chassis::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
	SetDefaultCommand(new DriveWithJoystickCommand());
}

void Chassis::Periodic() {

#ifdef DEBUG_SMARTDASHBOARD
	if(DriverStation::GetInstance().IsEnabled()) {
		SmartDashboard::PutNumber("Left Front Raw Speed",  leftFront_->GetSelectedSensorVelocity(kPidId));
		SmartDashboard::PutNumber("Left Back Raw Speed",  leftBack_->GetSelectedSensorVelocity(kPidId));
		SmartDashboard::PutNumber("Right Front Raw Speed",  rightFront_->GetSelectedSensorVelocity(kPidId));
		SmartDashboard::PutNumber("Right Back Raw Speed",  rightBack_->GetSelectedSensorVelocity(kPidId));

		SmartDashboard::PutNumber("Left Front Error",  leftFront_->GetClosedLoopError(kPidId));
		SmartDashboard::PutNumber("Left Back Error",  leftBack_->GetClosedLoopError(kPidId));
		SmartDashboard::PutNumber("Right Front Error",  rightFront_->GetClosedLoopError(kPidId));
		SmartDashboard::PutNumber("Right Back Error",  rightBack_->GetClosedLoopError(kPidId));

		SmartDashboard::PutNumber("LF Position", this->GetLFPosition());
		SmartDashboard::PutNumber("LB Position", this->GetLBPosition());
		SmartDashboard::PutNumber("RF Position", this->GetRFPosition());
		SmartDashboard::PutNumber("RB Position", this->GetRBPosition());

		SmartDashboard::PutNumber("Linear Y", this->GetLinearY());
	}
#endif
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void Chassis::configTalonSRX(TalonSRX* talon, PIDF s) {
	talon->ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, kPidId, kTimeoutMS);
	talon->SetInverted(false);
	talon->SetSensorPhase(false);

	talon->SetStatusFramePeriod(StatusFrameEnhanced::Status_3_Quadrature, 20, kTimeoutMS);


	talon->ConfigNominalOutputForward(0.0, kTimeoutMS);
	talon->ConfigNominalOutputReverse(0.0, kTimeoutMS);
	talon->ConfigPeakOutputForward(1.0, kTimeoutMS);
	talon->ConfigPeakOutputReverse(-1.0, kTimeoutMS);

	talon->ConfigClosedloopRamp(kRampRate, kTimeoutMS);

	talon->SelectProfileSlot(0, kPidId);
	talon->Config_kP(kSlot, s.p, kTimeoutMS);
	talon->Config_kI(kSlot, s.i, kTimeoutMS);
	talon->Config_kD(kSlot, s.d, kTimeoutMS);
	talon->Config_kF(kSlot, s.f, kTimeoutMS);

}

void Chassis::SetBreak(bool state) {
	NeutralMode mode = state ? NeutralMode::Brake : NeutralMode::Coast;
	leftFront_->SetNeutralMode(mode);
	leftBack_->SetNeutralMode(mode);
	rightFront_->SetNeutralMode(mode);
	rightBack_->SetNeutralMode(mode);
}


void Chassis::ZeroEncoders() {
	leftFront_->SetSelectedSensorPosition(0, kPidId, kTimeoutMS);
	leftBack_->SetSelectedSensorPosition(0, kPidId, kTimeoutMS);
	rightFront_->SetSelectedSensorPosition(0, kPidId, kTimeoutMS);
	rightBack_->SetSelectedSensorPosition(0, kPidId, kTimeoutMS);
}

void Chassis::SetMotionMagicParams(double cruiseVel, double accel) {
	leftFront_->ConfigMotionCruiseVelocity(cruiseVel, kTimeoutMS);
	leftBack_->ConfigMotionCruiseVelocity(cruiseVel, kTimeoutMS);
	rightFront_->ConfigMotionCruiseVelocity(cruiseVel, kTimeoutMS);
	rightBack_->ConfigMotionCruiseVelocity(cruiseVel, kTimeoutMS);

	leftFront_->ConfigMotionAcceleration(accel, kTimeoutMS);
	leftBack_->ConfigMotionAcceleration(accel, kTimeoutMS);
	rightFront_->ConfigMotionAcceleration(accel, kTimeoutMS);
	rightBack_->ConfigMotionAcceleration(accel, kTimeoutMS);
}

void Chassis::MecanumOpenLoop(double x, double y, double z, bool squareInputs) {
	for(int i = 0; i < 4; i++) {
		srxWrapper[i]->SetMode(SRXWrapper::Mode::kPercentVoltage);
	}

	if(squareInputs) {
		x = std::copysign(x * x, x);
		y = std::copysign(y * y, y);
		z = std::copysign(z * z, z);
	}

	drive_->DriveCartesian(x, y, z);
}

void Chassis::MecanumClosedLoop(double x, double y, double z, bool squareInputs) {
	for(int i = 0; i < 4; i++) {
		srxWrapper[i]->SetMode(SRXWrapper::Mode::kPercentVelocity);
	}

	if(squareInputs) {
		x = std::copysign(x * x, x);
		y = std::copysign(y * y, y);
		z = std::copysign(z * z, z);
	}

	drive_->DriveCartesian(x, y, z);
}

void Chassis::FieldOrientedDrive(double x, double y, double z, bool squareInputs) {
	for(int i = 0; i < 4; i++) {
		srxWrapper[i]->SetMode(SRXWrapper::Mode::kPercentVelocity);
	}

	if(squareInputs) {
		x = std::copysign(x * x, x);
		y = std::copysign(y * y, y);
		z = std::copysign(z * z, z);
	}

	drive_->DriveCartesian(x, y, z, -CommandBase::sensors->GetIMU()->GetAngle());
}

void Chassis::MotionMagicFeet(double left, double right) {
	// Invert the right motors
	right *= -1.0;

	// Convert into Rotations
	left /= kWheelCircumference;
	right /= kWheelCircumference;

	// Convert into codes
	left *= kEncoderCodes;
	right *= kEncoderCodes;

	printf("MM\n");

	leftFront_->Set(ControlMode::MotionMagic, left);
	leftBack_->Set(ControlMode::MotionMagic, left);
	rightFront_->Set(ControlMode::MotionMagic, right);
	rightBack_->Set(ControlMode::MotionMagic, right);
}

void Chassis::Stop() {
	leftFront_->NeutralOutput();
	leftBack_->NeutralOutput();
	rightFront_->NeutralOutput();
	rightBack_->NeutralOutput();
}

double Chassis::GetLeftFrontRealOutput() {
	return leftFront_->GetMotorOutputVoltage() / leftFront_->GetBusVoltage();
}

double Chassis::GetLeftBackRealOutput() {
	return leftBack_->GetMotorOutputVoltage() / leftBack_->GetBusVoltage();
}

double Chassis::GetRightFrontRealOutput() {
	return rightFront_->GetMotorOutputVoltage() / rightFront_->GetBusVoltage();
}

double Chassis::GetRightBackRealOutput() {
	return rightBack_->GetMotorOutputVoltage() / rightBack_->GetBusVoltage();
}

double Chassis::GetLFPosition() {
	return leftFront_->GetSelectedSensorPosition(kPidId) / kEncoderCodes * kWheelCircumference;
}

double Chassis::GetLBPosition() {
	return leftBack_->GetSelectedSensorPosition(kPidId) / kEncoderCodes * kWheelCircumference;
}

double Chassis::GetRFPosition() {
	return -rightFront_->GetSelectedSensorPosition(kPidId) / kEncoderCodes * kWheelCircumference;
}

double Chassis::GetRBPosition() {
	return -rightBack_->GetSelectedSensorPosition(kPidId) / kEncoderCodes * kWheelCircumference;
}

double Chassis::GetLinearX() {
	double leftPos = (GetLBPosition() + GetLFPosition()) / 2.0;
	double rightPos = (GetRBPosition() + GetRFPosition()) / 2.0;
	return (leftPos + rightPos) / 2;
}


double Chassis::GetLinearY() {
	return (-GetLFPosition() + GetRFPosition() + GetLBPosition() - GetRBPosition()) / 4.0 * kStrafeScrubFactor;
}

int Chassis::GetLeftFrontClosedLoopError() {
	return leftFront_->GetClosedLoopError(kPidId);
}

int Chassis::GetLeftBackClosedLoopError() {
	return leftBack_->GetClosedLoopError(kPidId);
}

int Chassis::GetRightFrontClosedLoopError() {
	return rightFront_->GetClosedLoopError(kPidId);
}

int Chassis::GetRightBackClosedLoopError() {
	return rightBack_->GetClosedLoopError(kPidId);
}
