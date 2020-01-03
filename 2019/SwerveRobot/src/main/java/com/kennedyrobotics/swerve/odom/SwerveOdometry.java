package com.kennedyrobotics.swerve.odom;

import com.kennedyrobotics.swerve.module.Module;
import com.team254.lib.geometry.Pose2d;
import com.team254.lib.geometry.Rotation2d;
import com.team254.lib.geometry.Translation2d;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class SwerveOdometry {

    private Pose2d pose;
    private double distanceTraveled;
    private double currentVelocity = 0;

    public synchronized void setPose(Pose2d pose) {
        this.pose = pose;
    }
    public synchronized Pose2d getPose(){
        return pose;
    }

    public synchronized void setDistanceTraveled(double distanceTraveled ) {
        this.distanceTraveled = distanceTraveled;
    }
    public synchronized double getDistanceTraveled() {
        return distanceTraveled;
    }

    public synchronized double getCurrentVelocity() {
        return currentVelocity;
    }

    public SwerveOdometry() {
        pose = new Pose2d();
        distanceTraveled = 0;
    }

    /** The tried and true algorithm for keeping track of position */
    public synchronized void updatePose(List<Module> modules, List<Module> positionModules, Rotation2d heading, double lastUpdateTimestamp, double timestamp){
        double x = 0.0;
        double y = 0.0;

        double averageDistance = 0.0;
        double[] distances = new double[4];
        for(Module m : positionModules){
            m.updatePose(heading);
            double distance = m.getEstimatedRobotPose().getTranslation().translateBy(pose.getTranslation().inverse()).norm();
            distances[m.moduleId().id] = distance;
            averageDistance += distance;
        }
        averageDistance /= positionModules.size();

        int minDevianceIndex = 0;
        double minDeviance = 100.0;
        List<Module> modulesToUse = new ArrayList<>();
        for(Module m : positionModules){
            double deviance = Math.abs(distances[m.moduleId().id] - averageDistance);
            if(deviance < minDeviance){
                minDeviance = deviance;
                minDevianceIndex = m.moduleId().id;
            }
            if(deviance <= 0.01){
                modulesToUse.add(m);
            }
        }

        if(modulesToUse.isEmpty()){
            modulesToUse.add(modules.get(minDevianceIndex));
        }

        //SmartDashboard.putNumber("Modules Used", modulesToUse.size());

        for(Module m : modulesToUse){
            x += m.getEstimatedRobotPose().getTranslation().x();
            y += m.getEstimatedRobotPose().getTranslation().y();
        }
        Pose2d updatedPose = new Pose2d(new Translation2d(x / modulesToUse.size(), y / modulesToUse.size()), heading);
        double deltaPos = updatedPose.getTranslation().translateBy(pose.getTranslation().inverse()).norm();
        distanceTraveled += deltaPos;
        currentVelocity = deltaPos / (timestamp - lastUpdateTimestamp);
        pose = updatedPose;
        modules.forEach((m) -> m.resetPose(pose));
    }

    public synchronized void alternatePoseUpdate(List<Module> modules, List<Module> positionModules, Rotation2d heading) {
        double x = 0.0;
        double y = 0.0;

        double[][] distances = new double[4][2];
        for(Module m : modules){
            m.updatePose(heading);
            double distance = m.getEstimatedRobotPose().getTranslation().distance(pose.getTranslation());
            distances[m.moduleId().id][0] = m.moduleId().id;
            distances[m.moduleId().id][1] = distance;
        }

        Arrays.sort(distances, new java.util.Comparator<double[]>() {
            public int compare(double[] a, double[] b) {
                return Double.compare(a[1], b[1]);
            }
        });
        List<Module> modulesToUse = new ArrayList<>();
        double firstDifference = distances[1][1] - distances[0][1];
        double secondDifference = distances[2][1] - distances[1][1];
        double thirdDifference = distances[3][1] - distances[2][1];
        if(secondDifference > (1.5 * firstDifference)){
            modulesToUse.add(modules.get((int)distances[0][0]));
            modulesToUse.add(modules.get((int)distances[1][0]));
        }else if(thirdDifference > (1.5 * firstDifference)){
            modulesToUse.add(modules.get((int)distances[0][0]));
            modulesToUse.add(modules.get((int)distances[1][0]));
            modulesToUse.add(modules.get((int)distances[2][0]));
        }else{
            modulesToUse.add(modules.get((int)distances[0][0]));
            modulesToUse.add(modules.get((int)distances[1][0]));
            modulesToUse.add(modules.get((int)distances[2][0]));
            modulesToUse.add(modules.get((int)distances[3][0]));
        }

        SmartDashboard.putNumber("Modules Used", modulesToUse.size());

        for(Module m : modulesToUse){
            x += m.getEstimatedRobotPose().getTranslation().x();
            y += m.getEstimatedRobotPose().getTranslation().y();
        }

        Pose2d updatedPose = new Pose2d(new Translation2d(x / modulesToUse.size(), y / modulesToUse.size()), heading);
        double deltaPos = updatedPose.getTranslation().distance(pose.getTranslation());
        distanceTraveled += deltaPos;
        pose = updatedPose;
        modules.forEach((m) -> m.resetPose(pose));
    }
}
