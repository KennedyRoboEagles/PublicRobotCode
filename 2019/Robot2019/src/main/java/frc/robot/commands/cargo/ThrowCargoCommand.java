package frc.robot.commands.cargo;

import edu.wpi.first.wpilibj.Timer;
import edu.wpi.first.wpilibj.command.Command;
import frc.robot.subsystems.CargoIntake;

public class ThrowCargoCommand extends Command {

    public static final double kTimeout = 1.5;

    private final CargoIntake intake_ = CargoIntake.getInstance();
    private final Timer timer_ = new Timer();

    public ThrowCargoCommand() {
        requires(intake_);

    }

    @Override
    protected void initialize() {
        timer_.start();
    }

    @Override
    protected void execute() {
        // intake_.throwCargo();
        intake_.set(1.0);
    }

    @Override
    protected boolean isFinished() {
        return timer_.hasPeriodPassed(kTimeout);
    }

    @Override
    protected void end() {
        intake_.stop();
        timer_.stop();
    }

    @Override
    protected void interrupted() {
        this.end();
    }


}