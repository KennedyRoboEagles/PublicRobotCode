package com.kennedyrobotics.subsystem;

import com.kennedyrobotics.log.Logger;
import com.kennedyrobotics.logging.AutoLoggerFactory;
import com.kennedyrobotics.logging.Loggable;
import edu.wpi.first.wpilibj.command.Subsystem;

import java.lang.reflect.Field;

/**
 * This is the class that every subsystem should subclass
 *
 * Based on Team 1014 Badrobots' 2019 BadSubsystem
 * https://github.com/BadRobots1014/2019_Shepard/blob/master/src/main/java/frc/robot/subsystem/BadSubsystem.java
 */
public abstract class KennSubsystem extends Subsystem implements CheesySubsystem, Loggable {

    /**
     * Make sure this is called in subclass constructors.
     */
    public KennSubsystem() {
        super();
    }

//    /**
//     * Initialize the motors, sensors, etc for a subsystem
//     */
//    public abstract void initComponents();

    /**
     * Verify that all of the subsystem's fields are initialized. This should be called after
     * late in the constructor after all fields have been constructed.
     */
    private void verifyFieldInitialization() {
        for (Field field : getClass().getDeclaredFields()) {
            try {
                field.setAccessible(true);
                if (field.get(this) == null) {
                    Logger.log("Field " + field.getName() + " was not initialized");
                }
            } catch (IllegalArgumentException | IllegalAccessException e) {
                e.printStackTrace();
            }
        }
    }

    /**
     * Final initialization code
     * @todo doc
     */
    protected void postConstruction() {
        verifyFieldInitialization();
        initLogging();
    }

//    /**
//     * Initialize the fields that are sent to the SmartDashboard/Shuffleboard. This method is
//     * automatically called by WPILIB.
//     */
//    @Override
//    public abstract void initSendable(SendableBuilder builder);

    /**
     * Initialize logging for all of the subsystem's components. All components should be
     * initialized before this is called. By default this method will try to log a component using
     * {@link com.kennedyrobotics.logging.AutoLoggerFactory#log(String, String, Object)}.
     *
     * @see badlog.lib.BadLog
     * @see com.kennedyrobotics.logging.AutoLoggerFactory
     */
    @Override
    public void initLogging() {
        String subsystemName = getName();
        Object obj;
        String deviceName;

        for (Field field : getClass().getDeclaredFields()) {
            try {
                obj = field.get(this);
                deviceName = field.getName();
                AutoLoggerFactory.log(subsystemName, deviceName, obj);
            } catch (NoClassDefFoundError e) {
                Logger.log(e.getMessage());
            } catch (Exception e) {
                continue;
            }
        }
    }

    @Override
    protected void initDefaultCommand() {
        System.out.println("No Default Command Set For " + getName());
    }

    /**
     * This should stop all physical movement of the subsystem
     */
    public abstract void stop();

    @Override
    public boolean checkSystem() {
        return false;
    }


//    /**
//     * Release all of the resources that are used by this subsystem. This should only be called by
//     * WPILIB.
//     */
//    @Override
//    public abstract void close();

//    /**
//     * This should test all of the methods in this subsystem and attept to validate the effects
//     * using JUnit assertions. {@link #stop()} should be called at the end of the test.
//     */
//    @Test
//    public abstract void test();

//    /**
//     * Convience method for {@link Timer#delay(double)}.
//     *
//     * @param seconds duration of sleep
//     */
//    protected void sleep(double seconds) {
//        Timer.delay(seconds);
//    }

//    /**
//     * This must be overridden in every subclass, as it is disabled by default
//     *
//     * @todo intergrate with RobotFactory
//     *
//     * @return whether or not the subsystem should be initialized
//     */
//    public static boolean isEnabled() {
//        return false;
//    }


}
