package frc.robot.subsystems;

import com.ctre.phoenix.motorcontrol.ControlMode;
import com.ctre.phoenix.motorcontrol.NeutralMode;
import com.ctre.phoenix.motorcontrol.can.TalonSRX;
import com.team254.lib.drivers.TalonSRXFactory;

import edu.wpi.first.wpilibj.DigitalInput;
import edu.wpi.first.wpilibj.command.Subsystem;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;
import frc.robot.RobotMap;

public class CargoIntake extends Subsystem {

    public static double kIntakeSpeed = 0.45;
    public static double kThrowSpeed = 0.65;

    private static final CargoIntake instance_ = new CargoIntake();
    public static CargoIntake getInstance() { return instance_; }

    private final TalonSRX motor_;
    private final DigitalInput cargoDetectFirst_ = new DigitalInput(RobotMap.kCargoDetectFirstChannel);
    private final DigitalInput cargoDetectSecond_ = new DigitalInput(RobotMap.kCargoDetectSecondChannel);

    public CargoIntake() {
        motor_ = TalonSRXFactory.createDefaultTalon(RobotMap.kCargoIntakeTalonId);
        motor_.setNeutralMode(NeutralMode.Brake);
        motor_.setInverted(true);
    }

    @Override
    protected void initDefaultCommand() {}

    @Override
    public void periodic() {
        SmartDashboard.putBoolean("Is Cargo Present First", this.isCargoPresentFirst());
        SmartDashboard.putBoolean("Is Cargo Present Second", this.isCargoPresentSecond());
    }

    public void intake() {
        motor_.set(ControlMode.PercentOutput, kIntakeSpeed);
    }

    public void set(double value) {
        motor_.set(ControlMode.PercentOutput, value);
    }

    public void throwCargo() {
        motor_.set(ControlMode.PercentOutput, kThrowSpeed);
    }

    public void stop() {
        motor_.neutralOutput();
    }

    public boolean isCargoPresentFirst() {
        return cargoDetectFirst_.get();
    }

    public boolean isCargoPresentSecond() {
        return cargoDetectSecond_.get();
    } 
 
}