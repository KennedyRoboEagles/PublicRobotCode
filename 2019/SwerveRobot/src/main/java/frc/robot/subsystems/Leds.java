package frc.robot.subsystems;

import com.ctre.phoenix.CANifier;
import com.ctre.phoenix.CANifierStatusFrame;
import com.ctre.phoenix.CANifier.LEDChannel;
import com.kennedyrobotics.CANConstants;
import com.kennedyrobotics.RobotFactory;
import com.kennedyrobotics.subsystem.KennSubsystem;
import com.mach.lightdrive.Color;
import com.mach.lightdrive.LightDriveCAN;

import edu.wpi.first.wpilibj.DriverStation;
import edu.wpi.first.wpilibj.Timer;

public class Leds extends KennSubsystem {

    private final CANifier canifier_;
    private final LightDriveCAN lightDrive_;

    public Leds(RobotFactory factory) {
        canifier_ = new CANifier(factory.getConstant("canifier", "canId").intValue());
        if(canifier_.getDeviceID() >= 0) {
            canifier_.setStatusFramePeriod(CANifierStatusFrame.Status_1_General, 100, CANConstants.kLongTimeoutMs);
            canifier_.setStatusFramePeriod(CANifierStatusFrame.Status_2_General, 2, CANConstants.kLongTimeoutMs);
        }

        lightDrive_ = new LightDriveCAN();
        lightDrive_.Update();
        int version = lightDrive_.GetFWVersion();
        DriverStation.reportError("LightDrive: " + version, false);

        timer_.start();
    }

    @Override
    protected void initDefaultCommand() {

    }


    @Override
    public void outputTelemetry() {

    }

    @Override
    public void stop() {

    }

    private int state_ = 0;
    private Timer timer_ = new Timer();

    @Override
    public void periodic() {
        // canifier_.setLEDOutput(0.0, LEDChannel.LEDChannelA);
        // canifier_.setLEDOutput(0.0, LEDChannel.LEDChannelB);
        // canifier_.setLEDOutput(0.0, LEDChannel.LEDChannelC);

        lightDrive_.Update();

        if (timer_.hasPeriodPassed(0.5)) {
            timer_.reset();
            timer_.start();
            state_ = (state_+1)%6;
        }

        Color color = Color.OFF;
        switch(state_) {
        case 0:
            color = Color.BLUE;
            break;
        case 1:
            color = Color.RED;
            break;
        case 2:
            color = Color.GREEN;
            break;
        case 3:
            color = Color.TEAL;
            break;
        case 4:
            color = Color.YELLOW;
            break;
        case 5:
            color = Color.PURPLE;
            break;
        }

        lightDrive_.SetColor(1, color);
        canifier_.setLEDOutput(color.green/ 255.0, LEDChannel.LEDChannelA);
        canifier_.setLEDOutput(color.red/ 255.0, LEDChannel.LEDChannelB);
        canifier_.setLEDOutput(color.blue/ 255.0, LEDChannel.LEDChannelC);
    }

} 