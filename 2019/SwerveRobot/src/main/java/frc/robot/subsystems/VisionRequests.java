package frc.robot.subsystems;

import com.kennedyrobotics.subsystem.requests.Request;
import com.team254.lib.geometry.Rotation2d;
import com.team254.lib.geometry.Translation2d;
import com.team254.lib.util.InterpolatingDouble;
import frc.robot.Constants;
import frc.robot.RobotState;
import frc.robot.vision.ShooterAimingParameters;

import java.util.Optional;

public class VisionRequests {

    private final RobotState robotState_;
    private final Swerve swerve_;
    private final VisionHelper vision_;

    public VisionRequests(Swerve swerve, RobotState robotState, VisionHelper vision) {
        swerve_ = swerve;
        robotState_ = robotState;
        vision_ = vision;
    }

    public Request trackRequest(double visionTargetHeight, Translation2d endTranslation, boolean hasDisk){
        return new Request(){

            @Override
            public void act() {
                vision_.robotHasDisk = hasDisk;
                vision_.useFixedVisionOrientation = false;
                vision_.visionCutoffDistance = Constants.kClosestVisionDistance;
                vision_.visionTrackingSpeed = Constants.kDefaultVisionTrackingSpeed;
                swerve_.resetVisionUpdates();
                swerve_.setVisionTrajectory(visionTargetHeight, endTranslation, false, VisionHelper.VisionState.CURVED);
            }

            @Override
            public boolean isFinished(){
                return swerve_.getState() == Swerve.ControlState.VISION && (robotState_.distanceToTarget() < vision_.visionCutoffDistance);
            }

        };
    }

    public Request trackRequest(double visionTargetHeight, Translation2d endTranslation, boolean hasDisk, Rotation2d fixedOrientation, double cutoffDistance, double trackingSpeed){
        return new Request(){

            @Override
            public void act() {
                vision_.robotHasDisk = hasDisk;
                vision_.fixedVisionOrientation = fixedOrientation;
                vision_.useFixedVisionOrientation = true;
                vision_.visionCutoffDistance = cutoffDistance;
                vision_.visionTrackingSpeed = trackingSpeed;
                vision_.resetVisionUpdates();
                vision_.setVisionTrajectory(visionTargetHeight, endTranslation, false, VisionHelper.VisionState.CURVED);
            }

            @Override
            public boolean isFinished(){
                return swerve_.getState() == Swerve.ControlState.VISION && (robotState_.distanceToTarget() < vision_.visionCutoffDistance);
            }

        };
    }

    public Request startTrackRequest(double visionTargetHeight, Translation2d endTranslation, boolean hasDisk, VisionHelper.VisionState vState){
        return new Request(){

            @Override
            public void act() {
                vision_.robotHasDisk = hasDisk;
                vision_.useFixedVisionOrientation = false;
                vision_.visionCutoffDistance = Constants.kClosestVisionDistance;
                vision_.visionTrackingSpeed = /*Constants.kDefaultVisionTrackingSpeed*/ 48.0;
                Optional<ShooterAimingParameters> aim = vision_.robotState.getAimingParameters();
                if(aim.isPresent()){
                    if(vState == VisionHelper.VisionState.LINEAR){
                        vision_.visionTrackingSpeed = Constants.kVisionSpeedTreemap.getInterpolated(new InterpolatingDouble(aim.get().getRange())).value;
                        System.out.println("Vision tracking speed set to: " + vision_.visionTrackingSpeed);
                    }
                    if(aim.get().getRange() < 54.0){
                        //visionTrackingSpeed = 30.0;
                        //System.out.println("Vision tracking speed set low");
                    }
                }
                swerve_.resetVisionUpdates();
                swerve_.setVisionTrajectory(visionTargetHeight, endTranslation, false, vState);
            }

        };
    }

    public void startTracking(double visionTargetHeight, Translation2d endTranslation, boolean hasDisk, Rotation2d fixedOrientation){
        vision_.robotHasDisk = hasDisk;
        vision_.fixedVisionOrientation = fixedOrientation;
        vision_.useFixedVisionOrientation = true;
        vision_.visionCutoffDistance = Constants.kClosestVisionDistance;
        vision_.visionTrackingSpeed = Constants.kDefaultVisionTrackingSpeed;
        swerve_.resetVisionUpdates();
        swerve_.setVisionTrajectory(visionTargetHeight, endTranslation, true, VisionHelper.VisionState.CURVED);
    }

    public Request startTrackRequest(double visionTargetHeight, Translation2d endTranslation, boolean hasDisk, Rotation2d fixedOrientation){
        return new Request(){

            @Override
            public void act() {
                vision_.robotHasDisk = hasDisk;
                vision_.fixedVisionOrientation = fixedOrientation;
                vision_.useFixedVisionOrientation = true;
                vision_.visionCutoffDistance = Constants.kClosestVisionDistance;
                vision_.visionTrackingSpeed = Constants.kDefaultVisionTrackingSpeed;
                swerve_.resetVisionUpdates();
                swerve_.setVisionTrajectory(visionTargetHeight, endTranslation, false, VisionHelper.VisionState.CURVED);
            }

        };
    }

    public Request startTrackRequest(double visionTargetHeight, Translation2d endTranslation, boolean hasDisk, Rotation2d fixedOrientation, double cutoffDistance, double trackingSpeed){
        return new Request(){

            @Override
            public void act() {
                vision_.robotHasDisk = hasDisk;
                vision_.fixedVisionOrientation = fixedOrientation;
                vision_.useFixedVisionOrientation = true;
                vision_.visionCutoffDistance = cutoffDistance;
                vision_.visionTrackingSpeed = trackingSpeed;
                swerve_.resetVisionUpdates();
                swerve_.setVisionTrajectory(visionTargetHeight, endTranslation, false, VisionHelper.VisionState.CURVED);
            }

        };
    }

    public Request waitForTrackRequest(){
        return new Request(){

            @Override
            public void act() {

            }

            @Override
            public boolean isFinished(){
                return swerve_.getState() == Swerve.ControlState.VISION && /*motionPlanner.isDone()*/ (robotState_.distanceToTarget() < vision_.visionCutoffDistance);
            }

        };
    }

}
