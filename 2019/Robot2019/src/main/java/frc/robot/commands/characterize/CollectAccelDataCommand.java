package frc.robot.commands.characterize;

import java.util.List;

import com.team254.lib.physics.DriveCharacterization;
import com.team254.lib.util.DriveSignal;
import com.team254.lib.util.ReflectingCSVWriter;
import com.team254.lib.util.Util;

import edu.wpi.first.wpilibj.Timer;
import edu.wpi.first.wpilibj.command.Command;
import frc.robot.subsystems.Drive;

public class CollectAccelDataCommand extends Command {

    private static final double kPower = 0.5;
    private static final double kTotalTime = 2.0; //how long to run the test for
    private static final Drive mDrive = Drive.getInstance();

    private final ReflectingCSVWriter<DriveCharacterization.AccelerationDataPoint> mCSVWriter;
    private final List<DriveCharacterization.AccelerationDataPoint> mAccelerationData;
    private final boolean mTurn;
    private final boolean mReverse;

    private double mStartTime = 0.0;
    private double mPrevVelocity = 0.0;
    private double mPrevTime = 0.0;

    private final Timer mTimer = new Timer();


    /**
     * @param data     reference to the list where data points should be stored
     * @param reverse  if true drive in reverse, if false drive normally
     * @param turn     if true turn, if false drive straight
     */
    public CollectAccelDataCommand(List<DriveCharacterization.AccelerationDataPoint> data, boolean reverse, boolean turn) {
        requires(Drive.getInstance());
        mAccelerationData = data;
        mReverse = reverse;
        mTurn = turn;
        mCSVWriter = new ReflectingCSVWriter<>("/home/lvuser/ACCEL_DATA.csv", DriveCharacterization.AccelerationDataPoint.class);
    }

    @Override
    protected void initialize() {
        mTimer.reset();
        mTimer.start();

        mStartTime = 0;
        mPrevVelocity = 0;
        mPrevTime = 0;
        mAccelerationData.clear();
    
        mDrive.setOpenLoop(new DriveSignal((mReverse ? -1.0 : 1.0) * kPower, (mReverse ? -1.0 : 1.0) * (mTurn ? -1.0 : 1.0) * kPower));
        mStartTime = Timer.getFPGATimestamp();
        mPrevTime = mStartTime;
    }

    @Override
    protected void execute() {
        double currentVelocity = (Math.abs(mDrive.getLeftVelocityNativeUnits()) + Math.abs(mDrive.getRightVelocityNativeUnits())) / Drive.kDriveEncoderPPR * Math.PI * 10;
        double currentTime = Timer.getFPGATimestamp();

        //don't calculate acceleration until we've populated prevTime and prevVelocity
        if (mPrevTime == mStartTime) {
            mPrevTime = currentTime;
            mPrevVelocity = currentVelocity;
            return;
        }

        double acceleration = (currentVelocity - mPrevVelocity) / (currentTime - mPrevTime);

        //ignore accelerations that are too small
        if (acceleration < Util.kEpsilon) {
            mPrevTime = currentTime;
            mPrevVelocity = currentVelocity;
            return;
        }

        mAccelerationData.add(new DriveCharacterization.AccelerationDataPoint(
                currentVelocity, //convert to radians per second
                kPower * 12.0, //convert to volts
                acceleration
        ));

        mCSVWriter.add(mAccelerationData.get(mAccelerationData.size() - 1));

        mPrevTime = currentTime;
        mPrevVelocity = currentVelocity;
    }

    @Override
    protected boolean isFinished() {
        return mTimer.hasPeriodPassed(kTotalTime);
    }

    @Override
    protected void end() {
        mDrive.setOpenLoop(DriveSignal.BRAKE);
        mCSVWriter.flush();
    }

    @Override
    protected void interrupted() {
        this.end();
    }

}