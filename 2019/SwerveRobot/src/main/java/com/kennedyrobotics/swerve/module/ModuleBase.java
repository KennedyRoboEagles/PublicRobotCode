package com.kennedyrobotics.swerve.module;

import com.kennedyrobotics.swerve.odom.ModuleOdometry;
import com.team254.lib.geometry.Pose2d;
import com.team254.lib.geometry.Rotation2d;
import com.team254.lib.geometry.Translation2d;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;

public abstract class ModuleBase implements Module {

    protected final ModuleID moduleID_;
    protected final ModuleOdometry.Config config_;

    protected final ModuleOdometry odom_;

    /**
     * @TODO
     * @param moduleID
     * @param config
     */
    protected ModuleBase(ModuleID moduleID, ModuleOdometry.Config config, Translation2d startingPosition) {
        moduleID_ = moduleID;
        config_ = config;
        odom_ = new ModuleOdometry(config, moduleID);
        odom_.setStartingPosition(startingPosition);
    }

    @Override
    public ModuleID moduleId() {
        return moduleID_;
    }

    @Override
    public synchronized Pose2d moduleCentricPose() {
        return new Pose2d(getPosition(), moduleAngle());
    }

    @Override
    public synchronized  Rotation2d getFieldCentricAngle(Rotation2d robotHeading) {
        Rotation2d normalizedAngle = this.moduleAngle();
        return normalizedAngle.rotateBy(robotHeading);
    }

    @Override
    public synchronized Translation2d getPosition() {
        return odom_.getPosition();
    }

    @Override
    public synchronized Pose2d getEstimatedRobotPose() {
        return odom_.getEstimatedRobotPose();
    }

    @Override
    public synchronized void updatePose(Rotation2d robotHeading) {
        odom_.update(robotHeading, driveDistance(), moduleAngle());
    }

    @Override
    public synchronized  void resetPose(Pose2d robotPose) {
        Translation2d modulePosition = robotPose.transformBy(Pose2d.fromTranslation(odom_.getStartingPosition())).getTranslation();
        odom_.setPosition(modulePosition);
    }

    @Override
    public synchronized void setCarpetDirection(boolean standardDirection) {
        odom_.setStandardCarpetDirection(standardDirection);
    }


    @Override
    public synchronized void zeroSensors(Pose2d robotPose) {
        resetPose(robotPose);
        odom_.setEstimatedRobotPose(robotPose);
        odom_.setPreviousEncDistance(driveDistance());
    }


    @Override
    public synchronized void resetLastEncoderReading() {
        odom_.setPreviousEncDistance(driveDistance());
    }


    @Override
    public synchronized void outputTelemetry() {
        if (moduleID_ == ModuleID.FRONT_LEFT) {
            SmartDashboard.putNumber(moduleID_.name() + " Drive Distance", driveDistance());
            SmartDashboard.putNumber(moduleID_.name() + " Rotation Distance", moduleAngle().getDegrees());
        }

        SmartDashboard.putBoolean(moduleID_.name() + "Angle ontarget", this.angleOnTarget());
    }

    @Override
    public synchronized void stop() {
        this.neutralOutput();
    }

}
