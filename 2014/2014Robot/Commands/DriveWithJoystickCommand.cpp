#include "DriveWithJoystickCommand.h"

#define DRIVE_JOYSTICK_X_SCALE (0.75)
#define DRIVE_JOYSTICK_Y_SCALE (0.75)

DriveWithJoystickCommand::DriveWithJoystickCommand() : CommandBase("DriveWithJoystickCommand") {
	Requires(chassis);
}

// Called just before this Command runs the first time
void DriveWithJoystickCommand::Initialize() {
	chassis->Stop();
}

// Called repeatedly when this Command is scheduled to run
void DriveWithJoystickCommand::Execute() {
	float x = oi->GetDriverJoystick()->GetX();
	float y = oi->GetDriverJoystick()->GetY();
			
	if(this->oi->GetDriverJoystick()->GetRawButton(BUTTON_DRIVER_INVERT_JOYSTICK)) {
		y = -y;
	}
	if(sensorSubsystem->GetIntakeBallTwoSensor() && !oi->GetDriverJoystick()->GetRawButton(BUTTON_PREVENT_AUTO_BALL_INTAKE)
			&& !oi->GetDriverTwoJoystick()->GetRawButton(BUTTON_DRIVER_TWO_DISABLE)) {
		x = DRIVE_JOYSTICK_X_SCALE * x;
		y = DRIVE_JOYSTICK_Y_SCALE * y; 
	}
	
	chassis->GetRobotDrive()->ArcadeDrive(y, x);
	
#ifdef DEBUG_PRINT
	printf("[DriveWithJoystick] X:%f Y:%f\n", oi->GetDriverJoystick()->GetX(), oi->GetDriverJoystick()->GetY());
#endif	
}

// Make this return true when this Command no longer needs to run execute()
bool DriveWithJoystickCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void DriveWithJoystickCommand::End() {
	chassis->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveWithJoystickCommand::Interrupted() {
	chassis->Stop();
}
