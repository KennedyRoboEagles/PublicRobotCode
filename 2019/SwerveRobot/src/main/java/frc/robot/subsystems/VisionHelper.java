package frc.robot.subsystems;

import com.team1323.lib.util.VisionCriteria;
import com.team254.lib.geometry.Pose2d;
import com.team254.lib.geometry.Pose2dWithCurvature;
import com.team254.lib.geometry.Rotation2d;
import com.team254.lib.geometry.Translation2d;
import com.team254.lib.trajectory.TimedView;
import com.team254.lib.trajectory.Trajectory;
import com.team254.lib.trajectory.TrajectoryIterator;
import com.team254.lib.trajectory.timing.TimedState;
import edu.wpi.first.wpilibj.DriverStation;
import frc.robot.Constants;
import frc.robot.DriveMotionPlanner;
import frc.robot.RobotState;
import frc.robot.vision.ShooterAimingParameters;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Optional;

public class VisionHelper {
    //Vision dependencies
    private final Swerve swerve_;
    RobotState robotState;
    Rotation2d visionTargetHeading = new Rotation2d();
    public Rotation2d getTargetHeading() {
        return visionTargetHeading;
    }
    boolean visionUpdatesAllowed = true;
    public void resetVisionUpdates(){
        visionUpdatesAllowed = true;
        visionUpdateCount = 0;
        attemptedVisionUpdates = 0;
        visionVisibleCycles = 0;
        firstVisionCyclePassed = false;
        visionCriteria.reset();
    }
    public enum VisionState{
        CURVED, LINEAR
    }
    VisionState visionState = VisionState.CURVED;
    double visionCurveDistance = Constants.kDefaultCurveDistance;
    Translation2d visionTargetPosition = new Translation2d();
    public Translation2d getVisionTargetPosition(){ return visionTargetPosition; }
    int visionUpdateCount = 0;
    int attemptedVisionUpdates = 0;
    int visionVisibleCycles = 0;
    boolean firstVisionCyclePassed = false;
    VisionCriteria visionCriteria = new VisionCriteria();
    double initialVisionDistance = 0.0;
    ShooterAimingParameters latestAim = new ShooterAimingParameters(100.0, new Rotation2d(), 0.0, 0.0, new Rotation2d());
    Translation2d latestTargetPosition = new Translation2d();
    Translation2d lastVisionEndTranslation = new Translation2d(-Constants.kRobotProbeExtrusion, 0.0);
    boolean visionUpdateRequested = false;
    boolean robotHasDisk = false;
    boolean useFixedVisionOrientation = false;
    Rotation2d fixedVisionOrientation = Rotation2d.fromDegrees(180.0);
    double visionCutoffDistance = Constants.kClosestVisionDistance;
    double visionTrackingSpeed = Constants.kDefaultVisionTrackingSpeed;

    public VisionHelper(RobotState robotState, Swerve swerve) {
        this.robotState = robotState;
        this.swerve_ = swerve;
    }

    boolean needsToNotifyDrivers = false;
    public boolean needsToNotifyDrivers(){
        if(needsToNotifyDrivers){
            needsToNotifyDrivers = false;
            return true;
        }
        return false;
    }

    public void updateControlCyclePre(double timestamp) {
        if(visionUpdateRequested){
            setVisionTrajectory(robotState.getVisionTargetHeight(), lastVisionEndTranslation, false, visionState);
            visionUpdateRequested = false;
        }
    }

    public void updateControlCycle(double timestamp) {
        throw new RuntimeException();
//        DriveMotionPlanner motionPlanner = swerve_.motionPlanner;
//
//        if (!motionPlanner.isDone()) {
//            visionUpdatesAllowed = elevator.inVisionRange(robotHasDisk ? Constants.kElevatorDiskVisibleRanges : Constants.kElevatorBallVisibleRanges);
//            Optional<ShooterAimingParameters> aim = robotState.getAimingParameters();
//            if (aim.isPresent() && visionUpdatesAllowed && firstVisionCyclePassed) {
//                visionVisibleCycles++;
//                latestAim = aim.get();
//                if (aim.get().getRange() < (initialVisionDistance - (Constants.kVisionDistanceStep * (visionCriteria.successfulUpdates(VisionCriteria.Criterion.DISTANCE) + 1)))
//                        && visionCriteria.updateAllowed(VisionCriteria.Criterion.DISTANCE) && aim.get().getRange() >= visionCutoffDistance) {
//                    setVisionTrajectory(lastVisionEndTranslation, visionState);
//                    visionCriteria.addSuccessfulUpdate(VisionCriteria.Criterion.DISTANCE);
//                    attemptedVisionUpdates++;
//                }
//                if (visionState == VisionState.LINEAR) {
//                    swerve_.setPathHeading(aim.get().getRobotToGoal().getDegrees());
//                }
//            }
//            Translation2d driveVector = motionPlanner.update(timestamp, swerve_.getPose());
//            if (Util.epsilonEquals(driveVector.norm(), 0.0, Constants.kEpsilon)) {
//                driveVector = swerve_.lastTrajectoryVector;
//                swerve_.setVelocityDriveOutput(swerve_.inverseKinematics.updateDriveVectors(driveVector,
//                        swerve_.rotationCorrection * rotationScalar, pose, false), 0.0);
//            } else {
//                setVelocityDriveOutput(inverseKinematics.updateDriveVectors(driveVector,
//                        rotationCorrection * rotationScalar, pose, false));
//            }
//            lastTrajectoryVector = driveVector;
//            firstVisionCyclePassed = true;
//        }
    }

    public synchronized void setCurvedVisionTrajectory( double linearShiftDistance, Optional<ShooterAimingParameters> aimingParameters, Translation2d endTranslation, boolean overrideSafeties){
        Pose2d pose = swerve_.getPose();
        DriveMotionPlanner motionPlanner = swerve_.motionPlanner;

        visionCurveDistance = linearShiftDistance;
        //System.out.println("Vision Curve Distance: " + visionCurveDistance);
        visionTargetPosition = robotState.getCaptureTimeFieldToGoal().get(2).getTranslation();
        Optional<Pose2d> orientedTarget = robotState.getOrientedTargetPosition(aimingParameters);
        lastVisionEndTranslation = endTranslation;
        if((orientedTarget.isPresent() && /*robotState.seesTarget() &&*/ visionUpdatesAllowed) || overrideSafeties){

            Rotation2d closestHeading = fixedVisionOrientation;
            double distance = 2.0 * Math.PI;
            if(!useFixedVisionOrientation){
                Rotation2d robotToTarget = orientedTarget.get().getTranslation().translateBy(pose.getTranslation().inverse()).direction();
                Rotation2d oppRobotToTarget = robotToTarget.rotateBy(Rotation2d.fromDegrees(180.0));
                if(Math.abs(pose.getRotation().distance(oppRobotToTarget)) < Math.abs(pose.getRotation().distance(robotToTarget))){
                    robotToTarget = oppRobotToTarget;
                }

                for(Rotation2d r : (robotHasDisk ? Constants.kPossibleDiskTargetAngles : Constants.kPossibleBallTargetAngles)){
                    if(Math.abs(r.distance(/*orientedTarget.get().getRotation()*/robotToTarget)) < distance){
                        closestHeading = r;
                        distance = Math.abs(r.distance(/*orientedTarget.get().getRotation()*/robotToTarget));
                    }
                }
            }
            Optional<Pose2d> robotScoringPosition = robotState.getRobotScoringPosition(aimingParameters, closestHeading, endTranslation);
            Translation2d deltaPosition = new Pose2d(orientedTarget.get().getTranslation(), closestHeading).transformBy(Pose2d.fromTranslation(new Translation2d(-linearShiftDistance, 0.0))).getTranslation().translateBy(pose.getTranslation().inverse());
            Rotation2d deltaPositionHeading = new Rotation2d(deltaPosition, true);
            Rotation2d oppositeHeading = deltaPositionHeading.rotateBy(Rotation2d.fromDegrees(180.0));
            if(Math.abs(closestHeading.distance(oppositeHeading)) < Math.abs(closestHeading.distance(deltaPositionHeading))){
                deltaPositionHeading = oppositeHeading;
            }
            System.out.println("Closest target heading: " + closestHeading.getDegrees() + ". DeltaPosHeading: " + deltaPositionHeading.getDegrees() + ". Target orientation: " + orientedTarget.get().getRotation().getDegrees());
            if(!robotScoringPosition.isEmpty()){
                if(pose.getTranslation().distance(robotScoringPosition.get().getTranslation()) <= 2.0){
                    System.out.println("Vision update rejected; robot is within 2 inches of scoring position");
                }else{
                    System.out.println("Generating vision traj, first pos is: " + pose.getTranslation().toString() + ", second pos is: " + robotScoringPosition.get().getTranslation().toString() + ", last traj vector: " + swerve_.lastTrajectoryVector.toString());
                    List<Pose2d> waypoints = new ArrayList<>();
                    waypoints.add(new Pose2d(pose.getTranslation(), (swerve_.getState() == Swerve.ControlState.VISION || swerve_.getState() == Swerve.ControlState.TRAJECTORY) ? swerve_.lastTrajectoryVector.direction() : deltaPositionHeading));
                    waypoints.add(new Pose2d(robotScoringPosition.get().getTranslation(), closestHeading));
                    Trajectory<TimedState<Pose2dWithCurvature>> trajectory = swerve_.generator.generateTrajectory(false, waypoints, Arrays.asList(), 104.0, 66.0, 66.0, 9.0, (visionUpdateCount > 1) ? swerve_.lastTrajectoryVector.norm()*Constants.kSwerveMaxSpeedInchesPerSecond : visionTrackingSpeed, 1);
                    motionPlanner.reset();
                    motionPlanner.setTrajectory(new TrajectoryIterator<>(new TimedView<>(trajectory)));
                    swerve_.setPathHeading(closestHeading.getDegrees());
                    swerve_.rotationScalar = 0.25;
                    visionTargetHeading = robotScoringPosition.get().getRotation();
                    visionUpdateCount++;
                    if(swerve_.getState() != Swerve.ControlState.VISION){
                        needsToNotifyDrivers = true;
                    }
                    visionState = VisionState.CURVED;
                    swerve_.setState(Swerve.ControlState.VISION);
                    System.out.println("Vision trajectory updated " + visionUpdateCount + " times. Distance: " + aimingParameters.get().getRange());
                }
            }
        }else{
            DriverStation.reportError("Vision update refused! " + orientedTarget.isPresent() + " " + robotState.seesTarget() + " " + visionUpdatesAllowed, false);
        }
    }

    public synchronized void setLinearVisionTrajectory(Optional<ShooterAimingParameters> aim, Translation2d endTranslation){
        Pose2d pose = swerve_.getPose();
        DriveMotionPlanner motionPlanner = swerve_.motionPlanner;

        visionTargetPosition = robotState.getCaptureTimeFieldToGoal().get(2).getTranslation();
        lastVisionEndTranslation = endTranslation;
        Optional<Pose2d> orientedTarget = robotState.getOrientedTargetPosition(aim);
        if((orientedTarget.isPresent() && robotState.seesTarget() && visionUpdatesAllowed)){

            Rotation2d closestHeading = fixedVisionOrientation;
            double distance = 2.0 * Math.PI;
            if(!useFixedVisionOrientation){
                Rotation2d robotToTarget = orientedTarget.get().getTranslation().translateBy(pose.getTranslation().inverse()).direction();
                Rotation2d oppRobotToTarget = robotToTarget.rotateBy(Rotation2d.fromDegrees(180.0));
                if(Math.abs(pose.getRotation().distance(oppRobotToTarget)) < Math.abs(pose.getRotation().distance(robotToTarget))){
                    robotToTarget = oppRobotToTarget;
                }

                for(Rotation2d r : (robotHasDisk ? Constants.kPossibleDiskTargetAngles : Constants.kPossibleBallTargetAngles)){
                    if(Math.abs(r.distance(robotToTarget)) < distance){
                        closestHeading = r;
                        distance = Math.abs(r.distance(robotToTarget));
                    }
                }
            }
            Pose2d robotScoringPosition = new Pose2d(visionTargetPosition, aim.get().getRobotToGoal()).transformBy(Pose2d.fromTranslation(new Translation2d(-Constants.kRobotHalfLength + endTranslation.x(), endTranslation.y())));

            if(pose.getTranslation().distance(robotScoringPosition.getTranslation()) <= 2.0){
                System.out.println("Vision update rejected; robot is within 2 inches of scoring position");
            }else{
                Rotation2d linearHeading = robotScoringPosition.getTranslation().translateBy(swerve_.getPose().getTranslation().inverse()).direction();
                System.out.println("Generating vision traj, first pos is: " + pose.getTranslation().toString() + ", second pos is: " + robotScoringPosition.getTranslation().toString() + ", last traj vector: " + swerve_.lastTrajectoryVector.toString());
                List<Pose2d> waypoints = new ArrayList<>();
                waypoints.add(new Pose2d(pose.getTranslation(), linearHeading));
                waypoints.add(new Pose2d(robotScoringPosition.getTranslation(), linearHeading));
                Trajectory<TimedState<Pose2dWithCurvature>> trajectory = swerve_.generator.generateTrajectory(false, waypoints, Arrays.asList(), 104.0, 66.0, 66.0, 9.0, (visionUpdateCount > 1) ? swerve_.lastTrajectoryVector.norm()*Constants.kSwerveMaxSpeedInchesPerSecond : visionTrackingSpeed, 1);
                motionPlanner.reset();
                motionPlanner.setTrajectory(new TrajectoryIterator<>(new TimedView<>(trajectory)));
                swerve_.setPathHeading(aim.get().getRobotToGoal().getDegrees());
                swerve_.rotationScalar = 0.75;
                visionTargetHeading = aim.get().getRobotToGoal();
                visionUpdateCount++;
                if(swerve_.getState() != Swerve.ControlState.VISION){
                    needsToNotifyDrivers = true;
                }
                visionState = VisionState.LINEAR;
                swerve_.setState(Swerve.ControlState.VISION);
                System.out.println("Vision trajectory updated " + visionUpdateCount + " times. Distance: " + aim.get().getRange());
            }
        }else{
            DriverStation.reportError("Vision update refused! " + orientedTarget.isPresent() + " " + robotState.seesTarget() + " " + visionUpdatesAllowed, false);
        }
    }

    /** Creates and sets a trajectory for the robot to follow, in order to approach a target and score a game piece */
    public synchronized void setVisionTrajectory(double visionTargetHeight, Translation2d endTranslation, boolean override, VisionState vState){
		Optional<ShooterAimingParameters> aim = robotState.getAimingParameters();
		visionState = vState;
		if(aim.isPresent()){
//			if(pigeon.isGood()){
//				if(aim.get().getRange() >= Constants.kClosestVisionDistance){
//					if(swerve_.getState() != Swerve.ControlState.VISION){
//						initialVisionDistance = aim.get().getRange();
//						latestAim = aim.get();
//					}
//					double previousHeight = robotState.getVisionTargetHeight();
//					robotState.setVisionTargetHeight(visionTargetHeight);
//					if(!Util.epsilonEquals(previousHeight, visionTargetHeight)){
//						robotState.clearVisionTargets();
//						lastVisionEndTranslation = endTranslation;
//						visionUpdateRequested = true;
//						System.out.println("Vision delayed until next cycle");
//					}else{
//						visionUpdatesAllowed = elevator.inVisionRange(robotHasDisk ? Constants.kElevatorDiskVisibleRanges : Constants.kElevatorBallVisibleRanges);
//						if(vState == VisionState.CURVED)
//							setCurvedVisionTrajectory(aim.get().getRange() * 0.5, aim, endTranslation, override);
//						else
//							setLinearVisionTrajectory(aim, endTranslation);
//					}
//					//System.out.println("Vision attempted");
//				}else{
//					System.out.println("Vision target too close");
//				}
//			}else{
//				System.out.println("Pigeon unresponsive");
//			}
		}else{
			visionUpdateRequested = true;
			System.out.println("Vision delayed until next cycle");
		}
    }

    public synchronized void setVisionTrajectory(Translation2d endTranslation, VisionState vState){
		Optional<ShooterAimingParameters> aim = robotState.getAimingParameters();
		visionState = vState;
		if(aim.isPresent()){
//			if(pigeon.isGood()){
//				if(aim.get().getRange() >= Constants.kClosestVisionDistance){
//					if(swerve_.getState() != Swerve.ControlState.VISION){
//						initialVisionDistance = aim.get().getRange();
//						latestAim = aim.get();
//					}
//					visionUpdatesAllowed = elevator.inVisionRange(robotHasDisk ? Constants.kElevatorDiskVisibleRanges : Constants.kElevatorBallVisibleRanges);
//					if(vState == VisionState.CURVED)
//						setCurvedVisionTrajectory(aim.get().getRange() * 0.5, aim, endTranslation, false);
//					else
//						setLinearVisionTrajectory(aim, endTranslation);
//				}else{
//					System.out.println("Vision target too close");
//				}
//			}else{
//				System.out.println("Pigeon unresponsive");
//			}
		}
    }
}
