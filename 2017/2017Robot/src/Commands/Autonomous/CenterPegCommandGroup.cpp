#include "CenterPegCommandGroup.h"
#include <Commands/MotionProfiling/PathFinderCommand.h>
#include <Commands/PrintCommand.h>
#include <RobotConstants.h>
#include <Commands/TimedForwardCommand.h>
CenterPegCommandGroup::CenterPegCommandGroup() {
	AddSequential(new PrintCommand("Starting Center Peg Auto"));
	AddSequential(new PathFinderCommand(110.0/12.0));
	AddSequential(new TimedForwardCommand());

}
