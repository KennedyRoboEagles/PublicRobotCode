#include "TurnSpecifiedDegreesCommand.h"
#include "math.h"

// If we're within this # of degrees to target, then we're good.

#define DEGREES_PRECISION 1.5


/*
 * This command turns the number of degrees specified in the dashboard field.
 */
//Positive angles to the right
TurnSpecifiedDegreesCommand::TurnSpecifiedDegreesCommand(double degreesToTurn)
	: CommandBase("TurnSpecifiedDegreesCommand") {
	Requires(chassis.get());
	this->goalAngle = degreesToTurn;
	this->timer = new Timer();
	this->finished = false;
}

// Called just before this Command runs the first time
void TurnSpecifiedDegreesCommand::Initialize() {
	this->finished = false;
	chassis->EnableBrake();
//	chassis->SetReversed(false);
	sensorSubsystem->ZeroYaw();
	this->timer->Reset();
	this->timer->Start();
	printf("TurnSpecifiedDegreesCommand %f\n", this->goalAngle);
}

// Called repeatedly when this Command is scheduled to run
void TurnSpecifiedDegreesCommand::Execute() {
//	double currentAngle = sensorSubsystem->GetIMU()->GetYaw();
	double currentAngle = sensorSubsystem->GetYaw();
	double angleDifference = goalAngle - currentAngle;
	
	SmartDashboard::PutNumber("Goal angle", goalAngle);
	SmartDashboard::PutNumber("Angle difference", fabs(angleDifference));
	printf("Angle difference %f goalAngle %f currentAngle %f\n", angleDifference, goalAngle, currentAngle);
	
	double turnRate = 0;
	
	if (fabs(angleDifference) < DEGREES_PRECISION) {
		chassis->Stop();
		finished = true;
	} else {
		// We slow our rate of turn as we get close to the angle we want.
		// These values are guesses.  A PID would be better here.

		if(fabs(angleDifference) > 60.0)  {
			turnRate = 0.30;
		} else if(fabs(angleDifference) > 45.0) {
			turnRate = 0.25;
		} else if(fabs(angleDifference) > 20.0) {
			turnRate = 0.20;
		} else if(fabs(angleDifference) > 15.0) {
			turnRate = 0.15;
		} else {
			turnRate = 0.13;
		}

		SmartDashboard::PutNumber("turn rate", turnRate);
		
		if (angleDifference < 0) {
			chassis->ArcadeDrive(0.0, -turnRate);
		} else {
			chassis->ArcadeDrive(0.0, turnRate);
		}
	}
}

// Make this return true when this Command no longer needs to run execute()
bool TurnSpecifiedDegreesCommand::IsFinished() {
	return finished || this->timer->HasPeriodPassed(5);
}

// Called once after isFinished returns true
void TurnSpecifiedDegreesCommand::End() {
	printf("TurnSpecifiedDegreesCommand completed.\n");
	this->cleanUp();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TurnSpecifiedDegreesCommand::Interrupted() {
	printf("TurnSpecifiedDegreesCommand interrupted.\n");
	this->cleanUp();
}

void TurnSpecifiedDegreesCommand::cleanUp() {
	chassis->Stop();
//	chassis->DisableBrake();
	this->timer->Stop();
}
