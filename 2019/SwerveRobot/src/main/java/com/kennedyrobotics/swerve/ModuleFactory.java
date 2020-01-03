package com.kennedyrobotics.swerve;

import com.kennedyrobotics.RobotFactory;
import com.kennedyrobotics.swerve.module.Module;
import com.kennedyrobotics.swerve.module.drive.DriveSparkMax;
import com.kennedyrobotics.swerve.module.ModuleID;
import com.kennedyrobotics.swerve.module.hardware.KennedyModule;
import com.kennedyrobotics.swerve.module.simulated.SimulatedModule;
import com.kennedyrobotics.swerve.odom.ModuleOdometry;
import com.revrobotics.CANSparkMaxLowLevel;
import com.team254.lib.geometry.Translation2d;
import edu.wpi.first.wpilibj.RobotBase;

public class ModuleFactory {

    private final RobotFactory rFactory_;
    private final ModuleOffsets moduleOffsets_ = new ModuleOffsets();

    public ModuleFactory(RobotFactory rFactory) {
        rFactory_ = rFactory;
    }

    public Module getModule(ModuleID moduleID, ModuleOdometry.Config odomConfig, Translation2d startingPosition) {
        if (RobotBase.isSimulation()) {
            return new SimulatedModule(moduleID, odomConfig, startingPosition);
        }

        /*
         * PID Configuration
         */
        double kP = rFactory_.getConstant("drive", "steer_kp");
        double kI = rFactory_.getConstant("drive", "steer_ki");
        double kD = rFactory_.getConstant("drive", "steer_kd");

        String prefix = moduleID.name().toLowerCase();

        KennedyModule.Config config = KennedyModule.getDefaultConfig(kP, kI, kD, odomConfig);

        config.moduleOffset = moduleOffsets_.getOffset(
                rFactory_.getConstant("drive", prefix+"_id").intValue()
        );

        return new KennedyModule(
                moduleID,
                config,
                rFactory_.getCtreMotor("drive", prefix+"_steer"),
                new DriveSparkMax(rFactory_.getRevMotor("drive", prefix+"_drive", CANSparkMaxLowLevel.MotorType.kBrushless))
        );
    }
}
