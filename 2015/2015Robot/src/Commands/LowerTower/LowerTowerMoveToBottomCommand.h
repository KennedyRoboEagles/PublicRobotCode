#ifndef LowerTowerMoveToBottomCommand_H
#define LowerTowerMoveToBottomCommand_H

#include "../../CommandBase.h"
#include "WPILib.h"

class LowerTowerMoveToBottomCommand: public CommandBase
{
public:
	LowerTowerMoveToBottomCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
