/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <Commands/Motion/DriveLinearForwardCommand.h>
#include <Util/RampUtil.h>
#include <PIDController.h>
#include "Util/NullPIDOutput.h"

using namespace frc;

DriveLinearForwardCommand::DriveLinearForwardCommand(double goal, double heading) {
	// Use Requires() here to declare subsystem dependencies
	Requires(chassis.get());

	angularController_ = new PIDController(0.015, 0.002, 0, sensors->GetIMU(), new NullPIDOutput());
	angularController_->SetInputRange(-180, 180);
	angularController_->SetOutputRange(-0.3, 0.3);
	angularController_->SetContinuous(true);

	linearController_ = new PIDController(0.2, 0.0002, 0, &linearSource_, new NullPIDOutput());
	linearController_->SetAbsoluteTolerance(1.0/12.0);
	linearController_->SetOutputRange(-0.37, 0.37);

	state_ = State::kRun;

	goal_ = goal;
	heading_ = heading;
}

// Called just before this Command runs the first time
void DriveLinearForwardCommand::Initialize() {
	chassis->Stop();
	chassis->SetBreak(true);
	sensors->GetIMU()->SetPIDSourceType(PIDSourceType::kDisplacement);
	angularController_->Reset();
	angularController_->Enable();
	angularController_->SetSetpoint(heading_);

	linearController_->Reset();
	linearController_->Enable();
	linearController_->SetSetpoint(goal_);

	state_ = State::kRun;
	chassis->ZeroEncoders();
}

// Called repeatedly when this Command is scheduled to run
void DriveLinearForwardCommand::Execute() {
	double leftPos = (chassis->GetLBPosition() + chassis->GetLFPosition()) / 2.0;
	double rightPos = (chassis->GetRBPosition() + chassis->GetRFPosition()) / 2.0;

	linearSource_.Set(leftPos);

	double leftErr = leftPos - goal_;
	double rightErr = rightPos - goal_;

	angularController_->SetSetpoint(heading_);
	double rotate = angularController_->Get();

	linearController_->SetSetpoint(goal_);
	double move = linearController_->Get();

#ifdef DEBUG_PRINTF
	printf("[DLC] Angle %f, Left %f, Right %f\n", angularController_->GetError(), leftErr, rightErr);
#endif

	switch(state_) {
	case State::kRun:
//		printf("[DLC] Run\n");
		if(linearSource_.PIDGet() < 1.0 && move > 0.2) {
			printf("!\n");
			move = 0.2;
		}

		if(fabs(linearSource_.PIDGet()) > (fabs(goal_) - 2/12.0)) {
			state_ = State::kSteadyState;
			timer_.Reset();
			timer_.Start();
		}
		break;
	case State::kSteadyState:
//		printf("[DLC] Steady State\n");
		if(timer_.HasPeriodPassed(0.5)) {
			state_ = State::kDone;
		}
		break;
	case State::kDone:
		printf("[DLC] Done\n");
		move = 0;
		rotate = 0;
		break;
	}


#ifdef DEBUG_PRINTF
	printf("[DLC] State %i\n", state_);

	printf("[DLC] Move %f Angular %f\n", move, rotate);
#endif
	chassis->MecanumClosedLoop(0, move, rotate, false);
}

// Make this return true when this Command no longer needs to run execute()
bool DriveLinearForwardCommand::IsFinished() {
	return state_ == State::kDone;
}

// Called once after isFinished returns true
void DriveLinearForwardCommand::End() {
	chassis->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveLinearForwardCommand::Interrupted() {
	this->End();
}
