package frc.robot.subsystems;

import edu.wpi.first.wpilibj.AnalogInput;
import edu.wpi.first.wpilibj.DigitalInput;
import edu.wpi.first.wpilibj.DoubleSolenoid;
import edu.wpi.first.wpilibj.command.Subsystem;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;
import frc.robot.RobotMap;

public class Lift extends Subsystem {

    private static enum Side {
        kFront,
        kBack
    }

    private static final Lift frontInstance_ = new Lift(
        Side.kFront,
        RobotMap.kFrontExtendChannel,
        RobotMap.kFrontRetractChannel,
        RobotMap.kFrontExtendSwitchChannel,
        RobotMap.kFrontRetractSwitchChannel,
        0
    );
    private static final Lift backInstance_ = new Lift(
        Side.kBack,
        RobotMap.kBackExtendChannel,
        RobotMap.kBackRetractChannel,
        RobotMap.kBackExtendSwitchChannel,
        RobotMap.kBackRetractSwitchChannel,
        1
    );

    public static Lift getFrontInstance() { return frontInstance_; }
    public static Lift getBackInstance() { return backInstance_; }

    // Member variables
    private final Side side_;
    private final String name_;
    private DoubleSolenoid solenoid_;
    private DigitalInput retractSwitch_;
    private DigitalInput extenedSwtich_;
    private AnalogInput pot_;

    public Lift(Side side, int extendChannel, int retractChannel, int extendSwitchChannel, int retractSwitchChannel, int pot) {
        side_ = side;

        if (side == Side.kFront) {
            name_ = "Front";
        } else{
            name_ = "Back";
        }

        // TODO initialize solendoid
        solenoid_ = new DoubleSolenoid(extendChannel, retractChannel);

        // TODO initialize switches/Digitial input
        // https://wpilib.screenstepslive.com/s/currentCS/m/java/l/599709-switches-using-limit-switches-to-control-behavior
        retractSwitch_ = new DigitalInput(retractSwitchChannel);
        extenedSwtich_ = new DigitalInput(extendSwitchChannel);

        pot_ = new AnalogInput(pot);
    }

    @Override
    protected void initDefaultCommand() {
        // There is no default command        
    }


    @Override
    public void periodic() {
        SmartDashboard.putNumber("Lift "+name_+" voltage", pot_.getAverageVoltage());
        SmartDashboard.putNumber("Lift "+name_+" Distance", this.getDistance());
    }

    /**
     * Is the lift exteneded
     * @return
     */
    public boolean isExtended() {
        // TODO FIX
        if (extenedSwtich_.get() == true) {
            return true;
        } else {
            return false;
        }
    }

    /**
     * Is the lift retracted?
     * @return
     */
    public boolean isRetracted() {
        // TODO FIX
        if (retractSwitch_.get() == true) {
            return true;
        } else {
            return false;
        }
    }

    /**
     * Extend the lft out of the robot
     */
    public void extend() {
        solenoid_.set(DoubleSolenoid.Value.kForward);
    }

    /**
     * Retract the lift into the robot
     */
    public void retract() {
        solenoid_.set(DoubleSolenoid.Value.kReverse);
    }

    /**
     * Stop the lift
     */
    public void stop() {
        solenoid_.set(DoubleSolenoid.Value.kOff);
    }

    /**
     * This is in some unit
     */
    public double getDistance() {
        double voltage = pot_.getAverageVoltage();
        if (side_ == Side.kFront) {
            return 6.549 * voltage - 7.532;
        } else {
            return 6.643 * voltage - 8.637;
        }
    }

}