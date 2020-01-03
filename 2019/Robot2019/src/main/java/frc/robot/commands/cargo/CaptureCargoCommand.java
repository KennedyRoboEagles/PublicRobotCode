package frc.robot.commands.cargo;

import edu.wpi.first.wpilibj.Timer;
import edu.wpi.first.wpilibj.command.Command;
import frc.robot.subsystems.CargoIntake;

public class CaptureCargoCommand extends Command {

    private enum State {
        kWaitForCaputre,
        KCaptured,
        kStall
    } 

    private final CargoIntake intake_ = CargoIntake.getInstance();
    private State state_;

    public CaptureCargoCommand() {
        requires(intake_);
    }

    @Override
    protected void initialize() {
        state_ = State.kWaitForCaputre;
    }

    @Override
    protected void execute() {
        switch(state_) {
        case kWaitForCaputre:
            if(intake_.isCargoPresentFirst()) {
                state_ = State.KCaptured;
                break;
            }
            intake_.set(0.75);

            break;
        case KCaptured:
            if(intake_.isCargoPresentSecond()) {
                state_ = State.kStall;
                intake_.set(-0.075);
                break;
            }
            intake_.set(0.45);
            state_ = State.KCaptured;
            break;
        case kStall:
            intake_.set(-0.075);
            break;
        }
    }

    @Override
    protected boolean isFinished() {
        return false;
    }

    @Override
    protected void end() {
        intake_.stop();
    }

    @Override
    protected void interrupted() {
        this.end();
    }
}