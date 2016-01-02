#ifndef VISIONSUBSYSTEM_H
#define VISIONSUBSYSTEM_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author nowireless
 */
class VisionSubsystem: public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	bool isHotTargetPresenet;
public:
	VisionSubsystem();
	void InitDefaultCommand();
	void DetectHotGoal();
	bool IsHotTargetPressent();
	void WriteCameraImage();
	void Reset();
	
};

#endif
