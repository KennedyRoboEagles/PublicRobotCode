package frc.robot.auto.actions;


import frc.robot.subsystems.Swerve;
import com.team254.lib.auto.actions.RunOnceAction;

public class SetTargetHeadingAction extends RunOnceAction {
	double targetHeading;
	Swerve swerve;
	
	public SetTargetHeadingAction(double targetHeading){
		this.targetHeading = targetHeading;
		swerve = Swerve.getInstance();
	}
	
	@Override
	public void runOnce() {
		swerve.setAbsolutePathHeading(targetHeading);
	}

}
