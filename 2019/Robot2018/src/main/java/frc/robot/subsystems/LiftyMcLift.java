/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

package frc.robot.subsystems;

import com.ctre.phoenix.motorcontrol.can.VictorSPX;

import edu.wpi.first.wpilibj.DigitalInput;
import edu.wpi.first.wpilibj.Encoder;
import edu.wpi.first.wpilibj.CounterBase.EncodingType;
import edu.wpi.first.wpilibj.command.Subsystem;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;
import frc.robot.RobotMap;

/**
 * Add your docs here.
 */
public class LiftyMcLift extends Subsystem {
  // Put methods for controlling this subsystem
  // here. Call these from Commands.
  private final double kMeterPerRotation = 0.0791972 * Math.PI * (12.0/36.0);
  private final double kEncoderPulses = 120;
  private final double kDistancePerPulse = kMeterPerRotation / kEncoderPulses;
  private final double kHightOffset = .322;

  private final DigitalInput limit1_ = new DigitalInput(RobotMap.kLiftLimit1);
  private final DigitalInput limit2_ = new DigitalInput(RobotMap.kLiftLimit2);
  private final DigitalInput limit3_ = new DigitalInput(RobotMap.kLiftLimit3);

  private final Encoder encoder_ = new Encoder(
    RobotMap.kLiftEncoderA, 
    RobotMap.kLiftEncoderB,
    false, // Sensor Phase
    EncodingType.k4X
  );

  private final VictorSPX motor_ = new VictorSPX(RobotMap.kLiftMotorCanID);

  public LiftyMcLift(){
    motor_.configFactoryDefault();
    motor_.setInverted(false);

    encoder_.setDistancePerPulse(kDistancePerPulse); // Convert Encoder pulses to meters
  }

  @Override
  public void initDefaultCommand() {
    // Set the default command for a subsystem here.
    // setDefaultCommand(new MySpecialCommand());
  }

  @Override
  public void periodic() {
    SmartDashboard.putBoolean("Lift 1st Limit", this.isAt1stLimit());
    SmartDashboard.putBoolean("Lift 2nd Limit", this.isAt2ndLimit());
    SmartDashboard.putBoolean("Lift 3rd Limit", this.isAt3rdLimit());
    SmartDashboard.putBoolean("Lift At Bottom", this.isAtBottomLimit());

    SmartDashboard.putNumber("Lift Hight(m)", this.getHeight()); 
    SmartDashboard.putNumber("Lift Encoder Raw", encoder_.get()); 
  }

  public boolean isAt1stLimit() {
    return limit1_.get();
  }
  
  public boolean isAt2ndLimit() {
    return !limit2_.get();
  }

  public boolean isAt3rdLimit() {
    return !limit3_.get();
  }

  public boolean isAtBottomLimit() {
    return this.isAt1stLimit() && this.isAt2ndLimit() && this.isAt3rdLimit();
  }

  /**
   * Get height in meters
   * @return maters
   */
  public double getHeight() {
    double distance = encoder_.get();
    double cm = 0.0583823 * distance + 32.21158;
    return cm / 100.0; // To meters
  }
}
