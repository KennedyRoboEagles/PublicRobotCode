package frc.robot.subsystems;

import com.ctre.phoenix.motorcontrol.ControlMode;
import com.ctre.phoenix.motorcontrol.FeedbackDevice;
import com.ctre.phoenix.motorcontrol.NeutralMode;
import com.ctre.phoenix.motorcontrol.StatusFrameEnhanced;
import com.ctre.phoenix.motorcontrol.can.TalonSRX;
import com.kennedyrobotics.PIDF;
import com.kennedyrobotics.drive.DifferentialDrive;
import com.kennedyrobotics.motors.PFTalonSRX;

import edu.wpi.first.wpilibj.command.Subsystem;
import frc.robot.commands.ArcadeDriveXboxCommand;

/**
 * Chassis Subsystem
 */
public class Chassis extends Subsystem {

  private static final int kTimeoutMS = 20;
  private static final int kPidId = 0;
  private static final int kSlot = 0;

  private static final double kEncoderCounts = 120;
  private static final double kEncoderCodes = 4 *kEncoderCounts;

  private static final double kWheelDiameter = 6.0 / 12.0;
  private static final double kWheelCircumference = kWheelDiameter * Math.PI;


  private static final double kClosedLoopRampRate = 0.15; //  Ramp expressed as seconds to go from neutral throttle to full throttle.
  private static final double kOpenLoopRampRate = kClosedLoopRampRate;

  private static final PIDF kLeftPIDF = new PIDF(0, 0, 0, 0);
  private static final PIDF kRightPIDF = new PIDF(0, 0, 0, 0);

  // Put methods for controlling this subsystem
  // here. Call these from Commands.
  private final PFTalonSRX left_;
  private final PFTalonSRX right_;
  private final DifferentialDrive drive_;

  public Chassis() {
    left_ = new PFTalonSRX(5);
    configureTalon(left_, kLeftPIDF);
    left_.neutralOutput();

    right_ = new PFTalonSRX(6);
    configureTalon(right_, kRightPIDF);
    right_.setInverted(true);
    right_.neutralOutput();

    drive_ = new DifferentialDrive(left_, right_);
  }

  private void configureTalon(PFTalonSRX talon, PIDF s) {
    talon.configSelectedFeedbackSensor(FeedbackDevice.QuadEncoder, kPidId, kTimeoutMS);
    talon.setInverted(false);
    talon.setSensorPhase(false);

    talon.setStatusFramePeriod(StatusFrameEnhanced.Status_3_Quadrature, 20, kTimeoutMS);

    talon.configNominalOutputForward(0.0, kTimeoutMS);
    talon.configNominalOutputReverse(0.0, kTimeoutMS);
    talon.configPeakOutputForward(1.0, kTimeoutMS);
    talon.configPeakOutputReverse(-1.0, kTimeoutMS);

    talon.configClosedloopRamp(kClosedLoopRampRate, kTimeoutMS);
    talon.configOpenloopRamp(kOpenLoopRampRate, kTimeoutMS);

    talon.configurePIDF(kSlot, kPidId, s, kTimeoutMS);
  }

  @Override
  public void initDefaultCommand() {
    // Set the default command for a subsystem here.
    setDefaultCommand(new ArcadeDriveXboxCommand());
  }

  public void setBreak(boolean state) {
    NeutralMode mode = state ? NeutralMode.Brake : NeutralMode.Coast;
    left_.setNeutralMode(mode);
    right_.setNeutralMode(mode);
  }

  public void zeroEncoders() {
    left_.setSelectedSensorPosition(0, kPidId, kTimeoutMS);
    right_.setSelectedSensorPosition(0, kPidId, kTimeoutMS);
  }

  public void setMotionMagicParamsNative(int cruiseVel, int accel) {
    left_.configMotionCruiseVelocity(cruiseVel, kTimeoutMS);
    left_.configMotionAcceleration(accel, kTimeoutMS);
    
    right_.configMotionCruiseVelocity(cruiseVel, kTimeoutMS);
    right_.configMotionAcceleration(accel, kTimeoutMS);
  } 

  public void motionMagicFeet(double left, double right) {
    // Convert into rotations
    left /= kWheelCircumference;
    right /= kWheelCircumference;

    // Convert into codes
    left *= kEncoderCodes;
    right *= kEncoderCodes;

    left_.set(ControlMode.MotionMagic, left);
    right_.set(ControlMode.MotionMagic, left);
  }

  public void stop() {
    left_.neutralOutput();
    right_.neutralOutput();
  }

  public void arcade(double move, double rotate) {
    drive_.arcadeDrive(move, rotate, true);
  }

  private double getPosition(TalonSRX talon) {
    return talon.getSelectedSensorPosition(kPidId) / kEncoderCodes * kWheelCircumference;
  }

  private double getVelocity(TalonSRX talon) {
    // TODO: Need property conversion
    return talon.getSelectedSensorVelocity(kPidId);
  }

  public double leftPosition() {
    return getPosition(left_);
  }

  public double rightPosition() {
    return getPosition(right_);
  }

  public double leftVelocity() {
    return getVelocity(left_);
  }

  public double rightVelocity() {
    return getVelocity(right_);
  }
}
