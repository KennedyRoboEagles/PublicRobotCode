package com.kennedyrobotics.swerve.odom;

import com.kennedyrobotics.swerve.module.ModuleID;
import com.team254.lib.geometry.Pose2d;
import com.team254.lib.geometry.Rotation2d;
import com.team254.lib.geometry.Translation2d;
import com.team254.lib.util.Util;

public class ModuleOdometry {

    public static class Config {
        final double scrubFactor;
        final double xScrubFactor;
        final double yScrubFactor;
        final boolean simulateReversedCarpet;

        public Config(double scrubFactor, double xScrubFactor, double yScrubFactor, boolean simulateReversedCarpet) {
            this.scrubFactor = scrubFactor;
            this.xScrubFactor = xScrubFactor;
            this.yScrubFactor = yScrubFactor;
            this.simulateReversedCarpet = simulateReversedCarpet;
        }
    }

    private final Config config_;
    private final ModuleID moduleID_;
    private Translation2d position_;
    private Translation2d startingPosition_;
    private Pose2d estimatedRobotPose_;
    private double previousEncDistance_;
    private boolean standardCarpetDirection_ = true;


    public void setStartingPosition(Translation2d startingPosition) {
        startingPosition_ = startingPosition;
    }

    public Translation2d getPosition() {
        return position_;
    }

    public void setPosition(Translation2d position) {
        position_ = position;
    }

    public Pose2d getEstimatedRobotPose() {
        return estimatedRobotPose_;
    }

    public void setEstimatedRobotPose(Pose2d pose) {
        estimatedRobotPose_ = pose;
    }

    public Translation2d getStartingPosition() {
        return startingPosition_;
    }

    public void setStandardCarpetDirection(boolean direction) {
        standardCarpetDirection_ = direction;
    }

    public ModuleOdometry(Config config, ModuleID moduleID) {
        this.config_ = config;
        this.moduleID_ = moduleID;
    }



    public void setPreviousEncDistance(double distance) {
        previousEncDistance_ = distance;
    }

    public synchronized void update(Rotation2d robotHeading, double currentEncDistance, Rotation2d moduleAngle) {
//        double currentEncDistance = module_.driveDistance();
        double deltaEncDistance = (currentEncDistance - previousEncDistance_) * config_.scrubFactor;
        Rotation2d currentWheelAngle = moduleAngle.rotateBy(robotHeading); // Field centric angle of wheel
        Translation2d deltaPosition = new Translation2d(currentWheelAngle.cos()*deltaEncDistance,
                currentWheelAngle.sin()*deltaEncDistance);

        if (moduleID_ == ModuleID.FRONT_RIGHT) {
            System.out.println("Current: " + currentEncDistance);
            System.out.println("Delta: " + deltaEncDistance);
        }

        double xScrubFactor = config_.xScrubFactor;
        double yScrubFactor = config_.yScrubFactor;
        if(config_.simulateReversedCarpet){
            if(Util.epsilonEquals(Math.signum(deltaPosition.x()), 1.0)){
                if(standardCarpetDirection_){
                    xScrubFactor = 1.0 / config_.xScrubFactor;
                }else{
                    xScrubFactor = 1.0;
                }
            }else{
                if(standardCarpetDirection_){
                    xScrubFactor = config_.xScrubFactor * config_.xScrubFactor;
                }else{

                }
            }
            if(Util.epsilonEquals(Math.signum(deltaPosition.y()), 1.0)){
                if(standardCarpetDirection_){
                    yScrubFactor = 1.0 / config_.yScrubFactor;
                }else{
                    yScrubFactor = 1.0;
                }
            }else{
                if(standardCarpetDirection_){
                    yScrubFactor = config_.yScrubFactor * config_.yScrubFactor;
                }else{

                }
            }
        }else{
            if(Util.epsilonEquals(Math.signum(deltaPosition.x()), 1.0)){
                if(standardCarpetDirection_){
                    xScrubFactor = 1.0;
                }else{

                }
            }else{
                if(standardCarpetDirection_){

                }else{
                    xScrubFactor = 1.0;
                }
            }
            if(Util.epsilonEquals(Math.signum(deltaPosition.y()), 1.0)){
                if(standardCarpetDirection_){
                    yScrubFactor = 1.0;
                }else{

                }
            }else{
                if(standardCarpetDirection_){

                }else{
                    yScrubFactor = 1.0;
                }
            }
        }

        deltaPosition = new Translation2d(deltaPosition.x() * xScrubFactor,
                deltaPosition.y() * yScrubFactor);
        Translation2d updatedPosition = position_.translateBy(deltaPosition);
        Pose2d staticWheelPose = new Pose2d(updatedPosition, robotHeading);
        Pose2d robotPose = staticWheelPose.transformBy(Pose2d.fromTranslation(startingPosition_).inverse());
        position_ = updatedPosition;
        estimatedRobotPose_ =  robotPose;
        previousEncDistance_ = currentEncDistance;

    }
}
