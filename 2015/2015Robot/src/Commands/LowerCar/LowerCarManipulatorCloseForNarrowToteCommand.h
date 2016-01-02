#ifndef LowerCarManipulatorCloseForNarrowToteCommand_H
#define LowerCarManipulatorCloseForNarrowToteCommand_H

#include "../../CommandBase.h"
#include "WPILib.h"

class LowerCarManipulatorCloseForNarrowToteCommand: public CommandBase
{
public:
	LowerCarManipulatorCloseForNarrowToteCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
