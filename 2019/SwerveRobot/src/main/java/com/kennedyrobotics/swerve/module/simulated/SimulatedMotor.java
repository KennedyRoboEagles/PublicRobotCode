package com.kennedyrobotics.swerve.module.simulated;

import com.kennedyrobotics.sim.SimulatedActuator;
import com.kennedyrobotics.swerve.module.MotorControlMode;
import edu.wpi.first.wpilibj.Timer;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;
import frc.robot.Constants;

public class SimulatedMotor {

    private final SimulatedActuator sim_;
    private MotorControlMode controlType_ = MotorControlMode.kNeutralOutput;
    private double lastTimeStamp_ = 0.0;

    private final String name_;

    public SimulatedMotor(double velocity) {
        this(null, velocity);
    }


    public SimulatedMotor(String name, double velocity) {
        sim_ = new SimulatedActuator(0, velocity);
        name_ = name;
    }


    public double encoderPosition() {
        return sim_.getPosition();
    }

    public double encoderVelocity() {
        return sim_.getVelocity();
    }

    public void encoderReset() {
        sim_.reset(0);
    }

    public void setBrake(boolean enabled) {}

    public void neutralOutput() {
        this.setDrive(MotorControlMode.kNeutralOutput, 0);
    }

    public void setDrive(MotorControlMode controlType, double demand) {
        this.controlType_ = controlType; // Update controlMode

        double timestamp = Timer.getFPGATimestamp();
        double dt = timestamp - lastTimeStamp_;
        lastTimeStamp_ = timestamp;

        switch (controlType) {
            case kNeutralOutput:
                sim_.setCommandedVelocity(0);
                break;
            case kPercentOutput:
                // This is the cursive velocity
                sim_.setCommandedVelocity(demand * Constants.kSwerveMaxSpeedInchesPerSecond * 0.5);
                break;
            case kPosition:
                sim_.setCommandedPosition(demand);
                break;
            case kVelocity:
                sim_.setCommandedVelocity(demand);
                break;
            default:
                throw new IllegalStateException("Invalid control mode: " + controlType);
        }

        if (name_ != null) {
            SmartDashboard.putString(name_ + " Control Mode", controlType.name());
            SmartDashboard.putNumber(name_ + " Demand", demand);
            SmartDashboard.putNumber(name_ + " Position", sim_.getPosition());
        }


        // dt = (20.0 / 1000.0);
        sim_.update(dt);
    }

    public MotorControlMode controlMode() {
        return controlType_;
    }
}
