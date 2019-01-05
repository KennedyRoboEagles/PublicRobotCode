/*
 * PlaceCubeOnSideCommandGroup.cpp
 *
 *  Created on: Mar 17, 2018
 *      Author: nowir
 */

#include <Commands/Auto/PlaceCubeOnSideCommandGroup.h>
#include <Commands/Motion/DriveLinearForwardCommand.h>
#include <Commands/WaitCommand.h>

#include "Commands/Motion/RotateToAngle.h"
#include "Commands/Elevator/ElevatorMoveToPositionCommand.h"

PlaceCubeOnSideCommandGroup::PlaceCubeOnSideCommandGroup(double firstDistance,
		double secondHeading, double thridDistance, double elevatorHeight) {
	// Drive Forward and raise elevator
	AddSequential(new DriveLinearForwardCommand(firstDistance, 0));
	AddParallel(new ElevatorMoveToPositionCommand(elevatorHeight));

	// Rotate to face switch/scale
	AddSequential(new RotateToAngle(secondHeading));

	// Drive up to switch/scale
	AddSequential(new DriveLinearForwardCommand(thridDistance, secondHeading));

	// Wait for a "second" for things to settle
	AddSequential(new WaitCommand(0.5));

	// Release Cube into switch or scale
//	AddSequential(new IntakePrepareForCubeCommand());
}

PlaceCubeOnSideCommandGroup::~PlaceCubeOnSideCommandGroup() {}

