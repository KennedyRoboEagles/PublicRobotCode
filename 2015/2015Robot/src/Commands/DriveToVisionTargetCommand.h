#ifndef DriveToVisionTargetCommand_H
#define DriveToVisionTargetCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class DriveToVisionTargetCommand: public CommandBase
{
public:
	DriveToVisionTargetCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	enum DriveToVisionTargetState {
		Initializing,
		FindingTarget,
		CenteringTarget,
		DrivingToTarget,
		};
	void UpdateCameraData();
	bool isVisionTargetPresent;
	// X offset of vision target from center of image.  Target to right of center is positive, left is negative.
	int visionTargetXOffsetInPixels;
	int visionTargetYOffsetInPixels;
	int visionTargetArea;
	DriveToVisionTargetState state;

};

#endif
