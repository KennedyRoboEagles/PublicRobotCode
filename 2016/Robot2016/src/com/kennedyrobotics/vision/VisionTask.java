package com.kennedyrobotics.vision;

import java.util.Arrays;

import com.kennedyrobotics.subsystems.CameraSubsystem;
import com.ni.vision.NIVision;
import com.ni.vision.NIVision.IMAQdxCameraControlMode;
import com.ni.vision.NIVision.Image;
import com.ni.vision.NIVision.ImageType;
import com.ni.vision.VisionException;

import edu.wpi.first.wpilibj.CameraServer;
import edu.wpi.first.wpilibj.DriverStation;
import edu.wpi.first.wpilibj.Timer;

/**
 * Runs {@link Vision2016} in a separate thread.
 * @author Ryan
 *
 */
public class VisionTask implements Runnable {
	
	private static String ATTR_VIDEO_MODE = "AcquisitionAttributes::VideoMode";
	private static String ATTR_WB_MODE = "CameraAttributes::WhiteBalance::Mode";
	private static String ATTR_WB_VALUE = "CameraAttributes::WhiteBalance::Value";
	private static String ATTR_EX_MODE = "CameraAttributes::Exposure::Mode";
	private static String ATTR_EX_VALUE = "CameraAttributes::Exposure::Value";
	private static String ATTR_BR_MODE = "CameraAttributes::Brightness::Mode";
	private static String ATTR_BR_VALUE = "CameraAttributes::Brightness::Value";
	
	private final Vision2016 vision;
	private final Thread thread;
	private volatile boolean process = false;
	private volatile boolean running = false;
	private volatile double lastProcess = Timer.getFPGATimestamp();
	
	public double getLastProcessTimeStamp() {
		return lastProcess;
	}

	public VisionTask() {
		vision = new Vision2016();
		thread = new Thread(this, "VisionTask");
	}
	
	public double getTargetDistance() {
		return vision.getTargetDistance();
	}
	
	public double getTargetcomX() {
		return vision.getTargetComX();
	}
	
	public boolean isTargetPresent() {
		return vision.isTargetPresent();
	}
	
	/**
	 * Starts the image processing thread 
	 */
	public void start() {
		running = true;
		thread.start();
	}
	
	/**
	 * Stops the image processing thread
	 */
	public void stop() {
		running = false;
	}
	
	/**
	 * Enables processing in the thread 
	 */
	public void enableProcessing() {
		process = true;
	}
	
	/**
	 * Disables processing in the thread
	 */
	public void disableProcessing() {
		process = false;
	}
	
	/**
	 * Whether the thread is currently processing images
	 * @return
	 */
	public boolean isProcessing() {
		return process;
	}
	
	@Override
	public void run() {
		try {
			//Start Camera Session
			int session = NIVision.IMAQdxOpenCamera(CameraSubsystem.CAMERA_NAME, IMAQdxCameraControlMode.CameraControlModeController);
	
			//Set the resolution of the camera to 640x480
			NIVision.IMAQdxSetAttributeString(session, ATTR_VIDEO_MODE, "640x480 YUY2 30.00fps");

	        System.out.println("Exposure Max: " + NIVision.IMAQdxGetAttributeMaximumF64(session, ATTR_EX_VALUE) 
    			+ " Min: " + NIVision.IMAQdxGetAttributeMinimumF64(session, ATTR_EX_VALUE));

			//Set the exposure of the camera
			NIVision.IMAQdxSetAttributeString(session, ATTR_EX_MODE, "Manual");
	        NIVision.IMAQdxSetAttributeF64(session, ATTR_EX_VALUE, 10.6);//Note: this value is kind of finicky  

	        System.out.println("Brightness Max: " + NIVision.IMAQdxGetAttributeMaximumF64(session, ATTR_BR_VALUE) 
    			+ " Min: " + NIVision.IMAQdxGetAttributeMinimumF64(session, ATTR_BR_VALUE));
	        
	        
	        //Set the brightness
	        NIVision.IMAQdxSetAttributeString(session, ATTR_BR_MODE, "Manual");
	        NIVision.IMAQdxSetAttributeI64(session, ATTR_BR_VALUE, 65);

	        System.out.println("Saturation Max: " + NIVision.IMAQdxGetAttributeMaximumF64(session, "CameraAttributes::Saturation::Value") 
    			+ " Min: " + NIVision.IMAQdxGetAttributeMinimumF64(session,  "CameraAttributes::Saturation::Value"));
	        
	        //Set the camera saturation
	        NIVision.IMAQdxSetAttributeString(session, "CameraAttributes::Saturation::Mode", "Manual");
	        NIVision.IMAQdxSetAttributeI64(session, "CameraAttributes::Saturation::Value", 200);

	        System.out.println("White Balance Max: " + NIVision.IMAQdxGetAttributeMaximumI64(session, ATTR_WB_VALUE) 
    			+ " Min: " + NIVision.IMAQdxGetAttributeMinimumI64(session, ATTR_WB_VALUE));
	        
	        //Set the white balance
	        NIVision.IMAQdxSetAttributeString(session, ATTR_WB_MODE, "Manual");
	        NIVision.IMAQdxSetAttributeI64(session, ATTR_WB_VALUE, 4000);
	        
	        //Start Acquisition
			NIVision.IMAQdxConfigureGrab(session);
			NIVision.IMAQdxStartAcquisition(session);

			Image frame = NIVision.imaqCreateImage(ImageType.IMAGE_RGB, 0);
			//Preferences pref = Preferences.getInstance();
			//initPref(pref);
			
			//Initialize Image processing loop
			vision.init();
			while(running) {
				try {
					//Get new frame from camera
					NIVision.IMAQdxGrab(session, frame, 1);
					
					if(process) {
						//We are allowed to process images
						
						//Update Vision config from preferences
						//updateConfig(vision.getConfig(), pref);
						
						//Process frame
						vision.process(frame);
						lastProcess = Timer.getFPGATimestamp();
						
						//Draw results on the frame
						vision.draw(frame);
					}
					//Publish the frame to the DS/SmartDashboard
					CameraServer.getInstance().setImage(frame);

					Timer.delay(0.1);
				} catch(VisionException e) {
					DriverStation.reportError("Could not process image: " + e.getMessage() + Arrays.toString(e.getStackTrace()), false);
				}
			}
		} catch(Exception e) {
			DriverStation.reportError("Vision Task failed: " + e.getMessage() + " | " + Arrays.toString(e.getStackTrace()), false);
			e.printStackTrace();
		}
	}
	
//	/**
//	 * Update {@link Vision2016}'s configuration from WPI's {@link Preferences}
//	 * @param config The config to update
//	 * @param pref The prefenese to update from
//	 */
//	private static void updateConfig(Config config, Preferences pref) {
//		config.setRageMin(
//			pref.getInt("Min H", Config.DEFAULT_MIN_H),
//			pref.getInt("Min S", Config.DEFAULT_MIN_S),
//			pref.getInt("Min V", Config.DEFAULT_MIN_V)
//			);
//		
//		config.setRageMax(
//			pref.getInt("Max H", Config.DEFAULT_MAX_H),
//			pref.getInt("Max S", Config.DEFAULT_MAX_S),
//			pref.getInt("Max V", Config.DEFAULT_MAX_V)
//			);
//		
//		config.areaScoreMin = pref.getDouble("Area Score", Config.DEFAULT_AREA_SCORE);
//		config.aspectRatioScoreMin = pref.getDouble("Aspect Score", Config.DEFAULT_ASPECT_SCORE);
//	}
//	
//	/**
//	 * Initializes the {@link Preferences}
//	 * @param pref
//	 */
//	private static void initPref(Preferences pref) {
//		if(!pref.containsKey("Min H")) pref.putInt("Min H", Config.DEFAULT_MIN_H);
//		if(!pref.containsKey("Min S")) pref.putInt("Min S", Config.DEFAULT_MIN_S);
//		if(!pref.containsKey("Min V")) pref.putInt("Min V", Config.DEFAULT_MIN_V);
//		if(!pref.containsKey("Max H")) pref.putInt("Max H", Config.DEFAULT_MAX_H);
//		if(!pref.containsKey("Max S")) pref.putInt("Max S", Config.DEFAULT_MAX_S);
//		if(!pref.containsKey("Max V")) pref.putInt("Max V", Config.DEFAULT_MAX_V);
//		
//		if(!pref.containsKey("Area Score")) pref.putDouble("Area Score", Config.DEFAULT_AREA_SCORE);
//		if(!pref.containsKey("Aspect Score")) pref.putDouble("Aspect Score", Config.DEFAULT_ASPECT_SCORE);
//
//	}
}
