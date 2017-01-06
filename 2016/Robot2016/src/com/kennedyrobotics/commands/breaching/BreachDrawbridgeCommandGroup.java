package com.kennedyrobotics.commands.breaching;

import com.kennedyrobotics.Movement;
import com.kennedyrobotics.commands.drive.DriveDistanceCommand;
import com.kennedyrobotics.commands.drive.DriveUntilCollisionCommand;
import com.kennedyrobotics.commands.drive.DriveUntilLevelCommand;

import edu.wpi.first.wpilibj.command.CommandGroup;

/**
 *
 */
public class BreachDrawbridgeCommandGroup extends CommandGroup {
	
	private double distance1sttime = -0.5;
	private double distance2ndtime = -0.5;
	private double armTiltDegrees1stTime = 25.0;
	private double armTiltDegrees2ndTime = -3.0;
	private double armExtendPosition1stTime = 4.0;
	private double armExtendPosition2ndTime = 2.0;
	private double driveSpeed = 0.5;
	private double timeOut = 7;
	
	//This distacne can be tweaked later to fit the specific
	//drawbridge requirements.
    
    public  BreachDrawbridgeCommandGroup() {
    	
//    	addSequential(new DriveUntilCollisionCommand());
//    	addSequential(new DriveDistanceCommand(distance1sttime));
//    	addSequential(new TiltArmToPositionCommand(Movement.kSetpoint, armTiltDegrees1stTime));
//    	addSequential(new MoveArmToPositionCommand(Movement.kSetpoint, armExtendPosition1stTime));
//    	addSequential(new DriveDistanceCommand(distance2ndtime));
//    	addSequential(new MoveArmToPositionCommand(Movement.kSetpoint, armExtendPosition2ndTime));
//    	addSequential(new TiltArmToPositionCommand(Movement.kSetpoint, armTiltDegrees2ndTime));
//    	addSequential(new DriveUntilLevelCommand(driveSpeed, timeOut));
    	
    	/*
    	 * We're actually going to need a raise arm specified
    	 * degrees command, and specified degrees command for lower arm,
    	 * specified distace for extend/retract arm, too.
    	 */
    	
    	
        // Add Commands here:
        // e.g. addSequential(new Command1());
        //      addSequential(new Command2());
        // these will run in order.

        // To run multiple commands at the same time,
        // use addParallel()
        // e.g. addParallel(new Command1());
        //      addSequential(new Command2());
        // Command1 and Command2 will run in parallel.

        // A command group will require all of the subsystems that each member
        // would require.
        // e.g. if Command1 requires chassis, and Command2 requires arm,
        // a CommandGroup containing them would require both the chassis and the
        // arm.
    }
}
