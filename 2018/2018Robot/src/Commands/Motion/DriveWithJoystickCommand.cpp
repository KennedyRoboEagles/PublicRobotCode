#include <Commands/Motion/DriveWithJoystickCommand.h>
#include <Preferences.h>
#include <Util/NullPIDOutput.h>
#include "Constants.h"

const std::string kKey = "Scale Rotation";
constexpr double kDeadZone = 0.07;

constexpr int kFODButton = kUseXboxController ? 1 : 2;
constexpr int kZCurvePower = kUseXboxController ? 3 : 3;

DriveWithJoystickCommand::DriveWithJoystickCommand() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(chassis.get());

	fodLast_ = false;
	fod_ = false;

	xCurve = new JoystickResponseCurve( .4, 3, 1.0, kDeadZone);
    yCurve = new JoystickResponseCurve( .4, 3, 1.0, kDeadZone);
	zCurve = new JoystickResponseCurve( .4, kZCurvePower, 0.85, kDeadZone);

	angularController_ = new PIDController(0.02, 0.002, 0, sensors->GetIMU(), new NullPIDOutput());
	angularController_->SetInputRange(-180, 180);
	angularController_->SetOutputRange(-0.3, 0.3);
	angularController_->SetContinuous(true);

	heading_ = 0;
}

// Called just before this Command runs the first time
void DriveWithJoystickCommand::Initialize() {
	chassis->Stop();
	chassis->SetBreak(false);
}

// Called repeatedly when this Command is scheduled to run
void DriveWithJoystickCommand::Execute() {
	double x = oi->GetStickStrafe();
	double y = oi->GetStickMove();
	double z = oi->GetStickRotate();

	x = xCurve->Transform(x);
	y = yCurve->Transform(y);
	z = zCurve->Transform(z);

	bool fod_ = oi->GetStick()->GetAButton();

	if(fod_) {
		if(!fodLast_) {
#ifdef INFO_PRINTF
			printf("Entering field oriented drive\n");
#endif
			heading_ = sensors->GetIMU()->GetYaw();
			angularController_->Reset();
			angularController_->Enable();
		}
#ifdef DEBUG_PRINTF
		printf("In field oriented drive\n");
#endif
		angularController_->SetSetpoint(heading_);

		double rotate = angularController_->Get();
		chassis->FieldOrientedDrive(x, y, rotate, false);
	} else {
		angularController_->Disable();
		chassis->MecanumClosedLoop(x, y, z);
	}

	fodLast_ = fod_;

	// SmartDashboard::PutNumber("Joy Z", z);
	SmartDashboard::PutBoolean("FOD", fod_);
}

// Make this return true when this Command no longer needs to run execute()
bool DriveWithJoystickCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void DriveWithJoystickCommand::End() {
	chassis->Stop();
	chassis->SetBreak(false);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveWithJoystickCommand::Interrupted() {
	this->End();
}
