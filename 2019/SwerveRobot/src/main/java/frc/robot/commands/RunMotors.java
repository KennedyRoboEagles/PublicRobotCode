package frc.robot.commands;

import com.ctre.phoenix.motorcontrol.NeutralMode;
import com.kennedyrobotics.swerve.module.hardware.KennedyModule;
import com.kennedyrobotics.swerve.module.MotorControlMode;
import edu.wpi.first.wpilibj.command.Command;
import frc.robot.Robot;

public class RunMotors extends Command {

    public RunMotors() {
        requires(Robot.m_drive);
    }

    @Override
    protected void execute() {
        Robot.m_drive.setDebugControl(true);
        for (KennedyModule m : Robot.m_drive.modules()) {
            m.getDrive().set(MotorControlMode.kPercentOutput, 0.2);
            m.getSteer().setNeutralMode(NeutralMode.Coast);
            m.getSteer().neutralOutput();
        }
    }

    @Override
    protected boolean isFinished() {
        return false;
    }

    @Override
    protected void interrupted() {
        this.end();
    }

    @Override
    protected void end() {
        Robot.m_drive.stop();
        Robot.m_drive.setDebugControl(false);
        for (KennedyModule m : Robot.m_drive.modules()) {
            m.getDrive().set(MotorControlMode.kNeutralOutput, 0);
            m.getSteer().setNeutralMode(NeutralMode.Brake);
        }
    }
}
