package com.kennedyrobotics.motors;

import com.ctre.phoenix.motion.MotionProfileStatus;
import com.ctre.phoenix.motion.SetValueMotionProfile;

/**
 * https://github.com/CurtinFRC/2018-PowerUp/blob/605b409eb3652bfa9403863b5b5bdc118b3b6ce9/common/src/cpp/motors/MotionProfiling.cpps
 */
public class TalonMPMode extends MotionProfilingMode {

    private TalonSRX talon_;

    public TalonMPMode(TalonSRX talon, MotionProfileConfig cfg, String fileName) {
        super(cfg, fileName);
        talon_ = talon;
    }

    @Override
    public void init() {
        talon_.resetMP();
        talon_.setSelectedSensorPosition(0, 0, 0);
        talon_.configureMPUpdateRate((int)tracjectory_.get(0).dt * 1000, 0);
        talon_.configureMPEncoderCodesPerRev(cfg_.encTicksPerRev);
        talon_.configureMPWheelDiameter(cfg_.wheelDiameter);
        talon_.configurePIDF(0, 0, cfg_.kP, cfg_.kI, cfg_.kD, 1023/cfg_.kV, 0);
        talon_.loadPathFinder(tracjectory_);
        talon_.disableMP();
    }

    @Override
    public double calculate() {
        // If the motion profile buffer is not full, try to load more points
        talon_.loadPathFinder(tracjectory_);

        MotionProfileStatus status =  talon_.processMP();
        return status.isLast ? SetValueMotionProfile.Hold.value ? SetValueMotionProfile.Enable.value;
    }



}