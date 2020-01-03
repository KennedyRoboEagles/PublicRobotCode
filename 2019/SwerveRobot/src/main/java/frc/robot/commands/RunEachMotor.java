package frc.robot.commands;

import com.ctre.phoenix.motorcontrol.NeutralMode;
import com.kennedyrobotics.swerve.module.hardware.KennedyModule;
import com.kennedyrobotics.swerve.module.MotorControlMode;
import edu.wpi.first.wpilibj.Timer;
import edu.wpi.first.wpilibj.command.Command;
import frc.robot.Robot;
import frc.robot.subsystems.KennedyDrive;

public class RunEachMotor extends Command {

    private final KennedyDrive drive_ = Robot.m_drive;

    private int state_ = 0;
    private final Timer timer_ = new Timer();

    public RunEachMotor() {
        requires(drive_);
    }

    @Override
    protected void initialize() {
        state_ = 0;
        timer_.start();
    }

    @Override
    protected void execute() {
        if (3 < state_) return;

        int i = 0;
        for (KennedyModule m : drive_.modules()) {
            m.getDrive().set(MotorControlMode.kPercentOutput, i == state_ ? 0.2 : 0);
            m.getSteer().setNeutralMode(NeutralMode.Coast);
            m.getSteer().neutralOutput();
            i++;
        }

        if (timer_.hasPeriodPassed(5.0)) {
            timer_.reset();
            state_++;
        }
    }

    @Override
    protected boolean isFinished() {
        return state_ == 4;
    }

    @Override
    protected void end() {
        drive_.stop();
    }
}
