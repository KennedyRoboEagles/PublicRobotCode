#ifndef LowerCarManipulatorCloseForBinCommand_H
#define LowerCarManipulatorCloseForBinCommand_H

#include "../../CommandBase.h"
#include "WPILib.h"

class LowerCarManipulatorCloseForBinCommand: public CommandBase
{
public:
	LowerCarManipulatorCloseForBinCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
