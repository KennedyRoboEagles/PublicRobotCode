package frc.robot.commands.lift;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import edu.wpi.first.wpilibj.command.Command;
import frc.robot.subsystems.Lift;

public class ControlLiftCommand extends Command {

    private final Logger log = LoggerFactory.getLogger("ControlLift");

    // This is a enumeration!
    // https://docs.oracle.com/javase/tutorial/java/javaOO/enum.html
    public static enum Value {
        kExtend,
        kRetract
    }

    private final Lift lift_;
    private final Value value_;

    public ControlLiftCommand(Lift lift, Value value) {
        requires(lift);
        lift_ = lift;
        value_ = value;
    }

    @Override
    protected void initialize() {
        // Nothing really
    }

    @Override
    protected void execute() {
        // http://www.c4learn.com/java/java-switch-case/
        switch (value_) {
        case kExtend:
            log.info("Extending " + lift_);
            // TODO Fill me in!
            lift_.extend();
            break;
        case kRetract:
            log.info("Retracting " + lift_);
            // TODO Fill me in!
            lift_.retract();
            break;
        }
    }

    @Override
    protected boolean isFinished() {
        // TOOD what is the exit condition
        // switch (value_) {
        // case kExtend:
        //     // TODO Fill me in!
        //     return lift_.isExtended();
        // case kRetract:
        //     // TODO Fill me in!
        //     return lift_.isRetracted();
        // }
        return false;

    }

    @Override
    protected void end() {
        log.info("Stopping " + lift_);
        lift_.stop();
    }

    @Override
    protected void interrupted() {
        log.info("Interrupted " + lift_);
        this.end();
    }
}