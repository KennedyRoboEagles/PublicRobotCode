package com.kennedyrobotics.swerve.module;

import com.kennedyrobotics.swerve.signals.ModuleSignal;
import com.team254.lib.geometry.Pose2d;
import com.team254.lib.geometry.Rotation2d;
import com.team254.lib.geometry.Translation2d;
import com.kennedyrobotics.subsystem.CheesySubsystem;

/**
 * Swerve Drive Module
 */
public interface Module extends CheesySubsystem {

    ModuleID moduleId();


    /**
     * Set voltage for voltage compensation on drive motor
     * @param voltage volts
     */
    void setNominalDriveOutput(double voltage);

    /**
     * Set rotation motor voltage compentation mode
     *
     * 7 or 10 volts
     */
    void set10VoltRotationMode(boolean enable);

    // Feedback

    /**
     * Module positions in its odometry frame. IE pose in relation where the module started from
     * @return module pose
     */
    Pose2d moduleCentricPose();

    /**
     * Module's current angle in reference to the robot frame
     * @return Current angle of module
     */
    Rotation2d moduleAngle();

    /**
     * Module's current angle in reference to the field frame
     * @param robotHeading
     * @return
     */
    Rotation2d getFieldCentricAngle(Rotation2d robotHeading);

    /**
     * Current control mode of module
     * @return control mode
     */
    MotorControlMode controlMode();

    /**
     * Distance that drive wheel has traveled
     * @return distance in inches
     */
    double driveDistance();

    ///////////
    //Odom
    ///////////

    /**
     * Current module position in the module odometry frame
     * @return module position
     */
    Translation2d getPosition();

    /**
     * Estimated robot position in the module odometry frame.
     * Basically the removing modules offset from the center of the robot.
     * @return Robot pose in module frame
     */
    Pose2d getEstimatedRobotPose();

    /**
     * Update the module current pose
     * @param robotHeading Current heading of robot
     */
    void updatePose(Rotation2d robotHeading);

    /**
     * Reset the modules current pose
     * @param robotPose New pose of module
     */
    void resetPose(Pose2d robotPose);


    /**
     * @TODO
     * @param standardDirection
     */
    void setCarpetDirection(boolean standardDirection);

    // Commands

    /**
     * Send command signal to module
     * @param signal
     */
    void sendSignal(ModuleSignal signal);

    /**
     * Set module modules to neutral output
     *
     * Use setBrake() to define neutral behavior
     */
    void neutralOutput();

    /**
     * Zero sensors. Reset drive and rotation encoders to zero
     */
    default void zeroSensors() {
        this.zeroSensors(new Pose2d());
    }

    /**
     * Zero sensors. Reset drive and rotation encoders to the given pose
     *
     * @param robotPose pose to reset sensors to
     */
    void zeroSensors(Pose2d robotPose);


    void resetLastEncoderReading();

    void setMaxRotationSpeed(double maxRotationSpeed);

    boolean angleOnTarget();

    boolean drivePositionOnTarget();

}
