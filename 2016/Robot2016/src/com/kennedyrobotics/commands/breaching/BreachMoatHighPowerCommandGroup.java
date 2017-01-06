package com.kennedyrobotics.commands.breaching;

import com.kennedyrobotics.commands.drive.DriveDistanceCommand;

import edu.wpi.first.wpilibj.command.CommandGroup;
import edu.wpi.first.wpilibj.command.WaitCommand;

/**
 *
 */
public class BreachMoatHighPowerCommandGroup extends CommandGroup {
    
    public  BreachMoatHighPowerCommandGroup() {
    	
    	addSequential(new DriveDistanceCommand(12*15, 1.0));
    	addSequential(new WaitCommand(1.0));
    	addSequential(new DriveDistanceCommand(-12*15, 1.0));
       
    }
}
