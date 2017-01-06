package com.kennedyrobotics.robot2016.subsystems;

import com.kennedyrobotics.robot2016.commands.ComrpressorSupervisorCommand;

import edu.wpi.first.wpilibj.Compressor;
import edu.wpi.first.wpilibj.command.Subsystem;

/**
 *
 */
public class CompressorSubsystem extends Subsystem {
    
	private Compressor compressor = new Compressor();
	
    // Put methods for controlling this subsystem
    // here. Call these from Commands.

    public void initDefaultCommand() {
        // Set the default command for a subsystem here.
        //setDefaultCommand(new MySpecialCommand());
    	setDefaultCommand(new ComrpressorSupervisorCommand());
    }
    
    public void start() {
    	compressor.start();    	
    }
    
    public void stop() {
    	compressor.stop();
    }
       
}

