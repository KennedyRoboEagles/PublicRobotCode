package com.kennedyrobotics.subsystems;

import com.kennedyrobotics.RobotMap;
import com.ni.vision.VisionException;

import edu.wpi.first.wpilibj.Servo;
import edu.wpi.first.wpilibj.command.Subsystem;
import edu.wpi.first.wpilibj.vision.USBCamera;
import edu.wpi.first.wpilibj.CameraServer;
import edu.wpi.first.wpilibj.DriverStation;

/**
 *
 */
public class CameraSubsystem extends Subsystem {

	public static final double CAMERA_RASIE_ANGLE = 0.92;
	public static final double CAMERA_LOWER_ANGLE = 0.68;
	public static final int CAMERA_QUALITY = 30;
	public static final int CAMERA_FRAME_RATE = 15;

	public static final String CAMERA_NAME = "cam4";

	private final Servo cameraMotor = new Servo(RobotMap.CAMERA_TILT_MOTOR);

	public CameraSubsystem(boolean enableAutomaticCapture) {
		if (enableAutomaticCapture)
		{
			
			try {
				USBCamera camera = new USBCamera(CAMERA_NAME);
				camera.setExposureAuto();
				camera.setSize(320, 240);
				camera.setFPS(CAMERA_FRAME_RATE);
				camera.openCamera();
				
				CameraServer server = CameraServer.getInstance();
				server.setQuality(CAMERA_QUALITY);
				server.startAutomaticCapture(camera);
			} catch(VisionException e) {
				DriverStation.reportError("Camera: " + e, true);
			}
		}
	}

	public void initDefaultCommand() {
		// Set the default command for a subsystem here.
		// setDefaultCommand(new MySpecialCommand());
		cameraMotor.set(CAMERA_LOWER_ANGLE);
	}

	public void raiseCamera() {
		cameraMotor.set(CAMERA_RASIE_ANGLE);
	}

	public void lowerCamera() {
		cameraMotor.set(CAMERA_LOWER_ANGLE);
	}

	public void stop() {
		cameraMotor.set(CAMERA_LOWER_ANGLE);
	}
}
