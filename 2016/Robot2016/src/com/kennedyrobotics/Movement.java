package com.kennedyrobotics;

import com.kennedyrobotics.commands.shooter.AimShooterToPositionCommand;

/**
 * Used for the {@link MoveArmToPositionCommand}, {@link AimShooterToPositionCommand}, 
 * and {@link TiltArmToPositionCommand} to choose what kind of movement to perform. 
 * Either go directly move to a setpoint, or make adjustment to the setpoint.
 * @author Ryan
 *
 */
public enum Movement {
	kSetpoint,
	kAdjustment
}
