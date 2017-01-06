package com.kennedyrobotics.commands;

import com.kennedyrobotics.commands.shooter.AimShooterDownCommand;
import com.kennedyrobotics.commands.shooter.InjestBallCommand;
import com.kennedyrobotics.commands.shooter.ShootLowCommand;

import edu.wpi.first.wpilibj.command.CommandGroup;
import edu.wpi.first.wpilibj.command.PrintCommand;
import edu.wpi.first.wpilibj.command.WaitCommand;

/**
 *
 */
public class ShootLowGoalCommandGroup extends CommandGroup {
    
    public  ShootLowGoalCommandGroup() {
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
    	addSequential(new PrintCommand("!!Shooter down"));
    	addSequential(new AimShooterDownCommand());
    	
    	addSequential(new PrintCommand("!!Shoot low"));
    	addSequential(new ShootLowCommand());
    	
    	addSequential(new PrintCommand("!!Wait for shooter"));
    	addSequential(new WaitCommand(0.2));
    	
    	addSequential(new PrintCommand("!!Wait for InjestBall"));
    	addSequential(new InjestBallCommand());
    	
    }
}
