/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <Commands/Motion/DriveLinearStrafeCommandV2.h>
#include "Util/NullPIDOutput.h"

DriveLinearStrafeCommandV2::DriveLinearStrafeCommandV2(double goalX, double goalY, double heading) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(chassis.get());

	angularController_ = new PIDController(0.02, 0.003, 0, sensors->GetIMU(), new NullPIDOutput());
	angularController_->SetInputRange(-180, 180);
	angularController_->SetOutputRange(-0.3, 0.3);
	angularController_->SetContinuous(true);


	linearXController_ = new PIDController(0, 0.000, 0, &linearXSource_, new NullPIDOutput());
	linearXController_->SetAbsoluteTolerance(1.0/12.0);
	linearXController_->SetOutputRange(-0.4, 0.4);

	linearYController_ = new PIDController(0.0, 0.0, 0, &linearYSource_, new NullPIDOutput());
	linearYController_->SetAbsoluteTolerance(2.0/12.0);
	linearYController_->SetOutputRange(-0.7, 0.7);

	goalX_ = goalX;
	goalY_ = goalY;
	heading_ = heading;

	state_ = State::kRun;
}

// Called just before this Command runs the first time
void DriveLinearStrafeCommandV2::Initialize() {
	chassis->Stop();
	chassis->SetBreak(true);
	sensors->GetIMU()->SetPIDSourceType(PIDSourceType::kDisplacement);
	angularController_->Reset();
	angularController_->Enable();
	angularController_->SetSetpoint(heading_);

	linearXController_->Reset();
	linearXController_->Enable();
	linearXController_->SetSetpoint(0);

	linearYController_->Reset();
	linearYController_->Enable();
	linearYController_->SetSetpoint(goalY_);

	state_ = State::kRun;
	chassis->ZeroEncoders();

	timer_.Reset();
	timer_.Start();

}

// Called repeatedly when this Command is scheduled to run
void DriveLinearStrafeCommandV2::Execute() {
	linearXSource_.Set(chassis->GetLinearX());
	linearYSource_.Set(chassis->GetLinearY());

	angularController_->SetSetpoint(heading_);
	linearXController_->SetSetpoint(goalX_);
	linearYController_->SetSetpoint(goalY_);

	double moveX = linearXController_->Get();
	double moveY = linearYController_->Get();
	double rotate = angularController_->Get();


	switch(state_) {
	case State::kRun:
		if(linearYController_->GetError() < 0) {
			moveY = -0.5;
		} else {
			moveY = 0.5;
		}

		if(timer_.HasPeriodPassed(1)) {
			moveY = std::copysign(0.3, moveY);
		}


		if(linearYController_->OnTarget()) {
			state_ = State::kSteadyState;
			timer_.Reset();
			timer_.Start();
		}
		break;
	case State::kSteadyState:
		if(timer_.HasPeriodPassed(1)) {
			state_ = State::kDone;
		}

		break;
	case State::kDone:
		moveX = 0;
		moveY = 0;
		rotate = 0;
		break;
	}

	moveY *= -1; // Need to get move values in phase with linear_y values
#ifdef DEBUG_PRINTF
	printf("[DLC] Strafe Move %f Angular %f\n", moveY, rotate);
#endif
	// NOTE: Move Y is for Y axis movement
	// MOVE X is for X axis of movement
	// Not for joystick axis
	chassis->MecanumClosedLoop(moveY, 0, rotate, false);

}

// Make this return true when this Command no longer needs to run execute()
bool DriveLinearStrafeCommandV2::IsFinished() {
	return state_ == State::kDone;
}

// Called once after isFinished returns true
void DriveLinearStrafeCommandV2::End() {
	chassis->Stop();
	chassis->SetBreak(false);
	linearXController_->Disable();
	linearYController_->Disable();
	angularController_->Disable();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveLinearStrafeCommandV2::Interrupted() {
	this->End();
}
