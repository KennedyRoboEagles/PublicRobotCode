package com.kennedyrobotics.sim;

import com.team254.lib.util.Util;

public class SimulatedActuator {
    double mVelocity;
    double mCommand = 0;
    ControlType mCommandType;

    double mCurrentPosition = 0;
    double mCurrentVelocity = 0;

    private enum ControlType {
        POSITION, VELOCITY
    }

    public SimulatedActuator(double startPos, double velocity) {
        this.mVelocity = velocity;
        mCommand = startPos;
        mCurrentPosition = startPos;
        setCommandedPosition(mCurrentPosition);
    }

    public SimulatedActuator(double velocity) {
        mCurrentPosition = 0;
        mVelocity = velocity;
        mCurrentPosition = mCommand;
        setCommandedPosition(mCurrentPosition);
    }

    public void setCommandedPosition(double commandedPosition) {
        mCommand = commandedPosition;
        mCommandType = ControlType.POSITION;
    }

    public void setCommandedVelocity(double commandedVelocity) {
        mCommand = commandedVelocity;
        mCommandType = ControlType.VELOCITY;
    }

    public double update(double timeStep) {
        double prevPosition = mCurrentPosition;

        double amountToMove = 0.0;

        boolean positiveError = (mCommand - mCurrentPosition) > 0;
        if (mCommandType == ControlType.POSITION) {
            amountToMove = (mVelocity * timeStep) * (positiveError ? 1 : -1);
        } else if (mCommandType == ControlType.VELOCITY) {
            amountToMove = (mCommand * timeStep);
        } else {
            System.out.println("Command type invalid: " + mCommandType);
        }

        mCurrentPosition += amountToMove;

        if (mCommandType == ControlType.POSITION) {
            boolean newPositiveError = (mCommand - mCurrentPosition) > 0;
            System.out.println("newPositiveError: " + newPositiveError);
            if (newPositiveError != positiveError) {
                mCurrentPosition = mCommand;
            }
        }



        mCurrentVelocity = (mCurrentPosition - prevPosition) / timeStep;

        return mCurrentPosition;
    }

    public boolean positionNear(double position, double epsilon) {
        return Util.epsilonEquals(getPosition(), position, epsilon);
    }

    public boolean positionNear(double epsilon) {
        if (mCommandType == ControlType.POSITION) {
            return positionNear(mCommand, epsilon);
        }
        return false;
    }

    public double getVelocity() {
        return mCurrentVelocity;
    }

    public double getPosition() {
        return mCurrentPosition;
    }

    public double getTarget() {
        return mCommand;
    }

    public void reset(double position) {
        mCurrentPosition = mCommand = position;
    }

}