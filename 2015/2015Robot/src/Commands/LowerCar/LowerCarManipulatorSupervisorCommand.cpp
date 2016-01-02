#include "LowerCarManipulatorSupervisorCommand.h"

LowerCarManipulatorSupervisorCommand::LowerCarManipulatorSupervisorCommand()
{
	Requires(lowerCarManipulatorSubsystem);
}

void LowerCarManipulatorSupervisorCommand::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void LowerCarManipulatorSupervisorCommand::Execute()
{

	std::string state = "Unknown State";
	std::string position = "Position";
	switch (lowerCarManipulatorSubsystem->GetCurrentState())
	{
		case LowerCarManipulatorSubsystem::MS_Unknown:
			lowerCarManipulatorSubsystem->SetCurrentState(LowerCarManipulatorSubsystem::MS_Calibrating);
			break;
		case LowerCarManipulatorSubsystem::MS_Calibrating:
			state = "MS_Calibrating";
			lowerCarManipulatorSubsystem->Calibrate();
			break;
		case LowerCarManipulatorSubsystem::MS_AcquireTote:
			state = "MS_AcquireTote";
			lowerCarManipulatorSubsystem->AcquireTote();
			break;
		case LowerCarManipulatorSubsystem::MS_ReleaseTote:
			state = "MS_ReleaseTote";
			lowerCarManipulatorSubsystem->ReleaseTote();
			break;
		case LowerCarManipulatorSubsystem::MS_OpenForNarrowTote:
			state = "MS_OpenForNarrowTote";
			lowerCarManipulatorSubsystem->SetSize(20);
			break;
		case LowerCarManipulatorSubsystem::MS_OpenForWideTote:
			state = "MS_OpenForWideTote";
			lowerCarManipulatorSubsystem->SetSize(28.5);
			break;
		case LowerCarManipulatorSubsystem::MS_CloseForNarrowTote:
			state = "MS_CloseForNarrowTote";
			lowerCarManipulatorSubsystem->SetSize(16);
			break;
		case LowerCarManipulatorSubsystem::MS_CloseForBin:
			state = "MS_CloseForBin";
			lowerCarManipulatorSubsystem->SetSize(13);
	}

	lowerCarManipulatorSubsystem->GetSD()->UpdateState(state);
	lowerCarManipulatorSubsystem->GetSD()->UpdatePosition(position);
	lowerCarManipulatorSubsystem->GetSD()->UpdateCurrentDraw(lowerCarManipulatorSubsystem->GetManipulatorMotorCurrent());
	lowerCarManipulatorSubsystem->GetSD()->UpdateIsDone(lowerCarManipulatorSubsystem->IsDone());
	lowerCarManipulatorSubsystem->GetSD()->UpdateCurrentPosition(sensorSubsystem->GetLowerCarOpenDistance());
}

// Make this return true when this Command no longer needs to run execute()
bool LowerCarManipulatorSupervisorCommand::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void LowerCarManipulatorSupervisorCommand::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LowerCarManipulatorSupervisorCommand::Interrupted()
{

}
