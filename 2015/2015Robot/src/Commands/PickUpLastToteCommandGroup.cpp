#include "PickUpLastToteCommandGroup.h"

#include "LowerCar/LowerCarManipulatorAcquireToteCommand.h"
#include "LowerCar/LowerCarManipulatorOpenForNarrowToteCommand.h"
#include "LowerTower/LowerTowerLowerToteCommand.h"
#include "LowerTower/LowerTowerMoveToBottomCommand.h"
#include "DriveForwardTimeCommand.h"
#include "TurnSpecifiedDegreesCommand.h"

PickUpLastToteCommandGroup::PickUpLastToteCommandGroup(float timeBackward, float turnAngle)
{
	AddSequential(new LowerTowerLowerToteCommand());

	AddSequential(new LowerCarManipulatorOpenForNarrowToteCommand());

	AddSequential(new LowerTowerMoveToBottomCommand());

	AddSequential(new LowerCarManipulatorAcquireToteCommand());

	//AddSequential(new DriveForwardTimeCommand(timeBackward, -0.75));

	//AddSequential(new TurnSpecifiedDegreesCommand(turnAngle));
}
