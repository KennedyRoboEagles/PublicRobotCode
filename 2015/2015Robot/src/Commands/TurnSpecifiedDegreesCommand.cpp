#include "TurnSpecifiedDegreesCommand.h"
#include "math.h"

// If we're within this # of degrees to target, then we're good.

#define DEGREES_PRECISION 1.5


/*
 * This command turns the number of degrees specified in the dashboard field.
 */
TurnSpecifiedDegreesCommand::TurnSpecifiedDegreesCommand(float degreesToTurn) 
	: CommandBase("TurnSpecifiedDegreesCommand") {
	Requires(chassis);
	this->degreesToTurn = degreesToTurn;
}

// Called just before this Command runs the first time
void TurnSpecifiedDegreesCommand::Initialize() {
	this->finished = false;
	sensorSubsystem->GetIMU()->ZeroYaw();
	this->startingAngle = sensorSubsystem->GetIMU()->GetYaw();
	this->goalAngle = startingAngle + this->degreesToTurn;
	printf("TurnSpecifiedDegreesCommand %f\n", this->degreesToTurn);
}

// Called repeatedly when this Command is scheduled to run
void TurnSpecifiedDegreesCommand::Execute() {
	float currentAngle = sensorSubsystem->GetIMU()->GetYaw();
	float angleDifference = goalAngle - currentAngle;
	
	SmartDashboard::PutNumber("Goal angle", goalAngle);
	SmartDashboard::PutNumber("Angle difference", fabs(angleDifference));
	printf("Angle difference %f goalAngle %f currentAngle %f\n", angleDifference, goalAngle, currentAngle);
	
	float turnRate = 0;
	
	if (fabs(angleDifference) < DEGREES_PRECISION) {
		chassis->Stop();
		finished = true;
	} else {
		// We slow our rate of turn as we get close to the angle we want.
		// These values are guesses.  A PID would be better here.

		if(fabs(angleDifference) > 60.0)  {
			turnRate = 0.75;
		} else if(fabs(angleDifference) > 45.0) {
			turnRate = 0.45;
		} else if(fabs(angleDifference) > 20.0) {
			turnRate = 0.43;
		} else if(fabs(angleDifference) > 15.0) {
			turnRate = 0.40;
		} else {
			turnRate = 0.35;
		}

		//if (angleDifference > 10 || angleDifference < -10) {
		//	turnRate = 0.5;
		//} else {
		//	// Look at changing this at competition
		//	turnRate = 0.25;
		//}
		
		SmartDashboard::PutNumber("turn rate", turnRate);
		
		if (angleDifference > 0) {
			chassis->GetDrive()->ArcadeDrive(0.0, -turnRate);
		} else {
			chassis->GetDrive()->ArcadeDrive(0.0, turnRate);
		}
	}
}

// Make this return true when this Command no longer needs to run execute()
bool TurnSpecifiedDegreesCommand::IsFinished() {
	return finished;	
}

// Called once after isFinished returns true
void TurnSpecifiedDegreesCommand::End() {
	printf("TurnSpecifiedDegreesCommand completed.\n");
	chassis->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TurnSpecifiedDegreesCommand::Interrupted() {
	chassis->Stop();
}
