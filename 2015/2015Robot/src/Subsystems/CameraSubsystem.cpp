#include "CameraSubsystem.h"
#include "../RobotMap.h"
#include "../Commands/Camera/CameraTestCommand.h"

CameraSubsystem::CameraSubsystem() : Subsystem("CameraSubsystem")
{
	this->cameraServo = new Servo(CAMERA_TILT_SERVO);
	this->ledRing = new Solenoid(CAMERA_LED_RING_CHANNEL);
}

void CameraSubsystem::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
	//SetDefaultCommand(new CameraTestCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void CameraSubsystem::SetLedRingState(bool state) {
	this->ledRing->Set(state);
}


/*
 * 0 here represents forward, and 45 represents a 45 degree angle (which is the max based on how we mounted things.
 */
void CameraSubsystem::SetCameraTilt(double position)
{
	// Map 0-45 input to .65 - 1 value

	int range = 1 - .65;
	int offset = position / 45;
	this->cameraServo->Set(.65 + (range * offset));
}

/*
 * NOTE: Position is between -1 and 1
 */
void CameraSubsystem::SetCameraTiltRawServo(float position) {
	this->cameraServo->Set(position);
}
