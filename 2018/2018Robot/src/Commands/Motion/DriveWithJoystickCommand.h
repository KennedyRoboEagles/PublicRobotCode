#ifndef DriveCommand_H
#define DriveCommand_H

#include "CommandBase.h"
#include "Util/JoystickResponseCurve.h"
#include "PIDController.h"

class DriveWithJoystickCommand : public CommandBase {
public:
	DriveWithJoystickCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	bool fodLast_;
	bool fod_;
	JoystickResponseCurve* xCurve;
	JoystickResponseCurve* yCurve;
	JoystickResponseCurve* zCurve;

	frc::PIDController* angularController_;
	double heading_;
};

#endif  // DriveCommand_H
