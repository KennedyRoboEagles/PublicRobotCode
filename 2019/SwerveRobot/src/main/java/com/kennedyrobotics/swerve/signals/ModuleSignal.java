package com.kennedyrobotics.swerve.signals;

import com.kennedyrobotics.swerve.module.MotorControlMode;
import com.team254.lib.geometry.Rotation2d;

public class ModuleSignal {
    /**
     * Demand of drive wheel from -1.0, 1.0 (in Percent output)
     * Value interpretation changes depending on control mode
     */
    public double demand;

    /**
     * Drive Control Mode
     */
    public MotorControlMode controlMode;

    /**
     * Angle of drive wheel in radians
     */
    public Rotation2d angle = Rotation2d.identity();

    /**
     * Allow reversing of module to achieve goal angle.
     *
     * By default this is allowed
     */
    public boolean allowReverse = true;

    /**
     * Brake Mode
     */
    public boolean brake;

    public ModuleSignal() {}

    public ModuleSignal(ModuleSignal that) {
        this.controlMode = that.controlMode;
        this.demand = that.demand;
        this.angle = that.angle;
        this.allowReverse = that.allowReverse;
        this.brake = that.brake;
    }

    public static ModuleSignal from(MotorControlMode controlMode, double demand, Rotation2d angle) {
        ModuleSignal s = new ModuleSignal();
        s.controlMode = controlMode;
        s.demand = demand;
        s.angle = angle;

        return s;
    }

    public static ModuleSignal from(MotorControlMode controlMode, double demand, Rotation2d angle, boolean allowReverse) {
        ModuleSignal s = new ModuleSignal();
        s.controlMode = controlMode;
        s.demand = demand;
        s.angle = angle;
        s.allowReverse = allowReverse;

        return s;
    }

    public static ModuleSignal from(MotorControlMode controlMode, double demand, Rotation2d angle, boolean allowReverse, boolean brake) {
        ModuleSignal s = new ModuleSignal();
        s.controlMode = controlMode;
        s.demand = demand;
        s.angle = angle;
        s.allowReverse = allowReverse;
        s.brake = brake;

        return s;
    }
}