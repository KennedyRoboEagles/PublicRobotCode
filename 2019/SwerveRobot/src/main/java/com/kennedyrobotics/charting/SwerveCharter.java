package com.kennedyrobotics.charting;

import frc.robot.subsystems.Swerve;
import com.kennedyrobotics.swerve.module.ModuleID;
import com.team254.lib.geometry.Pose2d;
import com.team254.lib.geometry.Translation2d;
import com.kennedyrobotics.charting.Charting.FieldType;
import org.knowm.xchart.XChartPanel;
import org.knowm.xchart.XYChart;

public class SwerveCharter extends LiveCharter {

    private XYChart xyChart;

    private Swerve swerve;

    public SwerveCharter(Swerve swerve) {
        this.swerve = swerve;
        start();
    }

    public XChartPanel<XYChart> buildPanel() {

        return new XChartPanel<XYChart>(getChart());
    }

    public XYChart getChart() {
        xyChart = new Charting.ChartMaker("Chart", FieldType.HALF).build();
        xyChart.addSeries("Robot Pose", new double[] { 0 }, new double[] { 0 });
        xyChart.addSeries("Direction", new double[] { 0 }, new double[] { 0 });
        xyChart.addSeries(ModuleID.FRONT_RIGHT.name, new double[] { 0 }, new double[] { 0 });
        xyChart.addSeries(ModuleID.FRONT_LEFT.name, new double[] { 0 }, new double[] { 0 });
        xyChart.addSeries(ModuleID.REAR_LEFT.name, new double[] { 0 }, new double[] { 0 });
        xyChart.addSeries(ModuleID.REAR_RIGHT.name, new double[] { 0 }, new double[] { 0 });

        xyChart.addSeries("Path", new double[] { -1 }, new double[] { -1 });
        return xyChart;
    }

    public final double WHEEL_SIZE = 5;
    
    public void updateData() {

        var wheelPoses = swerve.getWheelPosesFieldCentric();
        var wheelTranslations = Pose2d.getListToTranslation(wheelPoses);

        // 3452 and 1323 use different coordinate systems
//        final var robotOdom2fieldTF = new Translation2d(0, FieldConstants.WIDTH/2);
        final var robotOdom2fieldTF = new Translation2d(0, 0);
//        final var robotOdom2fieldPose = new Pose2d(robotOdom2fieldTF, Rotation2d.fromDegrees(90));
//        var robotPose = swerve.getPose().transformBy(new Pose2d(robotOdom2fieldTF, Rotation2d.identity()));
        var robotPose = swerve.getPose();
        robotPose = new Pose2d(robotPose.getTranslation().translateBy(robotOdom2fieldTF), robotPose.getRotation());
        for (int i = 0; i < wheelTranslations.size(); i++) {
            wheelTranslations.set(i, wheelTranslations.get(i).translateBy(robotOdom2fieldTF));
        }

//        System.out.println("Wheels count: " + wheelTranslations.size());
//        System.out.println("Wheel pose 0:" + wheelPoses.get(0));

        for (int i = 0; i < wheelPoses.size(); i++) {
            var wheelPose = wheelPoses.get(i);

//            System.out.println("Wheel " + i + " rotation: " + wheelPose.getRotation());

            Translation2d one = wheelPose.getTranslation().translateBy(-WHEEL_SIZE, wheelPose.getRotation());
            Translation2d two = wheelPose.getTranslation().translateBy(WHEEL_SIZE, wheelPose.getRotation());

            xyChart.updateXYSeries(
                ModuleID.getName(i),
                new double[] { one.x(), two.x() },
                new double[] { one.y(), two.y() },
                new double[] { 0, 0 }
            );
        }

        xyChart.updateXYSeries("Robot Pose",
            new double[] {
                wheelTranslations.get(0).x(), wheelTranslations.get(1).x(),
                wheelTranslations.get(2).x(), wheelTranslations.get(3).x()
            },
            new double[] {
                wheelTranslations.get(0).y(), wheelTranslations.get(1).y(),
                wheelTranslations.get(2).y(), wheelTranslations.get(3).y()
            },
            new double[] { 2, 2, 2, 2 }
        );

        {
            var startOfArrow = robotPose.getTranslation();
            var endOfArrow = startOfArrow.translateBy(15, robotPose.getRotation());
            xyChart.updateXYSeries(
                "Direction",
                new double[] { startOfArrow.x(), endOfArrow.x() },
                new double[] { startOfArrow.y(), endOfArrow.y() },
                new double[] { 2, 2 }
            );
        }

        {
            final boolean followingTrajectory = swerve.followingTrajectory();
//            System.out.println("Following Trajectory: " + followingTrajectory);
            var path = swerve.getLatchedTrajectory();
//            System.out.println("Path not null: " + path == null);
            if (path != null && followingTrajectory) {
//                System.out.println("Path Length: " + path.length());

                final int length = path.length();
                double[] xData = new double[length];
                double[] yData = new double[length];
                double[] errorBars = new double[length];

                for (int i = 0; i < length; i++) {
                    Translation2d point = path.getPoint(i).state().state().getPose().getTranslation();
                    point = point.translateBy(robotOdom2fieldTF);
                    xData[i] = point.x();
                    yData[i] = point.y();
                    errorBars[i] = 0;
                }
                xyChart.updateXYSeries("Path", xData, yData, errorBars);
            } else if (!followingTrajectory) {
                xyChart.updateXYSeries("Path", new double[] {}, new double[] {}, new double[] {});
            }
        }

    }
}