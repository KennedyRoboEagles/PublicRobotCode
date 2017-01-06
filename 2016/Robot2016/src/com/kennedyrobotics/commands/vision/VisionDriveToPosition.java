package com.kennedyrobotics.commands.vision;

import com.kennedyrobotics.Robot;
import com.kennedyrobotics.commands.drive.DriveDistanceCommand;

/**
 *
 */
public class VisionDriveToPosition extends DriveDistanceCommand {

	private final double goalDistnace;
	
    public VisionDriveToPosition(double goalDistnace) {
    	super(0, 0.65);
        this.goalDistnace = goalDistnace;
    }
    
    @Override
    protected void initialize() {
    	double targetDistnace = Robot.visionSubsystem.getTask().getTargetDistance();
    	this.distance = -(targetDistnace - goalDistnace) * 12;
    	super.initialize();
    }

}
