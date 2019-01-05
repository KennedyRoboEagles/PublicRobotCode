#include <Commands/Motion/Depercated/FieldOrientedDriveCommand.h>
#include <Preferences.h>

const std::string kKey = "Scale Rotation";

FieldOrientedDriveCommand::FieldOrientedDriveCommand() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(chassis.get());
	if(!Preferences::GetInstance()->ContainsKey(kKey)) {
		Preferences::GetInstance()->PutDouble(kKey, 1.0);
	}

	this->SetPIDSourceType(PIDSourceType::kRate);

	rateController_ = new PIDController(0.001, 0, 0, 0, this, this);
	rateController_->SetInputRange(-6, 6);
	rateController_->SetOutputRange(-0.72, 0.72);

}


// Called just before this Command runs the first time
void FieldOrientedDriveCommand::Initialize() {
	SmartDashboard::PutData(rateController_);

	chassis->Stop();

	turnComp_ = 0;
	rateController_->Reset();
	rateController_->Enable();
}

// Called repeatedly when this Command is scheduled to run
void FieldOrientedDriveCommand::Execute() {
	double x = oi->GetStickStrafe();
	double y = oi->GetStickMove();
	double z = oi->GetStickRotate();

	z *= Preferences::GetInstance()->GetDouble(kKey, 1.0);
	z = std::copysign(z*z, z);

	if(oi->GetStick()->GetRawButton(1)) {
		z = 0;
	} else if(oi->GetStick()->GetRawButton(2)) {
		z = 0;
		y = 0;
	}


	rateController_->SetSetpoint(z * 3.0);

	SmartDashboard::PutNumber("Turn Setpoint", rateController_->GetSetpoint());
	SmartDashboard::PutNumber("Turn Error", rateController_->GetAvgError());
	SmartDashboard::PutNumber("Turn Output", rateController_->Get());

//	chassis->MecanumClosedLoop(x, y, turnComp_, false);
	x = std::copysign(x*x, x);
	y = std::copysign(y*y, y);

	chassis->FieldOrientedDrive(x, y, turnComp_, false);

}

// Make this return true when this Command no longer needs to run execute()
bool FieldOrientedDriveCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void FieldOrientedDriveCommand::End() {
	chassis->Stop();
	rateController_->Disable();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void FieldOrientedDriveCommand::Interrupted() {
	chassis->Stop();
	rateController_->Disable();
}

void FieldOrientedDriveCommand::PIDWrite(double output) {
	turnComp_ = output;
}

double FieldOrientedDriveCommand::PIDGet() {
	return sensors->GetIMU()->GetRate();
}
