#ifndef INSEnableCommand_H
#define INSEnableCommand_H

#include "../../CommandBase.h"
#include "WPILib.h"

class INSEnableCommand: public CommandBase
{
public:
	INSEnableCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
