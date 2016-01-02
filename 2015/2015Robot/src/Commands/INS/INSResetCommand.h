#ifndef INSResetCommand_H
#define INSResetCommand_H

#include "../../CommandBase.h"
#include "WPILib.h"

class INSResetCommand: public CommandBase
{
public:
	INSResetCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
