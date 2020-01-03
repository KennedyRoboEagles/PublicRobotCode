/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

package frc.robot;

import java.util.Arrays;

import com.kennedyrobotics.RobotFactory;
import com.kennedyrobotics.charting.SwerveCharter;
import com.kennedyrobotics.subsystem.SubsystemManager;
import frc.robot.subsystems.Swerve;
import com.team254.lib.auto.AutoModeExecutor;

import com.team254.lib.loops.Looper;
import edu.wpi.first.wpilibj.TimedRobot;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;
import frc.robot.auto.AutoModeBase2019;
import frc.robot.auto.SmartDashboardInteractions;
import frc.robot.auto.modes.CloseFarBallMode;
import frc.robot.auto.modes.CloseMidShipMode;
import frc.robot.loops.QuinticPathTransmitter;
import frc.robot.loops.RobotStateEstimator;
import frc.robot.trajectory.TrajectoryGenerator;

/**
 * The VM is configured to automatically run this class, and to call the
 * functions corresponding to each mode, as described in the IterativeRobot
 * documentation. If you change the name of this class or the package after
 * creating this project, you must also update the build.properties file in the
 * project.
 */
public class Robot1323 extends TimedRobot {
	private Swerve swerve;
	private SubsystemManager subsystems;

	private Looper enabledLooper = new Looper();
	private Looper disabledLooper = new Looper();

	private RobotState robotState;

	private AutoModeExecutor autoModeExecuter = null;
	private QuinticPathTransmitter qTransmitter;
	private TrajectoryGenerator generator;
//    private SmartDashboardInteractions smartDashboardInteractions;



	@Override
	public void robotInit() {
		RobotFactory factory = RobotFactory.initialize("sim");
		swerve = new Swerve(factory);
		Swerve.setInstance(swerve);

		robotState = RobotState.getInstance();
		qTransmitter = QuinticPathTransmitter.getInstance();
		generator = TrajectoryGenerator.getInstance();
//        smartDashboardInteractions = new SmartDashboardInteractions();

		subsystems = new SubsystemManager(
				Arrays.asList(swerve)
		);

		enabledLooper.register(RobotStateEstimator.getInstance());
		enabledLooper.register(QuinticPathTransmitter.getInstance());

		disabledLooper.register(RobotStateEstimator.getInstance());
		disabledLooper.register(QuinticPathTransmitter.getInstance());


		subsystems.registerEnabledLoops(enabledLooper);
		subsystems.registerDisabledLoops(disabledLooper);

		swerve.zeroSensors();

		robotState.feignVisionTargets();
//		swerve.startTracking(Constants.kDiskTargetHeight, new Translation2d(-6.0, 0.0), true, new Rotation2d());
		swerve.stop();

		generator.generateTrajectories();

		AutoModeBase2019 auto = new CloseFarBallMode(true);
		qTransmitter.addPaths(auto.getPaths());
		System.out.println("Total path time: " + qTransmitter.getTotalPathTime(auto.getPaths()));

		new SwerveCharter(swerve);
	}

	@Override
	public void robotPeriodic() {

	}

	@Override
	public void autonomousInit() {
		if (autoModeExecuter != null)
			autoModeExecuter.stop();

		// Initialize swerve for auto
		swerve.zeroSensors();
		swerve.setNominalDriveOutput(0.0);
		swerve.requireModuleConfiguration();

		disabledLooper.stop();
		enabledLooper.start();

		SmartDashboard.putBoolean("Auto", true);

		// Always assume Red Alliance
		robotState.setAlliance(SmartDashboardInteractions.Alliance.RED);
//        robotState.setAlliance(smartDashboardInteractions.getSelectedAlliance());
		swerve.setCarpetDirection(robotState.onStandardCarpet());

		autoModeExecuter = new AutoModeExecutor();
//        autoModeExecuter.setAutoMode(smartDashboardInteractions.getSelectedAutoMode());
		autoModeExecuter.setAutoMode(new CloseMidShipMode(true));
		autoModeExecuter.start();
	}

	@Override
	public void autonomousPeriodic() {
		allPeriodic();
		//Pigeon.getInstance().outputToSmartDashboard();
//        SmartDashboard.putBoolean("Enabled", ds.isEnabled());
//        SmartDashboard.putNumber("Match time", ds.getMatchTime());

		System.out.println("Remaining progress: " + swerve.getRemainingProgress());
	}

	@Override
	public void disabledInit() {
		if (autoModeExecuter != null)
			autoModeExecuter.stop();
		enabledLooper.stop();
		subsystems.stop();
		disabledLooper.start();
	}

	@Override
	public void disabledPeriodic() {
		allPeriodic();
//        smartDashboardInteractions.output();
	}

	public void allPeriodic() {
		subsystems.outputToSmartDashboard();
		robotState.outputToSmartDashboard();
		enabledLooper.outputToSmartDashboard();
		//Pigeon.getInstance().outputToSmartDashboard();
//        SmartDashboard.putBoolean("Enabled", ds.isEnabled());
//        SmartDashboard.putNumber("Match time", ds.getMatchTime());
	}
}
