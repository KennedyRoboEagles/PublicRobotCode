/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <Commands/Auto/PlaceCubeOnSwitchCenterCommandGroup.h>
#include "Commands/Motion/RotateToAngle.h"
#include "Commands/Motion/DriveLinearStrafeCommandV2.h"
#include "Commands/Elevator/ElevatorMoveToPositionCommand.h"
#include <Commands/Motion/DriveLinearForwardCommand.h>


PlaceCubeOnSwitchCenterCommandGroup::PlaceCubeOnSwitchCenterCommandGroup(
		double firstDistance, double secondStrafe, double thirdDistance, double elevatorHeight) {
	// Add Commands here:
	// e.g. AddSequential(new Command1());
	//      AddSequential(new Command2());
	// these will run in order.

	// To run multiple commands at the same time,
	// use AddParallel()
	// e.g. AddParallel(new Command1());
	//      AddSequential(new Command2());
	// Command1 and Command2 will run in parallel.

	// A command group will require all of the subsystems that each member
	// would require.
	// e.g. if Command1 requires chassis, and Command2 requires arm,
	// a CommandGroup containing them would require both the chassis and the
	// arm.

	// Drive Forward and raise elevator
	AddSequential(new DriveLinearForwardCommand(firstDistance, 0));
	AddParallel(new ElevatorMoveToPositionCommand(elevatorHeight));

	// Stafe to line up with switch
	AddSequential(new DriveLinearStrafeCommandV2(0, secondStrafe, 0));

	// Drive up to switch/scale
	AddSequential(new DriveLinearForwardCommand(thirdDistance, 0));

	// Wait for a "second" for things to settle
	AddSequential(new WaitCommand(0.5));


	// Release Cube into switch or scale
//	AddSequential(new IntakePrepareForCubeCommand());


}
