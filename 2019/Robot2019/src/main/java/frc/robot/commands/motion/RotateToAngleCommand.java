package frc.robot.commands.motion;

import com.team254.lib.util.DriveSignal;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import edu.wpi.first.wpilibj.Timer;
import edu.wpi.first.wpilibj.command.Command;
import frc.robot.subsystems.Drive;

@Deprecated
public class RotateToAngleCommand extends Command {
    
	private static final double DEGREES_PRECISION = 3;
	private final Logger log = LoggerFactory.getLogger("Rotate");
	private final Timer timer = new Timer();	
	private final Drive drive_ = Drive.getInstance();

	private boolean finished = false;
	private double goalAngle = 0.0;
	private final double degreesToTurn;
	
    public RotateToAngleCommand(double degreesToTurn) {
    	if(Math.abs(degreesToTurn) > 180) {
    		throw new IllegalArgumentException("Degrees not in range +-180");
    	}
    	requires(drive_);
    	this.degreesToTurn = degreesToTurn;
    }

    // Called just before this Command runs the first time
    protected void initialize() {
    	finished = false;
		
    	System.out.println(drive_.getHeading().getDegrees());
    	goalAngle = degreesToTurn;
    	
    	timer.reset();
    	timer.start();
    	
    	log.info("Going to turn " + degreesToTurn);
    }

    // Called repeatedly when this Command is scheduled to run
    protected void execute() {
    	// if(!timer.hasPeriodPassed(0.2)) {
    	// 	return;
    	// }
    	
    	double currentAngle = drive_.getHeading().getDegrees();
    	double angleDifference = goalAngle - currentAngle;
    	//angleDifference %= 180;
    	log.info("Angle Difference " + angleDifference + " gaolAngle " + goalAngle + " currentAngle " + currentAngle);
    	
    	double turnRate = 0;
    	if(Math.abs(angleDifference) <  DEGREES_PRECISION) {
			drive_.stop();
    		finished = true;
    		return;
    	} else {
    		if(Math.abs(angleDifference) > 45) {
    			turnRate = 0.50;
    		} if(Math.abs(angleDifference) > 20) {
    			turnRate = 0.30;
    		} else { 
    			turnRate = 0.2;
    		}
    	}
    	
    	if(angleDifference < 0) {
    		turnRate = -turnRate;
		}
		
		log.info("Turn rate " + turnRate);
    	
		DriveSignal signal = new DriveSignal(-turnRate, turnRate);
		drive_.setOpenLoop(signal);
    }

    // Make this return true when this Command no longer needs to run execute()
    protected boolean isFinished() {
        return finished;
    }

    // Called once after isFinished returns true
    protected void end() {
		log.info("[TurnSpecifiedDegreesCommand] completed.");
		drive_.stop();
    	timer.stop();
    }

    // Called when another command which requires one or more of the same
    // subsystems is scheduled to run
    protected void interrupted() {
    	log.info("[TurnSpecifiedDegreesCommand] Interrupted.");
		drive_.stop();
    	timer.stop();
    }
}