package frc.robot.subsystems;

import edu.wpi.first.wpilibj.DoubleSolenoid;
import edu.wpi.first.wpilibj.command.Subsystem;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;
import frc.robot.RobotMap;

public class HatchIntake extends Subsystem {

    private static final HatchIntake instance_ = new HatchIntake();
    public static HatchIntake getInstance() { return instance_; }

    private final DoubleSolenoid solendoid_ = new DoubleSolenoid(RobotMap.kIntakeHatchForwardChannel, RobotMap.kIntakeHatchReverseChannel);

    public HatchIntake() {
        SmartDashboard.putBoolean("Hatch", false);
    }

    @Override
    public void initDefaultCommand() {}


    public void extend() {
        solendoid_.set(DoubleSolenoid.Value.kReverse);
    }

    public void retract() {
        solendoid_.set(DoubleSolenoid.Value.kForward);
    }

    public void stop() {
        solendoid_.set(DoubleSolenoid.Value.kOff);
    }
}