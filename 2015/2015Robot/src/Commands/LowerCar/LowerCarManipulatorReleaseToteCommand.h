#ifndef LowerCarManipulatorReleaseToteCommand_H
#define LowerCarManipulatorReleaseToteCommand_H

#include "../../CommandBase.h"
#include "WPILib.h"

class LowerCarManipulatorReleaseToteCommand: public CommandBase
{
public:
	LowerCarManipulatorReleaseToteCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
