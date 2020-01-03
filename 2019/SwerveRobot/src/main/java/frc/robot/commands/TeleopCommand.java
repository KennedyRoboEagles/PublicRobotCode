package frc.robot.commands;

import com.kennedyrobotics.swerve.signals.SwerveSignal;

import com.kennedyrobotics.swerve.signals.SwerveSignal.ControlOrientation;
import edu.wpi.first.wpilibj.GenericHID;
import edu.wpi.first.wpilibj.command.Command;
import frc.robot.Robot;

public class TeleopCommand extends Command {

    private boolean fieldOrient_;

    public TeleopCommand() {
        requires(Robot.m_drive);
    }

    @Override
    protected void initialize() {
        fieldOrient_ = false;
    }

    @Override
    protected void execute() {
         double xMove = -Robot.m_oi.controller.getY(GenericHID.Hand.kLeft);
         double yMove = Robot.m_oi.controller.getX(GenericHID.Hand.kLeft);
         double rotate; // = Robot.m_oi.controller.getX(Hand.kRight);

        double left = Robot.m_oi.controller.getTriggerAxis(GenericHID.Hand.kLeft);
        double right = Robot.m_oi.controller.getTriggerAxis(GenericHID.Hand.kRight);

        if(left < right) {
            rotate =  right;
        } else {
            rotate =  -left;
        }

//        double xMove = -Robot.m_oi.stick.getY();
//        double yMove = Robot.m_oi.stick.getX();
//        double rotate = Robot.m_oi.stick.getZ();
//
        if (Math.abs(xMove) < 0.15) {
            xMove = 0;
        }

        if (Math.abs(yMove) < 0.15) {
            yMove = 0;
        }

        if (Math.abs(rotate) < 0.15) {
            rotate = 0;
        }

        xMove = Math.copySign(xMove * xMove, xMove);
        yMove = Math.copySign(yMove * yMove, yMove);
        rotate = Math.copySign(rotate * rotate, rotate);

//        xMove *= 0.3;
//        yMove *= 0.3;
//        rotate *= 0.25;
        xMove *= 0.8;
        yMove *= 0.8;
        rotate *= 0.5;

        if(Robot.m_oi.controller.getAButton()) {
            fieldOrient_ = false;
        } else if (Robot.m_oi.controller.getBButton()) {
            fieldOrient_ = true;
        }

        ControlOrientation co = ControlOrientation.kRobotCentric;
        if (fieldOrient_) {
            co = ControlOrientation.kFieldCentric;
        }

        SwerveSignal signal = new SwerveSignal(xMove, yMove, rotate, false, co);

        Robot.m_drive.set(signal);
    }

    @Override
    protected boolean isFinished() {
        return false;
    }

    @Override
    protected void interrupted() {
        super.end();
    }

    @Override
    protected void end() {
        Robot.m_drive.stop();
    }

}