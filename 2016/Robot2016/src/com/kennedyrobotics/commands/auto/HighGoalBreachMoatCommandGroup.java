package com.kennedyrobotics.commands.auto;

import com.kennedyrobotics.commands.DriveTillLineCommand;
import com.kennedyrobotics.commands.drive.DriveDistanceCommand;
import com.kennedyrobotics.commands.drive.TurnSpecifiedDegreesCommand;
import com.kennedyrobotics.commands.vision.VisionDriveToPosition;

import edu.wpi.first.wpilibj.command.CommandGroup;

/**
 *
 */
public class HighGoalBreachMoatCommandGroup extends CommandGroup {
    
    public  HighGoalBreachMoatCommandGroup(
    		double postBreachDistance, 
    		double turnangle, 
    		double goalTargetDistnace) {
        addSequential(new DriveDistanceCommand(10*12, 0.95));
        addSequential(new DriveTillLineCommand(-0.7));
        addSequential(new DriveDistanceCommand(postBreachDistance));
        addSequential(new TurnSpecifiedDegreesCommand(turnangle));
        addSequential(new VisionDriveToPosition(goalTargetDistnace));
        //addSequential(command);//High goal
    }
}
