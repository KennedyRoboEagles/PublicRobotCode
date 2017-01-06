package com.kennedyrobotics.commands.auto;

import com.kennedyrobotics.commands.DriveTillLineCommand;
import com.kennedyrobotics.commands.ShootLowGoalCommandGroup;
import com.kennedyrobotics.commands.drive.DriveDistanceCommand;
import com.kennedyrobotics.commands.drive.TurnSpecifiedDegreesCommand;
import com.kennedyrobotics.commands.shooter.AimShooterDownCommand;

import edu.wpi.first.wpilibj.command.CommandGroup;
import edu.wpi.first.wpilibj.command.PrintCommand;
import edu.wpi.first.wpilibj.command.WaitCommand;

/**
 *
 */
public class LowGoalBreachMoatCommandGroup extends CommandGroup {
    
	public enum Position {
		kLowBar(15*12, 45,18*12);
		public final double postB;
		public final double turn;
		public final double postT;
		private Position(double postBreach, double turnAngle, double postTurnDistnace) {
			this.postB = postBreach;
			this.turn = turnAngle;
			this.postT = postTurnDistnace;
		}
	}
	
	public LowGoalBreachMoatCommandGroup(Position p) {
		this(p.postB, p.turn, p.postT);
	}
	
    public  LowGoalBreachMoatCommandGroup(
    		double postBreachDistance, 
    		double turnangle, 
    		double postTurnDistance) {
    	addSequential(new PrintCommand("!Aim Shooter Down"));
    	addSequential(new AimShooterDownCommand());

//    	addSequential(new PrintCommand("!Breaching Moat"));
//    	addSequential(new DriveDistanceCommand(10*12, 0.95));
    	
//    	addSequential(new PrintCommand("!Drive back to line"));
//      addSequential(new DriveTillLineCommand(0.7));

        addSequential(new PrintCommand("!Drive Forward"));
        addSequential(new DriveDistanceCommand(postBreachDistance));
        
        addSequential(new PrintCommand("!Turn"));
    	addSequential(new TurnSpecifiedDegreesCommand(turnangle));
    	
    	addSequential(new PrintCommand("!Drive Forward To low goal"));
    	addSequential(new DriveDistanceCommand(postTurnDistance));
    	
    	addSequential(new PrintCommand("!Shoot Low goal command group"));
    	addSequential(new ShootLowGoalCommandGroup(), 1.5);
    	
    	addSequential(new PrintCommand("!Shoot again"));
    	addSequential(new ShootLowGoalCommandGroup(), 5);
    }
}
