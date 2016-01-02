#include "TestDaisyFIlterJoystickCommand.h"

TestDaisyFIlterJoystickCommand::TestDaisyFIlterJoystickCommand()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	//this->filter = DaisyFilter::SinglePoleIIRFilter(0.3);
	this->filter = NULL;
}

// Called just before this Command runs the first time
void TestDaisyFIlterJoystickCommand::Initialize() {
	float gain = SmartDashboard::GetNumber("Filter Gain", 0.5);
	printf("Gain for filter: %f\n", gain);
	this->filter = DaisyFilter::SinglePoleIIRFilter(gain);
}

// Called repeatedly when this Command is scheduled to run
void TestDaisyFIlterJoystickCommand::Execute() {
	float y = oi->GetDriverStick()->GetY();
	float filteredY = this->filter->Calculate(y);
	SmartDashboard::PutNumber("Joy Y", y);
	SmartDashboard::PutNumber("FIltered Y", filteredY);
	SmartDashboard::PutNumber("Diff", y - filteredY);
	printf("RawY: %f, FitleredY: %f\n", y, filteredY);
}

// Make this return true when this Command no longer needs to run execute()
bool TestDaisyFIlterJoystickCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void TestDaisyFIlterJoystickCommand::End() {
	if(this->filter != NULL) {
		delete this->filter;
	}
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TestDaisyFIlterJoystickCommand::Interrupted()
{

}
