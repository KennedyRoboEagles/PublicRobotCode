#include <Commands/MotionProfiling/ArcTurnCommand.h>
#include <Commands/MotionProfiling/PathFinderCommand.h>
#include <Commands/PrintCommand.h>
#include <Commands/TimedForwardCommand.h>
#include "BoilerCommandGroup.h"

BoilerCommandGroup::BoilerCommandGroup(bool blue) {
	AddSequential(new PrintCommand("Starting Boiler auto"));

	if(blue) {
		AddSequential(new PathFinderCommand(62.126/12.0));
	} else {
		AddSequential(new PathFinderCommand(62.126/12.0));
	}

	AddSequential(new PrintCommand("Turning"));
	if(blue) {
		//Turn 60 about the left wheel, turn the right
		//Turn clockwise
		AddSequential(new ArcTurnCommand(60, false));
	} else {
		//Turn 60 about the right wheel, turn the left
		//Turn counter-clockwise
		AddSequential(new ArcTurnCommand(60, true));
	}

	AddSequential(new PrintCommand("Driving"));
	if(blue) {
		AddSequential(new PathFinderCommand(78.808/12.0));
	} else {
		AddSequential(new PathFinderCommand(78.118/12.0));
	}
//	AddSequential(new TimedForwardCommand());

}
