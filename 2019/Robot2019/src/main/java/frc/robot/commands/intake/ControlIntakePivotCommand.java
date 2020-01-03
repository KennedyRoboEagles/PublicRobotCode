package frc.robot.commands.intake;

import edu.wpi.first.wpilibj.Timer;
import edu.wpi.first.wpilibj.command.Command;
import frc.robot.subsystems.IntakePivot;

public class ControlIntakePivotCommand extends Command {

    public static final double kTimeout = 4; 

    public enum Direction {
        kUp, 
        kDown
    }

    private final IntakePivot pivot_ = IntakePivot.getInstance();
    private final Timer timer_ = new Timer();
    private final Direction direction_;

    public ControlIntakePivotCommand(Direction direction) {
        requires(pivot_);
        direction_ = direction;
    }

    @Override
    protected void initialize() {
        timer_.start();
    }
    @Override
    protected void execute() {
        if (direction_ == Direction.kUp) {
            pivot_.up();
        } else {
            pivot_.down();
        }
    }

    @Override
    protected boolean isFinished() {
        return timer_.hasPeriodPassed(kTimeout);
    }

    @Override
    protected void end() {
        pivot_.stop();
        timer_.stop();
    }

    @Override
    protected void interrupted() {
        this.end();
    }
}