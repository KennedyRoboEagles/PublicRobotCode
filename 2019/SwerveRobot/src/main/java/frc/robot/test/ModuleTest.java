package frc.robot.test;

import com.ctre.phoenix.motorcontrol.IMotorControllerEnhanced;
import com.ctre.phoenix.motorcontrol.can.TalonSRX;
import com.kennedyrobotics.swerve.signals.ModuleSignal;
import com.kennedyrobotics.swerve.module.hardware.KennedyModule;

import com.kennedyrobotics.swerve.module.drive.DriveSparkMax;
import com.kennedyrobotics.swerve.module.ModuleID;
import com.kennedyrobotics.swerve.odom.ModuleOdometry;
import com.revrobotics.CANSparkMax;
import com.revrobotics.CANSparkMaxLowLevel;
import com.team254.lib.geometry.Rotation2d;
import edu.wpi.first.wpilibj.TimedRobot;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;
import frc.robot.Constants;

public class ModuleTest extends TimedRobot {

    public KennedyModule module_;

    @Override
    public void robotInit() {
        KennedyModule.Config moduleConfig = KennedyModule.getDefaultConfig(
                10, 0, 1,
                new ModuleOdometry.Config(
                        Constants.kWheelScrubFactors[ModuleID.FRONT_LEFT.id],
                        Constants.kXScrubFactor,
                        Constants.kYScrubFactor,
                        Constants.kSimulateReversedCarpet
                )
        );


        module_ = new KennedyModule(
                ModuleID.FRONT_LEFT,
                moduleConfig,
                new TalonSRX(21),
                new DriveSparkMax(new CANSparkMax(31, CANSparkMaxLowLevel.MotorType.kBrushless))
        );
        IMotorControllerEnhanced steer = module_.getSteer();

        /*
         * Max rotation speed: 295/100ms
         * 295Native/100ms * 1000ms/1sec * (2pi/1656.67 Native) = 11.18 Radians/Sec max
         */
    }

    @Override
    public void robotPeriodic() {
        
    }

    @Override
    public void teleopInit() {
        // Zero Steer
//        module_.getSteer().setSelectedSensorPosition(0, SwerveModule.kSteerPIDId, CANConstants.kLongTimeoutMs);
        module_.initialize();
    }

    @Override
    public void teleopPeriodic() {

        //        // 1656.67
//        final double countsPerRotation = 4 * 7 * 71 * 40.0/48.0;
//        double goal  = countsPerRotation / 4.0;
//
//        module_.getSteer().set(ControlMode.Position, goal);

        ModuleSignal signal = new ModuleSignal();
        signal.brake = false;
        signal.angle = Rotation2d.fromDegrees(45);
        signal.demand = 0;
        module_.sendSignal(signal);

        module_.readPeriodicInputs();
        module_.writePeriodicOutputs();


        double error = module_.getSteer().getClosedLoopError(KennedyModule.kSteerPIDId);
        double errorDeg = error / KennedyModule.kSteerNativeUnitsPerRotationAbs * 360;
        SmartDashboard.putNumber("Steer Error Raw", error);
        SmartDashboard.putNumber("Steer Error", errorDeg);

    }
}