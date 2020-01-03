package frc.robot.commands;

import com.kennedyrobotics.drive.DifferentialDriveHelper;
import com.team254.lib.util.DriveSignal;

import edu.wpi.first.wpilibj.GenericHID.Hand;
import edu.wpi.first.wpilibj.command.Command;
import frc.robot.OI;
import frc.robot.subsystems.Drive;

public class TeleopCommand extends Command {

    private final DifferentialDriveHelper driveHelper_ = new DifferentialDriveHelper();

    private final Drive drive_ = Drive.getInstance();
    private final OI oi_ = OI.getInstance();

    public TeleopCommand() {
        requires(drive_);
    }

    @Override
    protected void initialize() {
        // driveHelper_.setQuickStopAlpha(alpha);
        // driveHelper_.setQuickStopThreshold(threshold);
    }

    @Override
    protected void execute() {
        double throttle = oi_.throttle();
        double turn = oi_.rotate();

        if (oi_.secondThrottle() > 0.11) {
            throttle = oi_.secondThrottle();
            turn = 0;
        }

        throttle = Math.copySign(throttle * throttle, throttle);
        turn = Math.copySign(turn * turn, turn);

        boolean isQuickTurn = oi_.isQuickTurn();

        DriveSignal signal = driveHelper_.curvatureDrive(throttle, turn, isQuickTurn);
        drive_.setOpenLoop(signal);
    }

    @Override
    protected boolean isFinished() {
        return false;
    }

    @Override
    protected void end() {
        drive_.stop();
    }

    @Override
    protected void interrupted() {
        this.end();
    }
}