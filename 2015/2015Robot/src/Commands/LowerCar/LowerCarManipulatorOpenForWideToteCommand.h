#ifndef LowerCarManipulatorOpenForWideToteCommand_H
#define LowerCarManipulatorOpenForWideToteCommand_H

#include "../../CommandBase.h"
#include "WPILib.h"

class LowerCarManipulatorOpenForWideToteCommand: public CommandBase
{
public:
	LowerCarManipulatorOpenForWideToteCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
