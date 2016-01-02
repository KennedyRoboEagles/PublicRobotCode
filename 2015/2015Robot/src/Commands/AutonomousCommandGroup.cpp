#include "AutonomousCommandGroup.h"
#include "TurnSpecifiedDegreesCommand.h"
#include "DriveLaterallyDistanceCommand.h"
#include "DriveLaterallyTimeCommand.h"
#include "DriveForwardTimeCommand.h"

AutonomousCommandGroup::AutonomousCommandGroup()
{

	AddSequential(new DriveForwardTimeCommand(6, 0.35)); //TODO Find the right distance
	//AddSequential(new TurnSpecifiedDegreesCommand(-75.0));
}
