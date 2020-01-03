package frc.robot.commands.motion;

import com.team254.lib.util.ReflectingCSVWriter;

import edu.wpi.first.wpilibj.command.Command;
import frc.robot.subsystems.Drive;

public class LogDriveCommand extends Command {

    private class LogInfo {
        double leftVel;
        double rightVel;
        double leftVoltage;
        double rightVoltage;
    }

    private final Drive drive_ = Drive.getInstance();

    private ReflectingCSVWriter<LogInfo> writer_;

    public LogDriveCommand() {

    }

    @Override
    protected void initialize() {
        writer_ = new ReflectingCSVWriter<>("/home/lvuser/DRIVE-LOG.csv", LogInfo.class);
    }

    @Override
    protected void execute() {
        LogInfo info = new LogInfo();
        info.leftVel = drive_.getLeftLinearVelocity();
        info.rightVel = drive_.getRightLinearVelocity();
        info.leftVoltage = drive_.getLeft().getMotorOutputVoltage();
        info.rightVoltage = drive_.getRight().getMotorOutputVoltage();

        writer_.add(info);
        writer_.write();
    }

    @Override
    protected boolean isFinished() {
        return false;
    }

    @Override
    protected void end() {
        writer_.flush();
        
    }

    @Override
    protected void interrupted() {
        this.end();
    }

}