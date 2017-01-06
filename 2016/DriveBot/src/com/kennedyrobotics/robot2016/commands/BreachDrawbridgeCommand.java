package com.kennedyrobotics.robot2016.commands;

import edu.wpi.first.wpilibj.command.CommandGroup;

/**
 *
 */
public class BreachDrawbridgeCommand extends CommandGroup {
	
	private double distance1sttime = -0.5;
	private double distance2ndtime = -0.5;
	private double distance3rdtime = -0.5;
	//This distacne can be tweaked later to fit the specific
	//drawbridge requirements.
    
    public  BreachDrawbridgeCommand() {
    	
    	addSequential(new DriveUntilCollisionCommand());
    	addSequential(new DriveDistanceCommand(distance1sttime));
    	addSequential(new RaiseArmCommand());
    	//Will need specified degrees here
    	//Probably new raise arm specified degrees command
    	addSequential(new ExtendArmCommand());
    	addSequential(new DriveDistanceCommand(distance2ndtime));
    	addSequential(new RetractArmCommand());
    	addSequential(new LowerArmCommand());
    	addSequential(new DriveDistanceCommand(distance3rdtime));
    	
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
