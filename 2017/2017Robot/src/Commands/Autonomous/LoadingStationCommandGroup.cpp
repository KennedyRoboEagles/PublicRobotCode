#include "LoadingStationCommandGroup.h"
#include <Commands/MotionProfiling/TurnSpecifiedDegrees2Command.h>
#include <Commands/MotionProfiling/TurnSpecifiedDegrees2Command.h>
#include <Commands/MotionProfiling/PathFinderCommand.h>
#include <Commands/MotionProfiling/ArcTurnCommand.h>
#include <Commands/MotionProfiling/TurnSpecifiedDegreesCommand.h>
#include <Commands/PrintCommand.h>
#include <Commands/TimedForwardCommand.h>
#include <RobotConstants.h>

/*
//constexpr double L1 = 92.605/12;
constexpr double L1 = 89.0/12;
constexpr double L2 = 80.4/12.0;
*/

LoadingStationCommandGroup::LoadingStationCommandGroup(bool blue) {
	AddSequential(new PrintCommand("Starting Loading station auto"));
//	AddSequential(new PathFinderCommand(88.5/12 - 8.08/12.0 - (kCHASSIS_LENGTH/2.0 + kCHASSIS_BUMBER)));
	AddSequential(new PathFinderCommand(61.838/12.0));



	AddSequential(new PrintCommand("Turning"));
	if(blue) {
		//Turn 60 about the right wheel, turn the left
		//Turn counter-clockwise
		AddSequential(new ArcTurnCommand(60, true));
	} else {
		//Turn 60 about the left wheel, turn the right
		//Turn clockwise
		AddSequential(new ArcTurnCommand(60, false));
	}

	AddSequential(new PrintCommand("Driving"));
	AddSequential(new PathFinderCommand(77.0/12.0));
//	AddSequential(new TimedForwardCommand());
}
