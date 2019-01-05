package com.kennedyrobotics.motors;

public class MotionProfileConfig {
    public final int encTicksPerRev; 
    public final double wheelDiameter;
    public final double kP;
    public final double kI; 
    public final double kD; 
    public final double kV;
    public final double kA;  // note: ki unused in pathfinder, ka unused on Talon internal profile

    public MotionProfileConfig(int encTicksPerRev,  double wheelDiameter, double kP, double kI, double kD, double kV, double kA) {
        this.encTicksPerRev = encTicksPerRev;
        this.wheelDiameter = wheelDiameter;
        this.kP = kP;
        this.kI = kI;
        this.kD = kD;
        this.kV = kV;
        this.kA = kA;
    }
}