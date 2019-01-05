package com.kennedyrobotics.motors;

import com.kennedyrobotics.PathfinderUtil;

import jaci.pathfinder.Pathfinder;
import jaci.pathfinder.Trajectory;

/**
 * https://github.com/CurtinFRC/2018-PowerUp/blob/605b409eb3652bfa9403863b5b5bdc118b3b6ce9/common/src/include/curtinfrc/motors/MotionProfiling.h
 * https://github.com/CurtinFRC/2018-PowerUp/blob/605b409eb3652bfa9403863b5b5bdc118b3b6ce9/common/src/cpp/motors/MotionProfiling.cpp
 */
public abstract class MotionProfilingMode {

    protected final MotionProfileConfig cfg_;
    protected final Trajectory tracjectory_;

    public MotionProfilingMode(MotionProfileConfig cfg, String file) {
        cfg_ = cfg;
        tracjectory_ = PathfinderUtil.loadFile(file);
    }

    public abstract void init();

    public double ctrlPeriod() {
        return tracjectory_.get(0).dt;
    }

    public abstract double calculate();

}