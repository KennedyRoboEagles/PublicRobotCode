package frc.robot.commands.characterize;

import com.team254.lib.geometry.Rotation2d;
import com.team254.lib.util.DriveSignal;

import edu.wpi.first.wpilibj.AnalogGyro;
import edu.wpi.first.wpilibj.command.Command;
import edu.wpi.first.wpilibj.interfaces.Gyro;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;
import frc.robot.subsystems.Drive;

public class CalculateTrackWidthCommand extends Command {

    public static final AnalogGyro gyro_ = new AnalogGyro(0);

    public final Drive drive_ = Drive.getInstance();
    private double goalRotations_;    

    public CalculateTrackWidthCommand(double goalRotations) {
        requires(drive_);
        goalRotations_ = goalRotations;
    }

    @Override
    protected void initialize() {
        drive_.zeroSensors();
        gyro_.reset();
    }

    @Override
    protected void execute() {
        DriveSignal signal = new DriveSignal(0.4, -0.4, true);
        drive_.setOpenLoop(signal);
    }

    @Override
    protected boolean isFinished() {
        return gyro_.getAngle() >= goalRotations_ * 360;
    }

    @Override
    protected void end() {
        drive_.stop();
        double width = calcTrackWidth(drive_.getLeftDistance(), drive_.getRightDistance(), gyro_.getAngle());
        System.out.println("calculate track width" + width);
    }

    @Override
    protected void interrupted() {
        this.end();
    }

    private double calcTrackWidth(double l, double r, double theta) {
        double n = theta / 360.0;
        double c = (Math.abs(l) + Math.abs(r)) / (2 * n);
        double d = c/Math.PI;
        return d;
    }

}