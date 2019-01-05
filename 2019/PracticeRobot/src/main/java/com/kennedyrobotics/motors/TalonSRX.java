package com.kennedyrobotics.motors;

import com.ctre.phoenix.ErrorCode;
import com.ctre.phoenix.motion.MotionProfileStatus;
import com.ctre.phoenix.motion.SetValueMotionProfile;
import com.ctre.phoenix.motion.TrajectoryPoint;
import com.ctre.phoenix.motion.TrajectoryPoint.TrajectoryDuration;
import com.ctre.phoenix.motorcontrol.ControlMode;
import com.kennedyrobotics.PIDF;

import jaci.pathfinder.Trajectory;
import jaci.pathfinder.Trajectory.Segment;

/**
 * CTRE Talon SRX Motor Controller when used on CAN Bus, with PathFinder integration.
 * 
 * Based off of: https://github.com/CurtinFRC/2018-PowerUp/blob/605b409eb3652bfa9403863b5b5bdc118b3b6ce9/common/src/cpp/motors/CurtinTalonSRX.cpp
 */
public class TalonSRX extends com.ctre.phoenix.motorcontrol.can.TalonSRX {

    private int codesPerRev_;
    private int mpLoadOffset_ = 0;
    private double wheelDiameter_;

    public TalonSRX(int deviceID) {
        super(deviceID);
    }


    public void configurePIDF(int slot, int pidId, double p, double i, double d, double f, int timeoutMS) {
        this.selectProfileSlot(0, pidId);
        this.config_kP(slot, p, timeoutMS);
        this.config_kI(slot, i, timeoutMS);
        this.config_kD(slot, d, timeoutMS);
        this.config_kF(slot, f, timeoutMS);    
    }

    public void configurePIDF(int slot, int pidId, PIDF s, int timeoutMS) {
        this.configurePIDF(slot, pidId, s.p, s.i, s.d, s.f, timeoutMS);
    }

    public void configureMPUpdateRate(int milliseconds, int timeoutMS) {
        this.configMotionProfileTrajectoryPeriod(milliseconds, timeoutMS);
        this.changeMotionControlFramePeriod(milliseconds / 2);
    }

    public void configureMPEncoderCodesPerRev(int codesPerRev) {
        codesPerRev_ = codesPerRev;
    } 

    public void configureMPWheelDiameter(double wheelDiameter) {
        wheelDiameter_ = wheelDiameter;
    }

    public boolean loadPathFinder(Trajectory trajectory) {
        if(mpLoadOffset_ == 0) {
            this.clearMotionProfileTrajectories();
            // Set control mode
        }

        double revPerM = 1 / (Math.PI * wheelDiameter_);
        for (int i = mpLoadOffset_; i < trajectory.length(); i++) {
            if (this.isMotionProfileTopLevelBufferFull()) {
            mpLoadOffset_ = i;
            return false;
            }
        
            Segment s = trajectory.segments[i];
            double rpm = (s.velocity / (wheelDiameter_ / 2 * 0.10472)); // TODO what is 0.10472?
            double pos = s.position * revPerM * codesPerRev_;
            double vel = (rpm / 60.0) * codesPerRev_ * 10;

            TrajectoryPoint tp = new TrajectoryPoint();
            tp.position = pos;
            tp.velocity = vel;
            tp.headingDeg = 0;  // heading (degrees). Only needed if using Pidgeon IMU
            tp.profileSlotSelect0 = 0;  // slot select
            tp.profileSlotSelect1 = 0;  // slot select
            tp.isLastPoint = i == (trajectory.segments.length -1); // last point?
            tp.zeroPos = i == 0;  // zero sensor?
            tp.timeDur = TrajectoryDuration.Trajectory_Duration_0ms;
      
            // Fails if the buffer becomes full
            if (this.pushMotionProfileTrajectory(tp) != ErrorCode.OK) {
            mpLoadOffset_ = i + 1;
            return false;
            }
        }
        mpLoadOffset_ = trajectory.segments.length - 1;
        return true;
    }

    public void resetMP() {
        mpLoadOffset_ = 0;
        this.clearMotionProfileTrajectories();
    }

    public void enableMP() {
        this.set(ControlMode.MotionProfile, SetValueMotionProfile.Enable.value);
    }

    public void holdMP() {
        this.set(ControlMode.MotionProfile, SetValueMotionProfile.Hold.value);
    }

    public void disableMP() {
        this.set(ControlMode.MotionProfile, SetValueMotionProfile.Disable.value);
    }

    public MotionProfileStatus processMP() {
        this.processMotionProfileBuffer();
        MotionProfileStatus status = new MotionProfileStatus();;
        this.getMotionProfileStatus(status);
        return status;
    }
}