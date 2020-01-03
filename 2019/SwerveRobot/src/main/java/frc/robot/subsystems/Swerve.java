package frc.robot.subsystems;

import com.kennedyrobotics.RobotFactory;
import com.kennedyrobotics.drivers.HeadingProvider;
import com.kennedyrobotics.subsystem.CheesySubsystem;
import com.kennedyrobotics.subsystem.requests.Request;
import com.kennedyrobotics.swerve.ModuleFactory;
import com.kennedyrobotics.swerve.signals.ModuleSignal;
import com.kennedyrobotics.swerve.module.Module;
import com.kennedyrobotics.swerve.module.ModuleID;
import com.kennedyrobotics.swerve.odom.ModuleOdometry;
import com.kennedyrobotics.swerve.module.MotorControlMode;
import com.kennedyrobotics.swerve.odom.SwerveOdometry;
import com.kennedyrobotics.swerve.util.SwerveHeadingController;
import com.kennedyrobotics.swerve.util.SwerveInverseKinematics;
import com.team1323.lib.math.vectors.VectorField;
import com.team254.lib.geometry.Pose2d;
import com.team254.lib.geometry.Pose2dWithCurvature;
import com.team254.lib.geometry.Rotation2d;
import com.team254.lib.geometry.Translation2d;
import com.team254.lib.loops.ILooper;
import com.team254.lib.loops.Loop;
import com.team254.lib.trajectory.TimedView;
import com.team254.lib.trajectory.Trajectory;
import com.team254.lib.trajectory.TrajectoryIterator;
import com.team254.lib.trajectory.timing.TimedState;
import com.team254.lib.util.Util;
import edu.wpi.first.wpilibj.RobotBase;
import edu.wpi.first.wpilibj.Timer;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;
import frc.robot.Constants;
import frc.robot.DriveMotionPlanner;
import frc.robot.RobotState;
import frc.robot.trajectory.TrajectoryGenerator;
import frc.robot.vision.ShooterAimingParameters;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Optional;

public class Swerve implements CheesySubsystem {

    private static Swerve instance_;
    public static void setInstance(Swerve i) {
        instance_ = i;
    }

    public static Swerve getInstance() {
        if (instance_ == null) {
            throw new IllegalStateException("Swerve instance is null");
        }

        return instance_;
    }

    //Module declaration
    List<Module> modules;
    List<Module> positionModules;


    //Evade maneuver variables
    Translation2d clockwiseCenter = new Translation2d();
    Translation2d counterClockwiseCenter = new Translation2d();
    boolean evading = false;
    boolean evadingToggled = false;
    public void toggleEvade(){
        evading = !evading;
        evadingToggled = true;
    }

    //Heading controller methods
    HeadingProvider imu;
    SwerveHeadingController headingController = new SwerveHeadingController();
    public void temporarilyDisableHeadingController(){
        headingController.temporarilyDisable();
    }
    public double getTargetHeading(){
        return headingController.getTargetHeading();
    }


    // Vision integration
    private final VisionHelper vision_ = new VisionHelper(RobotState.getInstance(), this);
    public boolean isTracking(){
        return currentState == Swerve.ControlState.VISION;
    }
    public void resetVisionUpdates() {
        vision_.resetVisionUpdates();
    }


    //Name says it all
    TrajectoryGenerator generator;

    //Odometry variables
    private SwerveOdometry odom_ = new SwerveOdometry();
    public Pose2d getPose(){
        return odom_.getPose();
    }
    private double lastUpdateTimestamp = 0;
    private final RobotState robotState = RobotState.getInstance();

    // Module configuration variables (for beginnning of auto)
    boolean modulesReady = false;
    boolean alwaysConfigureModules = false;
    boolean moduleConfigRequested = false;
    public void requireModuleConfiguration(){
        modulesReady = false;
    }
    public void alwaysConfigureModules(){
        alwaysConfigureModules = true;
    }
    Pose2d startingPose = Constants.kRobotLeftStartingPose;
    public void setStartingPose(Pose2d newPose){
        startingPose = newPose;
    }

    //Trajectory variables
    DriveMotionPlanner motionPlanner;
    public double getRemainingProgress(){
        if(motionPlanner != null && getState() == ControlState.TRAJECTORY){
            return motionPlanner.getRemainingProgress();
        }
        return 0.0;
    }
    double rotationScalar;
    double trajectoryStartTime = 0;
    Translation2d lastTrajectoryVector = new Translation2d();
    public Translation2d getLastTrajectoryVector(){ return lastTrajectoryVector; }
    boolean hasStartedFollowing = false;
    boolean hasFinishedPath = false;
    public boolean hasFinishedPath(){
        return hasFinishedPath;
    }

    //Experimental
    VectorField vf;

    private ModuleOdometry.Config getOdomConfig(ModuleID moduleID) {
        return new ModuleOdometry.Config(
                Constants.kWheelScrubFactors[moduleID.id],
                Constants.kXScrubFactor,
                Constants.kYScrubFactor,
                Constants.kSimulateReversedCarpet
        );
    }

    public Swerve(RobotFactory factory){
        ModuleFactory mFactory = new ModuleFactory(factory);
        Module frontRight = mFactory.getModule(ModuleID.FRONT_RIGHT, getOdomConfig(ModuleID.FRONT_RIGHT), Constants.kVehicleToModuleZero);
        Module frontLeft = mFactory.getModule(ModuleID.FRONT_RIGHT, getOdomConfig(ModuleID.FRONT_RIGHT), Constants.kVehicleToModuleOne);
        Module rearLeft = mFactory.getModule(ModuleID.FRONT_RIGHT, getOdomConfig(ModuleID.FRONT_RIGHT), Constants.kVehicleToModuleTwo);
        Module rearRight = mFactory.getModule(ModuleID.FRONT_RIGHT, getOdomConfig(ModuleID.FRONT_RIGHT), Constants.kVehicleToModuleThree);

        modules = Arrays.asList(frontRight, frontLeft, rearLeft, rearRight);
        positionModules = Arrays.asList(frontRight, frontLeft, rearLeft, rearRight);

        this.imu = factory.getHeadingProvider();

        motionPlanner = new DriveMotionPlanner();
        generator = TrajectoryGenerator.getInstance();
    }

    //Assigns appropriate directions for scrub factors
    public void setCarpetDirection(boolean standardDirection){
        modules.forEach((m) -> m.setCarpetDirection(standardDirection));
    }

    //Teleop driving variables
    private Translation2d translationalVector = new Translation2d();
    private double rotationalInput = 0;
    private Translation2d lastDriveVector = new Translation2d();
    private final Translation2d rotationalVector = Translation2d.identity();
    private double lowPowerScalar = 0.6;
    public void setLowPowerScalar(double scalar){
        lowPowerScalar = scalar;
    }
    private double maxSpeedFactor = 1.0;
    public void setMaxSpeed(double max){
        maxSpeedFactor = max;
    }
    private boolean robotCentric = false;

    //Swerve kinematics (exists in a separate class)
    private SwerveInverseKinematics inverseKinematics = new SwerveInverseKinematics();
    public void setCenterOfRotation(Translation2d center){
        inverseKinematics.setCenterOfRotation(center);
    }

    //The swerve's various control states
    public enum ControlState{
        NEUTRAL, MANUAL, POSITION, ROTATION, DISABLED, VECTORIZED,
        TRAJECTORY, VELOCITY, VISION
    }
    private ControlState currentState = ControlState.NEUTRAL;
    public ControlState getState(){
        return currentState;
    }
    public void setState(ControlState newState){
        currentState = newState;
    }

    /**
     * Main function used to send manual input during teleop.
     * @param x forward/backward input
     * @param y left/right input
     * @param rotate rotational input
     * @param robotCentric gyro use
     * @param lowPower scaled down output
     */
    public void sendInput(double x, double y, double rotate, boolean robotCentric, boolean lowPower){
        Translation2d translationalInput = new Translation2d(x, y);
        double inputMagnitude = translationalInput.norm();

		/* Snap the translational input to its nearest pole, if it is within a certain threshold
		  of it. */
        double threshold = Math.toRadians(10.0);
        if(Math.abs(translationalInput.direction().distance(translationalInput.direction().nearestPole())) < threshold){
            translationalInput = translationalInput.direction().nearestPole().toTranslation().scale(inputMagnitude);
        }

        double deadband = 0.25;
        if(inputMagnitude < deadband){
            translationalInput = new Translation2d();
            inputMagnitude = 0;
        }

		/* Scale x and y by applying a power to the magnitude of the vector they create, in order
		 to make the controls less sensitive at the lower end. */
        final double power = (lowPower) ? 1.75 : 1.5;
        Rotation2d direction = translationalInput.direction();
        double scaledMagnitude = Math.pow(inputMagnitude, power);
        translationalInput = new Translation2d(direction.cos() * scaledMagnitude,
                direction.sin() * scaledMagnitude);

        rotate = (Math.abs(rotate) < deadband) ? 0 : rotate;
        rotate = Math.pow(Math.abs(rotate), 1.75)*Math.signum(rotate);

        translationalInput = translationalInput.scale(maxSpeedFactor);
        rotate *= maxSpeedFactor;

        translationalVector = translationalInput;

        if(lowPower){
            translationalVector = translationalVector.scale(lowPowerScalar);
            rotate *= lowPowerScalar;
        }else{
            rotate *= 0.8;
        }

        if(rotate != 0 && rotationalInput == 0){
            headingController.disable();
        }else if(rotate == 0 && rotationalInput != 0){
            headingController.temporarilyDisable();
        }

        rotationalInput = rotate;

        if(translationalInput.norm() != 0){
            if(currentState == ControlState.VISION){
                if(Math.abs(translationalInput.direction().distance(vision_.getTargetHeading())) > Math.toRadians(150.0)){
                    setState(ControlState.MANUAL);
                }
            }else if(currentState != ControlState.MANUAL){
                setState(ControlState.MANUAL);
            }
        }else if(rotationalInput != 0){
            if(currentState != ControlState.MANUAL && currentState != ControlState.VISION && currentState != ControlState.TRAJECTORY){
                setState(ControlState.MANUAL);
            }
        }

        if(inputMagnitude > 0.3)
            lastDriveVector = new Translation2d(x, y);
        else if(translationalVector.x() == 0.0 && translationalVector.y() == 0.0 && rotate != 0.0){
            lastDriveVector = rotationalVector;
        }

        this.robotCentric = robotCentric;
    }

    //Possible new control method for rotation
    public Rotation2d averagedDirection = Rotation2d.identity();
    public void resetAveragedDirection(){
        averagedDirection = getPose().getRotation();
    }
    public void setAveragedDirection(double degrees){ averagedDirection = Rotation2d.fromDegrees(degrees); }
    public final double rotationDirectionThreshold = Math.toRadians(5.0);
    public final double rotationDivision = 1.0;
    public synchronized void updateControllerDirection(Translation2d input){
        if(Util.epsilonEquals(input.norm(), 1.0, 0.1)){
            Rotation2d direction = input.direction();
            double roundedDirection = Math.round(direction.getDegrees() / rotationDivision) * rotationDivision;
            averagedDirection = Rotation2d.fromDegrees(roundedDirection);
        }
    }

    //Various methods to control the heading controller
    public synchronized void rotate(double goalHeading){
        if(translationalVector.x() == 0 && translationalVector.y() == 0)
            rotateInPlace(goalHeading);
        else
            headingController.setStabilizationTarget(
                    Util.placeInAppropriate0To360Scope(getPose().getRotation().getDegrees(), goalHeading));
    }

    public synchronized  void rotateInPlace(double goalHeading){
        setState(ControlState.ROTATION);
        headingController.setStationaryTarget(
                Util.placeInAppropriate0To360Scope(getPose().getRotation().getDegrees(), goalHeading));
    }

    public synchronized void rotateInPlaceAbsolutely(double absoluteHeading){
        setState(ControlState.ROTATION);
        headingController.setStationaryTarget(absoluteHeading);
    }

    public synchronized  void setPathHeading(double goalHeading){
        headingController.setSnapTarget(
                Util.placeInAppropriate0To360Scope(
                        getPose().getRotation().getDegrees(), goalHeading));
    }

    public synchronized void setAbsolutePathHeading(double absoluteHeading){
        headingController.setSnapTarget(absoluteHeading);
    }

    /** Sets MotionMagic targets for the drive motors */
//    public void setPositionTarget(double directionDegrees, double magnitudeInches){
//        setState(Swerve.ControlState.POSITION);
//        modules.forEach((m) -> m.setModuleAngle(directionDegrees));
//        modules.forEach((m) -> m.setDrivePositionTarget(magnitudeInches));
//    }

    /** Locks drive motors in place with MotionMagic */
//    public void lockDrivePosition(){
//        modules.forEach((m) -> m.setDrivePositionTarget(0.0));
//    }

    /** Puts drive motors into closed-loop velocity mode */
    public void setVelocity(Rotation2d direction, double velocityInchesPerSecond){
        setState(ControlState.VELOCITY);

        modules.forEach((m) -> m.sendSignal(ModuleSignal.from(
                MotorControlMode.kVelocity,
                velocityInchesPerSecond,
                direction,
                false
        )));
    }

    /** Configures each module to match its assigned vector */
    public void setDriveOutput(List<Translation2d> driveVectors){
        for (int i=0; i<modules.size(); i++) {
            modules.get(i).sendSignal(ModuleSignal.from(
                    MotorControlMode.kVelocity,
                    driveVectors.get(i).norm(),
                    driveVectors.get(i).direction()
            ));
        }
    }

    public void setDriveOutput(List<Translation2d> driveVectors, double percentOutputOverride){
        for (int i=0; i<modules.size(); i++) {
            modules.get(i).sendSignal(ModuleSignal.from(
                    MotorControlMode.kVelocity,
                    percentOutputOverride,
                    driveVectors.get(i).direction()
            ));
        }
    }


    /** Configures each module to match its assigned vector, but puts the drive motors into closed-loop velocity mode */
    public void setVelocityDriveOutput(List<Translation2d> driveVectors){
        for (int i=0; i<modules.size(); i++) {
            modules.get(i).sendSignal(ModuleSignal.from(
                    MotorControlMode.kVelocity,
                    driveVectors.get(i).norm() * Constants.kSwerveMaxSpeedInchesPerSecond,
                    driveVectors.get(i).direction()
            ));
        }
    }

    public void setVelocityDriveOutput(List<Translation2d> driveVectors, double velocityOverride){
        for (int i=0; i<modules.size(); i++) {
            modules.get(i).sendSignal(ModuleSignal.from(
                    MotorControlMode.kVelocity,
                    velocityOverride,
                    driveVectors.get(i).direction()
            ));
        }
    }

    /** Sets only module angles to match their assigned vectors */
    public void setModuleAngles(List<Translation2d> driveVectors){
        for (int i=0; i<modules.size(); i++) {
            modules.get(i).sendSignal(ModuleSignal.from(
                    MotorControlMode.kNeutralOutput,
                    0,
                    driveVectors.get(i).direction()
            ));
        }
    }

    /** Increases each module's rotational power cap for the beginning of auto */
    public void set10VoltRotationMode(boolean tenVolts){
        modules.forEach((m) -> m.set10VoltRotationMode(tenVolts));
    }

    /**
     * @return Whether or not at least one module has reached its MotionMagic setpoint
     */
    public boolean positionOnTarget(){
        boolean onTarget = false;
        for(Module m : modules){
            onTarget |= m.drivePositionOnTarget();
        }
        return onTarget;
    }

    /**
     * @return Whether or not all modules have reached their angle setpoints
     */
    public boolean moduleAnglesOnTarget(){
        boolean onTarget = true;
        for(Module m : modules){
            onTarget &= m.angleOnTarget();
        }
        return onTarget;
    }

    /**
     * Sets a trajectory for the robot to follow
     * @param trajectory
     * @param targetHeading Heading that the robot will rotate to during its path following
     * @param rotationScalar Scalar to increase or decrease the robot's rotation speed
     * @param followingCenter The point (relative to the robot) that will follow the trajectory
     */
    public synchronized void setTrajectory(Trajectory<TimedState<Pose2dWithCurvature>> trajectory, double targetHeading,
                                           double rotationScalar, Translation2d followingCenter){
        hasStartedFollowing = false;
        hasFinishedPath = false;
        moduleConfigRequested = false;
        motionPlanner.reset();
        motionPlanner.setTrajectory(new TrajectoryIterator<>(new TimedView<>(trajectory)));
        motionPlanner.setFollowingCenter(followingCenter);
        inverseKinematics.setCenterOfRotation(followingCenter);
        setAbsolutePathHeading(targetHeading);
        this.rotationScalar = rotationScalar;
        trajectoryStartTime = Timer.getFPGATimestamp();
        setState(ControlState.TRAJECTORY);

        newPathForDisplay = true;
    }

    public synchronized void setTrajectory(Trajectory<TimedState<Pose2dWithCurvature>> trajectory, double targetHeading,
                                           double rotationScalar){
        setTrajectory(trajectory, targetHeading, rotationScalar, Translation2d.identity());
    }

    public synchronized void setRobotCentricTrajectory(Translation2d relativeEndPos, double targetHeading){
        setRobotCentricTrajectory(relativeEndPos, targetHeading, 45.0);
    }

    public synchronized void setRobotCentricTrajectory(Translation2d relativeEndPos, double targetHeading, double defaultVel){
        modulesReady = true;
        Translation2d endPos = getPose().transformBy(Pose2d.fromTranslation(relativeEndPos)).getTranslation();
        Rotation2d startHeading = endPos.translateBy(getPose().getTranslation().inverse()).direction();
        List<Pose2d> waypoints = new ArrayList<>();
        waypoints.add(new Pose2d(getPose().getTranslation(), startHeading));
        waypoints.add(new Pose2d(getPose().transformBy(Pose2d.fromTranslation(relativeEndPos)).getTranslation(), startHeading));
        Trajectory<TimedState<Pose2dWithCurvature>> trajectory = generator.generateTrajectory(false, waypoints, Arrays.asList(), 96.0, 60.0, 60.0, 9.0, defaultVel, 1);
        double heading = Util.placeInAppropriate0To360Scope(getPose().getRotation().getDegrees(), targetHeading);
        setTrajectory(trajectory, heading, 1.0);
    }

    private synchronized void setCurvedVisionTrajectory(double linearShiftDistance, Optional<ShooterAimingParameters> aimingParameters, Translation2d endTranslation, boolean overrideSafeties){
        vision_.setCurvedVisionTrajectory(linearShiftDistance, aimingParameters, endTranslation, overrideSafeties);
    }

    public synchronized void setLinearVisionTrajectory(Optional<ShooterAimingParameters> aim, Translation2d endTranslation){
        vision_.setLinearVisionTrajectory(aim, endTranslation);
    }

    /** Creates and sets a trajectory for the robot to follow, in order to approach a target and score a game piece */
    public synchronized void setVisionTrajectory(double visionTargetHeight, Translation2d endTranslation, boolean override, VisionHelper.VisionState vState){
        vision_.setVisionTrajectory(visionTargetHeight, endTranslation, override, vState);
    }

    public synchronized void setVisionTrajectory(Translation2d endTranslation, VisionHelper.VisionState vState){
        vision_.setVisionTrajectory(endTranslation, vState);
    }

    /****************************************************/
    /* Vector Fields */
    public synchronized void setVectorField(VectorField vf_) {
        vf = vf_;
        setState(ControlState.VECTORIZED);
    }

    /** Determines which wheels the robot should rotate about in order to perform an evasive maneuver */
    public synchronized void determineEvasionWheels(){
        Translation2d here = lastDriveVector.rotateBy(getPose().getRotation().inverse());
        List<Translation2d> wheels = Constants.kModulePositions;
        clockwiseCenter = wheels.get(0);
        counterClockwiseCenter = wheels.get(wheels.size()-1);
        for(int i = 0; i < wheels.size()-1; i++) {
            Translation2d cw = wheels.get(i);
            Translation2d ccw = wheels.get(i+1);
            if(here.isWithinAngle(cw,ccw)) {
                clockwiseCenter = ccw;
                counterClockwiseCenter = cw;
            }
        }
    }

    /** The tried and true algorithm for keeping track of position */
    public synchronized void updatePose(double timestamp){
        // TODO Use a getHeading method to get heading instead of accessing IMU directly
        odom_.updatePose(modules, positionModules, imu.getHeading(), lastUpdateTimestamp, timestamp);
    }

    /** Playing around with different methods of odometry. This will require the use of all four modules, however. */
    public synchronized void alternatePoseUpdate(){
        odom_.alternatePoseUpdate(modules, positionModules, imu.getHeading());
    }

    /** Called every cycle to update the swerve based on its control state */
    public synchronized void updateControlCycle(double timestamp){
        SmartDashboard.putNumber("Update Control TS", timestamp);
        double rotationCorrection = headingController.updateRotationCorrection(getPose().getRotation().getDegrees(), timestamp);

        if (RobotBase.isSimulation()) {
            final double rotationOutput = rotationalInput + rotationCorrection;

            double output = rotationOutput * 4.0;
            output = Util.limit(output, 2);

            SmartDashboard.putNumber("Rotation Output", rotationOutput);
            SmartDashboard.putNumber("Rotation Correction", rotationCorrection);

            Rotation2d current = imu.getHeading();
            Rotation2d newHeading = current.rotateBy(new Rotation2d(output));

            imu.setHeading(newHeading);
        }

        vision_.updateControlCyclePre(timestamp);

        switch(currentState){
            case MANUAL:
                if(evading && evadingToggled){
                    determineEvasionWheels();
                    double sign = Math.signum(rotationalInput);
                    if(sign == 1.0){
                        inverseKinematics.setCenterOfRotation(clockwiseCenter);
                    }else if(sign == -1.0){
                        inverseKinematics.setCenterOfRotation(counterClockwiseCenter);
                    }
                    evadingToggled = false;
                }else if(evading){
                    double sign = Math.signum(rotationalInput);
                    if(sign == 1.0){
                        inverseKinematics.setCenterOfRotation(clockwiseCenter);
                    }else if(sign == -1.0){
                        inverseKinematics.setCenterOfRotation(counterClockwiseCenter);
                    }
                }else if(evadingToggled){
                    inverseKinematics.setCenterOfRotation(Translation2d.identity());
                    evadingToggled = false;
                }
                if(translationalVector.equals(Translation2d.identity()) && rotationalInput == 0.0){
                    if(lastDriveVector.equals(rotationalVector)){
                        stop();
                    }else{
                        setDriveOutput(inverseKinematics.updateDriveVectors(lastDriveVector,
                                rotationCorrection, getPose(), robotCentric), 0.0);
                    }
                }else{
                    setDriveOutput(inverseKinematics.updateDriveVectors(translationalVector,
                            rotationalInput + rotationCorrection, getPose(), robotCentric));
                }
                break;
            case POSITION:
//                if(positionOnTarget())
//                    rotate(headingController.getTargetHeading());
//                break;

                throw new IllegalStateException();
            case ROTATION:
                setDriveOutput(inverseKinematics.updateDriveVectors(new Translation2d(), Util.deadBand(rotationCorrection, 0.1), getPose(), false));
                break;
            case VECTORIZED:
                Translation2d outputVectorV = vf.getVector(getPose().getTranslation()).scale(0.25);
                SmartDashboard.putNumber("Vector Direction", outputVectorV.direction().getDegrees());
                SmartDashboard.putNumber("Vector Magnitude", outputVectorV.norm());
//			System.out.println(outputVector.x()+" "+outputVector.y());
                setDriveOutput(inverseKinematics.updateDriveVectors(outputVectorV, rotationCorrection, getPose(), false));
                break;
            case TRAJECTORY:
                SmartDashboard.putBoolean("Motion Planner Done: ", motionPlanner.isDone());
                SmartDashboard.putNumber("Last Control Update", Timer.getFPGATimestamp());
                if(!motionPlanner.isDone()){
                    Translation2d driveVector = motionPlanner.update(timestamp, getPose());

                    if(modulesReady){
                        if(!hasStartedFollowing){
                            if(moduleConfigRequested){
                                zeroSensors(startingPose);
                                System.out.println("Position reset for auto");
                            }
                            hasStartedFollowing = true;
                        }
                        double rotationInput = Util.deadBand(Util.limit(rotationCorrection*rotationScalar*driveVector.norm(), motionPlanner.getMaxRotationSpeed()), 0.01);
                        SmartDashboard.putNumber("Last Control Velocity Update", Timer.getFPGATimestamp());
                        if(Util.epsilonEquals(driveVector.norm(), 0.0, Constants.kEpsilon)){
                            driveVector = lastTrajectoryVector;
                            setVelocityDriveOutput(inverseKinematics.updateDriveVectors(driveVector,
                                    rotationInput, getPose(), false), 0.0);
                            System.out.println("Trajectory Vector set [last]: " + driveVector.toString());
                        }else{
                            setVelocityDriveOutput(inverseKinematics.updateDriveVectors(driveVector,
                                    rotationInput, getPose(), false));
                            System.out.println("Trajectory Vector set: " + driveVector.toString());
                        }
                    } else if(!moduleConfigRequested){
                        //set10VoltRotationMode(true);
                        // TODO(RYAN) Add Smartdashboard info
                        System.out.println("Modules not ready and Module config not requested");
                        setModuleAngles(inverseKinematics.updateDriveVectors(driveVector,
                                0.0, getPose(), false));
                        moduleConfigRequested = true;
                    }

                    if (!modulesReady) {
                        System.out.println("Modules not ready");
                    }

                    if(moduleAnglesOnTarget() && !modulesReady){
                        set10VoltRotationMode(false);
                        modules.forEach((m) -> m.resetLastEncoderReading());
                        modulesReady = true;
                        System.out.println("Modules Ready");
                    }

                    lastTrajectoryVector = driveVector;
                }else{
                    if(!hasFinishedPath){
                        System.out.println("Path completed in: " + (timestamp - trajectoryStartTime));
                        hasFinishedPath = true;
                        if(alwaysConfigureModules) requireModuleConfiguration();
                    }
                }
                break;
            case VISION:
                vision_.updateControlCycle(timestamp);
    			break;
            case VELOCITY:
                throw new RuntimeException();
			    // break;
            case NEUTRAL:
                stop();
                break;
            case DISABLED:
                break;
            default:
                break;
        }
    }

    private final Loop loop = new Loop(){

        @Override
        public void onStart(double timestamp) {
            synchronized(Swerve.this){
                translationalVector = new Translation2d();
                lastDriveVector = rotationalVector;
                rotationalInput = 0;
                resetAveragedDirection();
                headingController.temporarilyDisable();
                stop();
                lastUpdateTimestamp = timestamp;
            }
        }

        @Override
        public void onLoop(double timestamp) {
            synchronized(Swerve.this){
                if(modulesReady || (getState() != ControlState.TRAJECTORY)){
                    //updatePose(timestamp);
                    alternatePoseUpdate();
                }
                updateControlCycle(timestamp);
                lastUpdateTimestamp = timestamp;
            }
        }

        @Override
        public void onStop(double timestamp) {
            synchronized(Swerve.this){
                translationalVector = new Translation2d();
                rotationalInput = 0;
                stop();
            }
        }
    };


    public Request strictWaitForTrackRequest(){
        return new Request(){

            @Override
            public void act() {

            }

            @Override
            public boolean isFinished(){
                return getState() == ControlState.VISION && motionPlanner.isDone();
            }

        };
    }

    public Request trajectoryRequest(Translation2d relativeEndPos, double targetHeading, double defaultVel){
        return new Request(){

            @Override
            public void act() {
                setRobotCentricTrajectory(relativeEndPos, targetHeading, defaultVel);
            }

            @Override
            public boolean isFinished(){
                return (getState() == ControlState.TRAJECTORY && motionPlanner.isDone()) || getState() == ControlState.MANUAL;
            }

        };
    }

    public Request startTrajectoryRequest(Translation2d relativeEndPos, double targetHeading, double defaultVel){
        return new Request(){

            @Override
            public void act() {
                setRobotCentricTrajectory(relativeEndPos, targetHeading, defaultVel);
            }

        };
    }

    public Request openLoopRequest(Translation2d input, double rotation){
        return new Request(){

            @Override
            public void act() {
                setState(ControlState.MANUAL);
                sendInput(input.x(), input.y(), rotation, false, false);
            }

        };
    }

    public Request velocityRequest(Rotation2d direction, double magnitude){
        return new Request(){

            @Override
            public void act() {
                setVelocity(direction, magnitude);
            }

        };
    }

    public void setNominalDriveOutput(double voltage){
        modules.forEach((m) -> m.setNominalDriveOutput(voltage));
    }

    /** Sets the maximum rotation speed opf the modules, based on the robot's velocity */
    public void setMaxRotationSpeed(){
        double currentDriveSpeed = translationalVector.norm() * Constants.kSwerveMaxSpeedInchesPerSecond;
        double newMaxRotationSpeed = Constants.kSwerveRotationMaxSpeed /
                ((Constants.kSwerveRotationSpeedScalar * currentDriveSpeed) + 1.0);
        modules.forEach((m) -> m.setMaxRotationSpeed(newMaxRotationSpeed));
    }

    @Override
    public synchronized void readPeriodicInputs() {
        modules.forEach((m) -> m.readPeriodicInputs());
    }

    @Override
    public synchronized void writePeriodicOutputs() {
        modules.forEach((m) -> m.writePeriodicOutputs());
    }

    @Override
    public boolean checkSystem() {
        return false;
    }

    @Override
    public void registerEnabledLoops(ILooper enabledLooper) {
        enabledLooper.register(loop);
    }

    /** Puts all rotation and drive motors into open-loop mode */
    // @TODO(Ryan) Would be nice
//    public synchronized void disable(){
//        modules.forEach((m) -> m.neutralOutput());
//        setState(Swerve.ControlState.DISABLED);
//    }

    @Override
    public synchronized void stop() {
        setState(ControlState.NEUTRAL);
        modules.forEach((m) -> m.neutralOutput());
    }

    @Override
    public synchronized void zeroSensors() {
        zeroSensors(Constants.kRobotLeftStartingPose);
    }

    /** Zeroes the drive motors, and sets the robot's internal position and heading to match that of the fed pose */
    public synchronized void zeroSensors(Pose2d startingPose){
        imu.setHeading(startingPose.getRotation());
        modules.forEach((m) -> m.zeroSensors(startingPose));
        odom_.setPose(startingPose);
        odom_.setDistanceTraveled(0);
    }

    public synchronized void resetPosition(Pose2d newPose){
        odom_.setPose(new Pose2d(newPose.getTranslation(), odom_.getPose().getRotation()));
        modules.forEach((m) -> m.zeroSensors(odom_.getPose()));
        odom_.setDistanceTraveled(0);
    }

    public synchronized void setXCoordinate(double x){
        getPose().getTranslation().setX(x);
        modules.forEach((m) -> m.zeroSensors(getPose()));
        System.out.println("X coordinate reset to: " + getPose().getTranslation().x());
    }

    public synchronized void setYCoordinate(double y){
        getPose().getTranslation().setY(y);
        modules.forEach((m) -> m.zeroSensors(getPose()));
        System.out.println("Y coordinate reset to: " + getPose().getTranslation().y());
    }

    @Override
    public synchronized void outputTelemetry() {
        modules.forEach((m) -> m.outputTelemetry());
        SmartDashboard.putNumberArray("Robot Pose", new double[]{getPose().getTranslation().x(), getPose().getTranslation().y(), getPose().getRotation().getDegrees()});
        SmartDashboard.putString("Swerve State", currentState.toString());
        if(Constants.kDebuggingOutput){
            SmartDashboard.putNumber("Robot X", getPose().getTranslation().x());
            SmartDashboard.putNumber("Robot Y", getPose().getTranslation().y());
            SmartDashboard.putNumber("Robot Heading", getPose().getRotation().getDegrees());
            SmartDashboard.putString("Heading Controller", headingController.getState().toString());
            SmartDashboard.putNumber("Target Heading", headingController.getTargetHeading());
            SmartDashboard.putNumber("Distance Traveled", odom_.getDistanceTraveled());
            SmartDashboard.putNumber("Robot Velocity", odom_.getCurrentVelocity());
            SmartDashboard.putString("Swerve State", currentState.toString());
            SmartDashboard.putBoolean("Vision Updates Allowed", vision_.visionUpdatesAllowed);
//			SmartDashboard.putNumberArray("Pigeon YPR", pigeon.getYPR());

            SmartDashboard.putBoolean("Modules angle ontarget", this.moduleAnglesOnTarget());
        }
    }

    // 3452 Changes

    public synchronized ArrayList<Pose2d> getWheelPosesFieldCentric() {
        var poses = new ArrayList<Pose2d>();
        for (int i = 0; i < modules.size(); i++) {
            poses.add(new Pose2d(modules.get(i).moduleCentricPose().getTranslation(),
                    modules.get(i).getFieldCentricAngle(getPose().getRotation())));
        }
        return poses;
    }

    public synchronized boolean followingTrajectory() {
        return currentState == ControlState.TRAJECTORY;
    }

    private boolean newPathForDisplay = false;
    public synchronized Trajectory<TimedState<Pose2dWithCurvature>> getLatchedTrajectory() {
        if (currentState != ControlState.TRAJECTORY)
            return null;

        if (newPathForDisplay) {
            newPathForDisplay = false;
            return motionPlanner.getTrajectory();
        } else {
            return null;
        }
    }

    private List<Translation2d> getWheelPositions() {
        var poses = new ArrayList<Translation2d>();
        modules.forEach((m) -> poses.add(m.getPosition()));
        return poses;
    }
}
