#ifndef INSDisableCommand_H
#define INSDisableCommand_H

#include "../../CommandBase.h"
#include "WPILib.h"

class INSDisableCommand: public CommandBase
{
public:
	INSDisableCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
