package frc.robot.auto.actions;

import com.team254.lib.auto.actions.Action;

public class WaitForSuperstructureAction implements Action {
//	private Superstructure superstructure;
	
//	public WaitForSuperstructureAction(){
//		superstructure = Superstructure.getInstance();
//	}

	@Override
	public boolean isFinished() {
		return true; //superstructure.requestsCompleted();
	}

	@Override
	public void start() {		
	}

	@Override
	public void update() {		
	}

	@Override
	public void done() {
	}
	
}
