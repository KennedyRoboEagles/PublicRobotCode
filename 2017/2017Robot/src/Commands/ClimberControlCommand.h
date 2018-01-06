#ifndef ClimberCommand_H
#define ClimberCommand_H

#include "../CommandBase.h"
#include "../OI.h"

class ClimberControlCommand : public CommandBase {
private:
	frc::Joystick* stick;
public:
	ClimberControlCommand(frc::Joystick* stick, bool requireChassis);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // ClimberCommand_H
