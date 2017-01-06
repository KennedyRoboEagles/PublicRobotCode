package com.kennedyrobotics.commands.breaching;

import com.kennedyrobotics.commands.drive.DriveDistanceCommand;

import edu.wpi.first.wpilibj.command.CommandGroup;
import edu.wpi.first.wpilibj.command.WaitCommand;

/**
 *
 */
public class BreachMoatCommandGroup extends CommandGroup {
    
    public  BreachMoatCommandGroup() {
    	addSequential(new DriveDistanceCommand(12*13, 0.8));
    	addSequential(new WaitCommand(1.0));
    	addSequential(new DriveDistanceCommand(-12*13, 0.75));
    	
    }
}
