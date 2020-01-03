package frc.robot.subsystems;

import com.ctre.phoenix.motorcontrol.ControlMode;
import com.ctre.phoenix.motorcontrol.can.TalonSRX;
import com.team254.lib.drivers.TalonSRXFactory;

import edu.wpi.first.wpilibj.command.Subsystem;
import frc.robot.RobotMap;
import frc.robot.commands.lift.ControlDriveLiftMotorCommand;

public class LiftDrive extends Subsystem {

    private static final LiftDrive instance_ = new LiftDrive(RobotMap.kLiftDriveTalonID);

    public static LiftDrive getInstance() { return instance_; }

    // Member vatiables
    private final TalonSRX motor_;

    public LiftDrive(int id) {
        // Already initialized for you!
        motor_ = TalonSRXFactory.createDefaultTalon(id);
    }

    @Override
    protected void initDefaultCommand() {
        // No default command
        setDefaultCommand(new ControlDriveLiftMotorCommand());
    }


    /**
     * Set the speed of the motor using percentage voltage  
     * @param percent Speed of motor between -100 and 100
     */
    public void setMotor(double percent) {
        // See https://phoenix-documentation.readthedocs.io/en/latest/ch13_MC.html#test-drive-with-robot-controller
        motor_.set(ControlMode.PercentOutput, percent);
    }

    /**
     * Stop the motor
     */
    public void stop() {
        // Set neutral mode
        motor_.neutralOutput();
    }

}