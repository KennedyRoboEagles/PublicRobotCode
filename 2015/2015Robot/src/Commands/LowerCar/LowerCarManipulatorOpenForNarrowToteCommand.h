#ifndef LowerCarManipulatorOpenForNarrowToteCommand_H
#define LowerCarManipulatorOpenForNarrowToteCommand_H

#include "../../CommandBase.h"
#include "WPILib.h"

class LowerCarManipulatorOpenForNarrowToteCommand: public CommandBase
{
public:
	LowerCarManipulatorOpenForNarrowToteCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
