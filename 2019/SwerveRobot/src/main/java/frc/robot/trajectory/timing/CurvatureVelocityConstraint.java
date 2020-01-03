package frc.robot.trajectory.timing;

import com.team254.lib.geometry.Pose2dWithCurvature;
import com.team254.lib.trajectory.timing.TimingConstraint;
import frc.robot.Constants;

public class CurvatureVelocityConstraint implements TimingConstraint<Pose2dWithCurvature> {

	@Override
	public double getMaxVelocity(final Pose2dWithCurvature state){
		return Constants.kSwerveMaxSpeedInchesPerSecond / (1 + Math.abs(4.0*state.getCurvature()));//6.0
	}
	
	@Override
	public MinMaxAcceleration getMinMaxAcceleration(final Pose2dWithCurvature state, final double velocity){
		return MinMaxAcceleration.kNoLimits;
	}
	
}
