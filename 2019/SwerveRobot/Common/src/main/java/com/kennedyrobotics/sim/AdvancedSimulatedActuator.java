package com.kennedyrobotics.sim;

import com.team254.lib.util.Util;
import com.team3452.trajectory.BasicTrajectory;
import com.team3452.trajectory.BasicTrajectoryGenerator;

import java.text.DecimalFormat;

public class AdvancedSimulatedActuator {

    private final double DefaultVelocity;
    private final double DefaultAcceleration;
    private final double DefaultJerk;

    private double positionVelocity = 0.0;
    private double positionAcceleration = 0.0;
    private double positionJerk = 0.0;

    // Tracking
    private double mCurrentPosition = 0;
    private double mCurrentVelocity = 0.0;
    private double positionOffset = 0.0;
    private double trajectoryStartTime = 0.0;
    private BasicTrajectory trajectory = new BasicTrajectory(1);

    // Input
    private boolean needsUpdate;
    private double targetPosition = 0.0;

    // Time
    private double dt = 0.0;
    private double prevTime = 0.0;
    private Double forcedDT = Double.NaN;

    int id;

    public AdvancedSimulatedActuator(double velocity, double acceleration, int id) {
        this(velocity, acceleration, acceleration * 10);
        this.id = id;
    }

    public AdvancedSimulatedActuator(double velocity, double acceleration) {
        this(velocity, acceleration, acceleration * 10);
    }

    public AdvancedSimulatedActuator(double velocity, double acceleration, double jerk) {
        DefaultVelocity = velocity;
        DefaultAcceleration = acceleration;
        DefaultJerk = jerk;

        setGainsToDefault();

        id = -1;
    }

    final DecimalFormat df = new DecimalFormat("#0.00");

    public void configureGainsForMove(final double position, final double desired) {

        final double potential = predictTimeToMoveTo(position);
        final double scalar = potential / desired;

        setVelocity(DefaultVelocity * scalar);

        final double vToA = DefaultVelocity / DefaultAcceleration;
        final double vToJ = DefaultVelocity / DefaultJerk;

        setAcceleration(positionVelocity * vToA);
        setJerk(positionVelocity * vToJ);

        // V4 PID

        // double predictedTime = predictTimeToMoveTo(position);

        // final double vToA = DefaultVelocity / DefaultAcceleration;

        // final double kP = 0.1;

        // int loops = 0;
        // double velocity = DefaultVelocity;
        // while (loops < 7500) {

        // double delta = (predictedTime - time);
        // velocity += delta * kP;

        // predictedTime = predictTimeToMoveTo(position, velocity, velocity * vToA,
        // DefaultJerk);

        // System.out.println("Delta:" + df.format(delta) + "\tTarget: " +
        // df.format(time) + "\tCurrent guess: "
        // + df.format(predictedTime) + "\tVelocity: " + df.format(velocity));

        // if (velocity < 0) {
        // System.out.println("Could not home in on gains");
        // setGainsToDefault();
        // return;
        // }
        // loops++;
        // boolean complete = GZUtil.epsilonEquals(predictedTime, time, 0.0125);
        // if (complete) {
        // System.out
        // .println("Ideal velocity calculated in " + loops + ", will take " +
        // predictedTime + " seconds");
        // setVelocity(velocity);
        // return;
        // }
        // }

        // V3 PID 2
        // double predictedTime = predictTimeToMoveTo(position);
        // final double kP = 0.0125;

        // int loops = 0;
        // double velocity = DefaultVelocity;
        // while (!GZUtil.epsilonEquals(predictedTime, time, 0.0125)) {
        // double delta = predictedTime - time;
        // velocity += delta * kP;
        // predictedTime = predictTimeToMoveTo(position, velocity, DefaultAcceleration,
        // DefaultJerk);
        // System.out.println("Delta:" + delta + "Target: " + time + " current guess: "
        // + predictedTime
        // + "\tVelocity: " + velocity);

        // if (velocity < 0) {
        // System.out.println("Could not home in on gains");
        // setGainsToDefault();
        // return;
        // }
        // loops++;
        // }

        // System.out.println("Ideal velocity calculated in " + loops + ", will take " +
        // predictedTime + " seconds");
        // setVelocity(velocity);

        // V2 PID 1

        // SynchronousPIDF pid = new SynchronousPIDF(0.0125, 0, 0);
        // pid.setSetpoint(time);
        // double velocity = DefaultVelocity;

        // double predictedTime = predictTimeToMoveTo(position);
        // while (!GZUtil.epsilonEquals(predictedTime, time, .125)) {
        // predictedTime = predictTimeToMoveTo(position, velocity, DefaultAcceleration,
        // DefaultJerk);
        // velocity -= pid.calculate(predictedTime, .1);
        // System.out.println(predictedTime + "\t" + time + "\t" + velocity);
        // }

        // setVelocity(velocity);

        // V1
        // final double predictedTime = predictTimeToMoveTo(position);
        // System.out.println("\n\nNew move!");
        // System.out.println("Predicted time: " + predictedTime);

        // final double vToA = DefaultVelocity / DefaultAcceleration;
        // final double vToJ = DefaultVelocity / DefaultJerk;

        // if (predictedTime == 0)
        // return;

        // final double scalar = predictedTime / time;

        // System.out.println("Scalar: " + scalar);

        // positionVelocity = DefaultVelocity * scalar;
        // positionAcceleration = positionVelocity * vToA;
        // positionJerk = positionVelocity * vToJ;
    }

    public void setGainsToDefault() {
        setVelocity(DefaultVelocity);
        setAcceleration(DefaultAcceleration);
        setJerk(DefaultJerk);
    }

    private void setVelocity(double velocity) {
        this.positionVelocity = velocity;
    }

    private void setAcceleration(double acceleration) {
        this.positionAcceleration = acceleration;
    }

    private void setJerk(double jerk) {
        this.positionJerk = jerk;
    }

    public void setTargetPosition(double targetPosition) {
        if (this.targetPosition != targetPosition) {
            this.targetPosition = targetPosition;
            needsUpdate = true;
        }
    }

    public boolean nearTarget(double epsilon) {
        boolean near = Util.epsilonEquals(getCurrentPosition(), targetPosition, epsilon);
        return near;
    }

    public double getCurrentPosition() {
        return mCurrentPosition;
    }

    public double getCurrentVelocity() {
        return mCurrentVelocity;
    }

    public void forceDT(double dt) {
        forcedDT = dt;
    }

    public double predictTimeToMoveTo(double position) {
        return predictTimeToMoveTo(position, DefaultVelocity, DefaultAcceleration, DefaultJerk);
    }

    public double predictTimeToMoveTo(double position, double velocity, double acceleration, double jerk) {
        var t = getTrajectory(position, velocity, acceleration, jerk);
        if (t == null)
            return 0.0;
        return t.perdictedTime();
    }

    public double update(double time) {
        dt = time - prevTime;
        double prevPosition = getCurrentPosition();

        if (needsUpdate) {

            trajectory = getTrajectory(targetPosition, positionVelocity, positionAcceleration, positionJerk);
            positionOffset = getCurrentPosition();

            trajectoryStartTime = time;

            needsUpdate = false;

            if (id == 1 && trajectory != null) {
                // System.out.println("Predicted time: " + trajectory.perdictedTime());
            }

        }

        if (trajectory != null) {
            mCurrentPosition = positionOffset + trajectory.interpolate(time - trajectoryStartTime).pos;
        }

        mCurrentVelocity = (getCurrentPosition() - prevPosition) / dt;

        prevTime = time;
        return getCurrentPosition();
    }

    private BasicTrajectory getTrajectory(double a_targetPosition, double velocity, double acceleration, double jerk) {
        boolean flipTrajectory = false;
        if (a_targetPosition < mCurrentPosition) {
            flipTrajectory = true;
        }

        double usedDt;

        if (forcedDT.isNaN()) {
            usedDt = dt;
        } else {
            usedDt = forcedDT;
        }

        double distance = Math.abs(getCurrentPosition() - a_targetPosition);
        var newTrajectory = BasicTrajectoryGenerator.getTrajectory(usedDt, distance, velocity, acceleration, jerk);
        if (flipTrajectory) {
            newTrajectory.flipY();
        }
        return newTrajectory;
    }

}