package com.kennedyrobotics.swerve.module;

import com.team254.lib.geometry.Rotation2d;

public class ModuleUtil {

    private ModuleUtil() {}

    // @TODO Check for correctness, Write unit test
    public static boolean angleOnTarget(Rotation2d rotationDemand, Rotation2d moduleAngle, double toleranceDegrees) {
        return Math.abs(Math.toDegrees(
                rotationDemand.distance(moduleAngle)
        )) < toleranceDegrees;
    }

    /**
     *
     * @param currentAngle Current angle in radians
     * @param goalAngle Desired angle in radians (+/- PI)
     * @return Goal angle relative to current angle
     */
    public static double findClosestAngle(double currentAngle, double goalAngle) {
        // TODO: Does the following perserive sign? and bound the following to -/+ PI?
        double heading  = currentAngle % Math.PI;
        double offset = currentAngle - heading;

        return offset + goalAngle;
    }

}
