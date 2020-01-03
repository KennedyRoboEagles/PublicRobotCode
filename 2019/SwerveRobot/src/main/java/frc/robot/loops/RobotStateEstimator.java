package frc.robot.loops;

import frc.robot.subsystems.Swerve;
import com.team254.lib.loops.Loop;
import frc.robot.RobotState;

public class RobotStateEstimator implements Loop {
	private static RobotStateEstimator instance = null;
	public static RobotStateEstimator getInstance(){
		if(instance == null)
			instance = new RobotStateEstimator();
		return instance;
	}
	
	RobotStateEstimator(){
	}
	
	RobotState robotState = RobotState.getInstance();
	Swerve swerve;

	@Override
	public void onStart(double timestamp) {
		swerve = Swerve.getInstance();
	}

	@Override
	public void onLoop(double timestamp) {
		robotState.addFieldToVehicleObservation(timestamp, swerve.getPose());
	}

	@Override
	public void onStop(double timestamp) {
		
	}

}
