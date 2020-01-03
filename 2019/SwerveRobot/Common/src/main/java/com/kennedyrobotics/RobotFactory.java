package com.kennedyrobotics;

import com.ctre.phoenix.motorcontrol.IMotorController;
import com.ctre.phoenix.motorcontrol.IMotorControllerEnhanced;

import com.kauailabs.navx.frc.AHRS;
import com.kennedyrobotics.drivers.AHRSHeadingProvider;
import com.kennedyrobotics.drivers.CtreMotorFactory;
import com.kennedyrobotics.drivers.HeadingProvider;
import com.kennedyrobotics.drivers.SimulatedIMU;
import com.kennedyrobotics.ghost.GhostSpeedController;
import com.revrobotics.CANSparkMax;
import com.revrobotics.CANSparkMaxLowLevel;
import edu.wpi.first.wpilibj.*;

import org.yaml.snakeyaml.Yaml;
import org.yaml.snakeyaml.constructor.Constructor;

import java.util.HashMap;
import java.util.Map;

/**
 * TODO
 * Based on FRC Team 1816 The Green Machine's 2019 RobotFactory
 */
public class RobotFactory {

    private static RobotFactory instance_;
    public static RobotFactory getInstance() {
        if (instance_ == null) {
            throw new IllegalStateException("RobotFactory has not been initialized");
        } 
        return instance_;
    }

    public static RobotFactory initialize(String configName) {
        instance_ = new RobotFactory(configName);
        return instance_;
    }
    
    private YamlConfiguration config;

    public RobotFactory(String configName) {
        Yaml yaml = new Yaml(new Constructor(YamlConfiguration.class));
        config = yaml.load(
            this.getClass()
                .getClassLoader()
                .getResourceAsStream(configName + ".config.yml")
        );
    }

    public boolean isImplemented(String subsystem) {
        return (getSubsystem(subsystem) != null) && (getSubsystem(subsystem).implemented);
    }

    public IMotorControllerEnhanced getCtreMotor(String subsystem, String name) {
        if (!isImplemented(subsystem)) return CtreMotorFactory.createGhostTalon();
        YamlConfiguration.SubsystemConfig subsystemConfig = getSubsystem(subsystem);
        if (
            subsystemConfig.talons.get(name) != null &&
            subsystemConfig.talons.get(name) > -1
        ) {
            return CtreMotorFactory.createDefaultTalon(subsystemConfig.talons.get(name));
        }
        return CtreMotorFactory.createGhostTalon();
    }

    public IMotorController getCtreMotor(String subsystem, String name, String master) {
        if (!isImplemented(subsystem)) return CtreMotorFactory.createGhostTalon();
        YamlConfiguration.SubsystemConfig subsystemConfig = getSubsystem(subsystem);
        if (
            subsystemConfig.talons.get(name) != null &&
            subsystemConfig.talons.get(name) > -1 &&
            subsystemConfig.talons.get(master) != null &&
            subsystemConfig.talons.get(master) > -1
        ) {
            // Talons must be following another Talon, cannot follow a Victor.
            return CtreMotorFactory.createPermanentSlaveTalon(
                    subsystemConfig.talons.get(name), subsystemConfig.talons.get(master)
            );
        } else if (
            subsystemConfig.victors.get(name) != null &&
            subsystemConfig.victors.get(name) > -1
        ) {
            // Victors can follow Talons or another Victor.
            if (
                subsystemConfig.talons.get(master) != null &&
                subsystemConfig.talons.get(master) > -1
            ) {
                return CtreMotorFactory.createPermanentSlaveVictor(
                        subsystemConfig.victors.get(name), subsystemConfig.talons.get(master)
                );
            } else if (
                subsystemConfig.victors.get(master) != null &&
                subsystemConfig.victors.get(master) > -1
            ) {
                return CtreMotorFactory.createPermanentSlaveVictor(
                        subsystemConfig.victors.get(name), subsystemConfig.victors.get(master)
                );
            }
        }
        return CtreMotorFactory.createGhostTalon();
    }

    public SpeedController getPWMMotor(String subsystem, String name) {
        if (!isImplemented(subsystem)) return new GhostSpeedController();

        YamlConfiguration.SubsystemConfig subsystemConfig = getSubsystem(subsystem);
        if (
            subsystemConfig.talonSRs.get(name) != null &&
            subsystemConfig.talonSRs.get(name) > -1
        ) {
            return new Talon(subsystemConfig.talonSRs.get(name));
        }

        return new GhostSpeedController();
    }

//    public SparkMax getRevMotor(String subsystem, String name, CANSparkMaxLowLevel.MotorType type) {
//        if (!isImplemented(subsystem)) return new GhostSparkMax(type);
//
//        YamlConfiguration.SubsystemConfig subsystemConfig = getSubsystem(subsystem);
//        if (
//                subsystemConfig.sparks.get(name) != null &&
//                        subsystemConfig.talonSRs.get(name) > -1
//        ) {
//            return new KennCANSparkMax(subsystemConfig.talonSRs.get(name), type);
//        }
//
//        return new GhostSparkMax(type);
//    }

    public CANSparkMax getRevMotor(String subsystem, String name, CANSparkMaxLowLevel.MotorType type) {
        if (!isImplemented(subsystem)) return null;

        YamlConfiguration.SubsystemConfig subsystemConfig = getSubsystem(subsystem);
        if (
                subsystemConfig.sparks.get(name) != null &&
                    subsystemConfig.sparks.get(name) > -1
        ) {
            return new CANSparkMax(subsystemConfig.sparks.get(name), type);
        }

        return null;
    }

    public Solenoid getSolenoid(String subsystem, String name) {
        Integer solenoidId = getSubsystem(subsystem).solenoids.get(name);
        if (solenoidId != null) {
            return new Solenoid(config.pcm, solenoidId);
        }
        return null;
    }

    public DoubleSolenoid getDoubleSolenoid(String subsystem, String name) {
        YamlConfiguration.DoubleSolenoidConfig solenoidConfig = getSubsystem(subsystem).doubleSolenoids.get(name);
        if (solenoidConfig != null) {
            return new DoubleSolenoid(config.pcm, solenoidConfig.forward, solenoidConfig.reverse);
        }
        return null;
    }

    public HeadingProvider getHeadingProvider() {
        if(RobotBase.isSimulation()) {
            return new SimulatedIMU();
        }

        // TODO Allow this to be configurable
        return new AHRSHeadingProvider(new AHRS(SerialPort.Port.kUSB));
    }

    public Double getConstant(String name) {
        return config.constants.get(name);
    }

    public Double getConstant(String subsystem, String name) {
        //System.out.println(config.constants.toString());
        return getSubsystem(subsystem).constants.get(name);
    }

    public YamlConfiguration getConfig() {
        return config;
    }

    public YamlConfiguration.SubsystemConfig getSubsystem(String subsystem) {
        return config.subsystems.get(subsystem);
    }

    public static class YamlConfiguration {
        public Map<String, SubsystemConfig> subsystems;
        public Map<String, Double> constants = new HashMap<>();
        public int pcm;

        public static class SubsystemConfig {
            public boolean implemented = false;
            public Map<String, Integer> sparks = new HashMap<>();
            public Map<String, Integer> talons = new HashMap<>();
            public Map<String, Integer> talonSRs = new HashMap<>();
            public Map<String, Integer> victors = new HashMap<>();
            public Map<String, Integer> solenoids = new HashMap<>();
            public Map<String, DoubleSolenoidConfig> doubleSolenoids = new HashMap<>();
            public Map<String, Double> constants = new HashMap<>();

            @Override
            public String toString() {
                return "CheesySubsystem {\n" +
                        "  implemented = " + implemented + ",\n" +
                        "  sparks = " + sparks.toString() + ",\n" +
                        "  talons = " + talons.toString() + ",\n" +
                        "  talonSRs = " + talonSRs.toString() + ",\n" +
                        "  victors = " + victors.toString() + ",\n" +
                        "  solenoids = " + solenoids.toString() + ",\n" +
                        "  doubleSolenoids = " + doubleSolenoids.toString() + ",\n" +
                        "  constants = " + constants.toString() + ",\n" +
                        "}";
            }
        }

        public static class DoubleSolenoidConfig {
            public int forward;
            public int reverse;

            @Override
            public String toString() {
                return String.format("{ forward: %d, reverse: %d }", forward, reverse);
            }
        }

        @Override
        public String toString() {
            return "YamlConfiguration {\n  subsystems = " + subsystems.toString() +
                    "\n  pcm = " + pcm + "\n  constants = " + constants.toString( )+ "\n}";
        }
    }
}
