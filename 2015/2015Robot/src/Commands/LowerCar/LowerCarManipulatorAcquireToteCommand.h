#ifndef LowerCarManipulatorAcquireToteCommand_H
#define LowerCarManipulatorAcquireToteCommand_H

#include "../../CommandBase.h"
#include "WPILib.h"

class LowerCarManipulatorAcquireToteCommand: public CommandBase
{
public:
	LowerCarManipulatorAcquireToteCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
