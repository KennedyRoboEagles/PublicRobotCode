package frc.robot.auto.actions;

import frc.robot.subsystems.Swerve;
import com.team254.lib.auto.actions.RunOnceAction;
import com.team254.lib.geometry.Translation2d;

public class DriveStraightAction extends RunOnceAction {
	Translation2d driveVector;

	public DriveStraightAction(Translation2d driveVector){
		this.driveVector = driveVector;
	}

	@Override
	public void runOnce() {
		Swerve.getInstance().sendInput(driveVector.x(), driveVector.y(), 0.0, false, false);
	}
	
}
