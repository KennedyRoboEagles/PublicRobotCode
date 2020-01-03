package frc.robot.subsystems;

import edu.wpi.first.wpilibj.DoubleSolenoid;
import edu.wpi.first.wpilibj.command.Subsystem;
import frc.robot.RobotMap;

public class IntakePivot extends Subsystem {

    private static final IntakePivot instance_ = new IntakePivot();
    public static IntakePivot getInstance() { return instance_; }

    private final DoubleSolenoid solendoid_ = new DoubleSolenoid(RobotMap.kIntakePivotForwardChannel, RobotMap.kIntakePivotReverseChannel);

    @Override
    protected void initDefaultCommand() {}

    public void up() {
        solendoid_.set(DoubleSolenoid.Value.kReverse);
    }

    public void down() {
        solendoid_.set(DoubleSolenoid.Value.kForward);
    }

    public void stop() {
        solendoid_.set(DoubleSolenoid.Value.kOff);
    }
}