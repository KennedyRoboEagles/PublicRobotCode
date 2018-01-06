#include <Commands/MotionProfiling/TurnSpecifiedDegrees2Command.h>
#include <cmath>


const static double kP = 0.025f;
const static double kI = 0.000f;
const static double kD = 0.00f;
const static double kF = 0.000f;

const static double kToleranceDegrees = 2.0f;

const static double kMaxSpeed = 0.35;

TurnSpecifiedDegrees2Command::TurnSpecifiedDegrees2Command(double angle, double timeout) {
	Requires(chassis.get());

	timer = new Timer();

	controller = new PIDController(kP, kI, kD, kF, sensorSubsystem->GetYawSource(), this);
	controller->SetInputRange(-180, 180);
	controller->SetOutputRange(-kMaxSpeed , kMaxSpeed);
	controller->SetAbsoluteTolerance(kToleranceDegrees);
	controller->SetContinuous(true);

	filter = DaisyFilter::MovingAverageFilter(5);

	state = kTurning;
	finished = false;
	steadyStateStart = 0;

	output = 0;
	goalAngle = angle;
	this->timeout = timeout;
}

// Called just before this Command runs the first time
void TurnSpecifiedDegrees2Command::Initialize() {
	output = 0;
	sensorSubsystem->ZeroYaw();
	timer->Reset();
	timer->Start();

	chassis->EnableBrake();

//	controller->Reset();
//	controller->SetSetpoint(goalAngle);
//	controller->Enable();

	state = kTurning;
}

// Called repeatedly when this Command is scheduled to run
void TurnSpecifiedDegrees2Command::Execute() {
	SmartDashboard::PutNumber("Turn Error", controller->GetError());
	SmartDashboard::PutNumber("Turn Output", controller->Get());
	SmartDashboard::PutBoolean("Turn On Target", controller->OnTarget());

	double currentAngle = sensorSubsystem->GetYaw();
	double angleDifference = goalAngle - currentAngle;
	double avgAngleDifference = filter->Calculate(angleDifference);

	printf("Time %f, Error Avg %f\n", timer->Get(), avgAngleDifference);

	double turnRate = 0;
	printf("State %i\n", state);

	switch (state) {
		case kTurning:

			if(fabs(angleDifference) > 70.0)  {
				turnRate = 0.5;
			} else if(fabs(angleDifference) > 60.0) {
				turnRate = 0.30;
			} else if(fabs(angleDifference) > 45.0) {
				turnRate = 0.24;
			} else if(fabs(angleDifference) > 20.0) {
				turnRate = 0.15;
			} else {
				printf("Changing State\n");
				steadyStateStart = timer->Get();
				controller->Reset();
				controller->SetSetpoint(goalAngle);
				controller->Enable();
				state = kSteadyState;
			}
			if (angleDifference < 0) {
				chassis->ArcadeDrive(0.0, -turnRate);
			} else {
				chassis->ArcadeDrive(0.0, turnRate);
			}
			break;
		case kSteadyState:
//			if(fabs(avgAngleDifference) < 2.0) {
//				printf("Ending\n");
//				state = kEnd;
//			}
			break;
		case kEnd:
			printf("End\n");
			chassis->Stop();
			break;
		default:
			state = kEnd;
			break;
	}
}

// Make this return true when this Command no longer needs to run execute()
bool TurnSpecifiedDegrees2Command::IsFinished() {
	return timer->HasPeriodPassed(timeout) || (state == kEnd);
}

// Called once after isFinished returns true
void TurnSpecifiedDegrees2Command::End() {
	this->cleanUp();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TurnSpecifiedDegrees2Command::Interrupted() {
	this->cleanUp();
}

void TurnSpecifiedDegrees2Command::PIDWrite(double output) {
	chassis->ArcadeDrive(0,output);
}

void TurnSpecifiedDegrees2Command::cleanUp() {
//	chassis->DisableBrake();
	timer->Stop();
	controller->Disable();
	chassis->Stop();
}
