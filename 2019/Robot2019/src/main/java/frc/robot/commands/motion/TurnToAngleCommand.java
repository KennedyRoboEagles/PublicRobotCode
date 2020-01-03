package frc.robot.commands.motion;

import com.team254.lib.util.DriveSignal;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import edu.wpi.first.wpilibj.PIDController;
import edu.wpi.first.wpilibj.PIDOutput;
import edu.wpi.first.wpilibj.PIDSource;
import edu.wpi.first.wpilibj.PIDSourceType;
import edu.wpi.first.wpilibj.Preferences;
import edu.wpi.first.wpilibj.Timer;
import edu.wpi.first.wpilibj.command.Command;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;
import frc.robot.subsystems.Drive;

public class TurnToAngleCommand extends Command {

    private static final double kTurnMax = 0.35; 

    private final Logger log = LoggerFactory.getLogger("TurnToAngle");

    private enum State {
        kRun,
        kSteadyState,
        kDone
    }

    private class IMUHeading implements PIDSource {

        @Override
        public void setPIDSourceType(PIDSourceType pidSource) {}

        @Override
        public PIDSourceType getPIDSourceType() {
            return PIDSourceType.kDisplacement;
        }

        @Override
        public double pidGet() {
            return TurnToAngleCommand.this.drive_.getHeading().getDegrees();
		}

    }

    private class NullPIDOutput implements PIDOutput {

        @Override
        public void pidWrite(double output) {}

    }

    private final Preferences preferences_ = Preferences.getInstance();
    private final Drive drive_ = Drive.getInstance();
    private final PIDController controller_;
    private final double angle_;
    private final Timer timer_= new Timer();

    private State state_;

    public TurnToAngleCommand(double angle) {
        angle_ = angle;

        // Check preferences
        if (!preferences_.containsKey("turn_p")) {
            preferences_.putDouble("turn_p", 0);
        }
        if (!preferences_.containsKey("turn_i")) {
            preferences_.putDouble("turn_i", 0);
        }
        if (!preferences_.containsKey("turn_d")) {
            preferences_.putDouble("turn_d", 0);
        }
        if (!preferences_.containsKey("turn_f")) {
            preferences_.putDouble("turn_f", 0);
        }
            
        controller_ = new PIDController(0, 0, 0, 0, new IMUHeading(), new NullPIDOutput());
        controller_.setInputRange(-180, 180);
        controller_.setContinuous(true);
        controller_.setOutputRange(-kTurnMax, kTurnMax);
        controller_.setAbsoluteTolerance(2);
    }

    @Override
    protected void initialize() {
        log.info("Initialize");
        state_ = State.kRun;
        drive_.stop();
        controller_.reset();
        controller_.enable();

        double p = preferences_.getDouble("turn_p", 0);
        double i = preferences_.getDouble("turn_i", 0);
        double d = preferences_.getDouble("turn_d", 0);
        double f = preferences_.getDouble("turn_f", 0);

        controller_.setPID(p, i, d, f);
    }

    @Override
    protected void execute() {
        controller_.setSetpoint(angle_);
        double rotate = controller_.get();

        switch (state_) {
        case kRun:
            log.info("Run");
            if(controller_.onTarget()) {
                state_ = State.kSteadyState;
                timer_.reset();
                timer_.start();
            }
            break;
        case kSteadyState:
            log.info("SteadyState");
            if(timer_.hasPeriodPassed(1.0)) {
                state_ = State.kDone;
            }
            break;
        case kDone:
            log.info("Done");
            rotate = 0;
            break;
        }

        DriveSignal signal = new DriveSignal(-rotate, rotate, true);
        drive_.setOpenLoop(signal);

        SmartDashboard.putNumber("Angle error", controller_.getError());
        SmartDashboard.putNumber("Angle rotate output", rotate);
    }

    @Override
    protected boolean isFinished() {
        return state_ == State.kDone;
    }

    @Override
    protected void end() {
        log.info("Done");
        controller_.disable();
        drive_.stop();
    }

    @Override
    protected void interrupted() {
        this.end();
    }
} 