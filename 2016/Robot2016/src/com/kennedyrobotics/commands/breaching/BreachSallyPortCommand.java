package com.kennedyrobotics.commands.breaching;

import com.kennedyrobotics.Movement;
import com.kennedyrobotics.commands.drive.DriveDistanceCommand;
import com.kennedyrobotics.commands.drive.DriveUntilCollisionCommand;
import com.kennedyrobotics.commands.drive.DriveUntilLevelCommand;
import com.kennedyrobotics.commands.drive.TurnSpecifiedDegreesCommand;

import edu.wpi.first.wpilibj.command.CommandGroup;

/**
 *
 */
public class BreachSallyPortCommand extends CommandGroup {
	
	private final double distance1stTime = 0.0;
	private final double tiltArm1stTime = 0.0;
	private final double moveArm1stTime = 0.0;
	private final double distance2ndTime = 0.0;
	private final double degrees = 0.0;
	private final double speed = 0.5;
	private final double timeOut = 7;
    
    public  BreachSallyPortCommand() {
    	
//    	addSequential(new DriveUntilCollisionCommand());
//    	addSequential(new DriveDistanceCommand(distance1stTime));
//    	addSequential(new TiltArmToPositionCommand(Movement.kSetpoint, tiltArm1stTime));
//    	addSequential(new MoveArmToPositionCommand(Movement.kSetpoint, moveArm1stTime));
//    	addSequential(new DriveDistanceCommand(distance2ndTime));
//    	addSequential(new TurnSpecifiedDegreesCommand(degrees));
//    	addSequential(new DriveUntilLevelCommand(speed, timeOut));
    	
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
