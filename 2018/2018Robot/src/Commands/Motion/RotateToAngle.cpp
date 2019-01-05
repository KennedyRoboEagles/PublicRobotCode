#include <Commands/Motion/RotateToAngle.h>
#include <Util/NullPIDOutput.h>

const double kTurnMax = 0.35;
const double kP = 0.02;
const double kI = 0.00;
const double kD = 0;
const double kF = 0;

RotateToAngle::RotateToAngle(double goal) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(chassis.get());

	goal_ = goal;

	controller_ = new PIDController(kP, kI, kD, kF, sensors->GetIMU(), new NullPIDOutput());
	controller_->SetInputRange(-180, 180);
	controller_->SetContinuous(true);
	controller_->SetOutputRange(-kTurnMax, kTurnMax);
	controller_->SetAbsoluteTolerance(2);

	state_ = State::kRun;
}

// Called just before this Command runs the first time
void RotateToAngle::Initialize() {
	state_ = State::kRun;
	chassis->Stop();
	controller_->Reset();
	controller_->Enable();
}

// Called repeatedly when this Command is scheduled to run
void RotateToAngle::Execute() {
#ifdef DEBUG_PRINTF
	printf("[Turn] Error %f\n", controller_->GetError());
#endif
	controller_->SetSetpoint(goal_);
	double rotate = controller_->Get();

	switch(state_) {
	case State::kRun:
		if(controller_->OnTarget()) {
			state_ = State::kSteadyState;
			timer_.Reset();
			timer_.Start();
		}
		break;
	case State::kSteadyState:
		if(timer_.HasPeriodPassed(0.5)) {
			state_ = State::kDone;
		}
		break;
	case State::kDone:
		rotate = 0;
		break;
	}

	printf("[Turn] State %i\n", state_);
	chassis->MecanumClosedLoop(0, 0, rotate, false);
}

// Make this return true when this Command no longer needs to run execute()
bool RotateToAngle::IsFinished() {
	return state_ == State::kDone;
}

// Called once after isFinished returns true
void RotateToAngle::End() {
	chassis->Stop();
	controller_->Disable();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RotateToAngle::Interrupted() {
	this->End();
}
