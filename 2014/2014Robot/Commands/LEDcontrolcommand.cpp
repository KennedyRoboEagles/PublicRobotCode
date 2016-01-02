#include "LEDcontrolcommand.h"

#define LED_DIVISOR (1)



LEDcontrolcommand::LEDcontrolcommand() : CommandBase("LEDControlCommand") {
	Requires(ledSubsystem);
}

// Called just before this Command runs the first time
void LEDcontrolcommand::Initialize() {
	this->count = 0;
	
}

// Called repeatedly when this Command is scheduled to run
void LEDcontrolcommand::Execute() {
	if(DriverStation::GetInstance()->IsAutonomous())
		{ledSubsystem->Run();
		if(this->count % LED_DIVISOR == 0)
		{
			ledSubsystem->Redonoff(true);
			ledSubsystem->Blueonoff(true);
		}
		else
		{
			ledSubsystem->Redonoff(false);
			ledSubsystem->Blueonoff(false);
		}
		this->count++;
		
	
		}
	if(DriverStation::GetInstance()->IsOperatorControl())
	{
		ledSubsystem->Run();
			if(this->count % LED_DIVISOR == 0)
			{
				ledSubsystem->Redonoff(true);
				ledSubsystem->Blueonoff(true);
			}
			else
			{
				ledSubsystem->Redonoff(false);
				ledSubsystem->Blueonoff(false);
			}
			this->count++;
	}
}
// Make this return true when this Command no longer needs to run execute()
bool LEDcontrolcommand::IsFinished(){
		return false;

}

// Called once after isFinished returns true
void LEDcontrolcommand::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LEDcontrolcommand::Interrupted() {
}
