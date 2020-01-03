package frc.robot.commands.hatch;

import edu.wpi.first.wpilibj.Timer;
import edu.wpi.first.wpilibj.command.Command;
import frc.robot.subsystems.HatchIntake;

public class ControlHatchCommand extends Command {
    
    private static final double kTimeout = 0.5;

    public enum Direction {
        kExtend,
        kRetract
    }

    private final HatchIntake hatch_ = HatchIntake.getInstance();

    private final Direction direction_;
    private final Timer timer_ = new Timer();

    public ControlHatchCommand(Direction direction) {
        direction_ = direction;
    }

    @Override
    protected void initialize() {
        timer_.start();

    }

    @Override
    protected void execute() {
        if(direction_ == Direction.kExtend) {
            hatch_.extend();
        } else {
            hatch_.retract();
        }
    }

    @Override
    protected boolean isFinished() {
        return timer_.hasPeriodPassed(kTimeout);
    }

    @Override
    protected void end() {
        timer_.stop();
        hatch_.stop();
    }

    @Override
    protected void interrupted() {
        this.end();
    }
}