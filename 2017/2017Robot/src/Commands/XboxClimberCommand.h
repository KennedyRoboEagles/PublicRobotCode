#ifndef XboxClimberCommand_H
#define XboxClimberCommand_H

#include "../CommandBase.h"

class XboxClimberCommand : public CommandBase {
public:
	XboxClimberCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // XboxClimberCommand_H
