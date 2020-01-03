package frc.robot.auto.actions;


import frc.robot.subsystems.Swerve;
import com.team254.lib.auto.actions.Action;
import edu.wpi.first.wpilibj.Timer;

public class WaitToFinishPathAction implements Action {
	Swerve swerve;
	double timeout;
	double startTime;
	
	public WaitToFinishPathAction(){
		swerve = Swerve.getInstance();
		timeout = 15.0;
	}
	
	public WaitToFinishPathAction(double timeout){
		swerve = Swerve.getInstance();
		this.timeout = timeout;
	}
	
	@Override
	public boolean isFinished(){
		return swerve.hasFinishedPath() || ((Timer.getFPGATimestamp() - startTime) > timeout);
	}
	
	@Override
	public void start(){
		startTime = Timer.getFPGATimestamp();
	}
	
	@Override
	public void update(){
	}
	
	@Override
	public void done(){
	}
}
