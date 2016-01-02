#ifndef LowerTowerMoveToStackUpCommand_H
#define LowerTowerMoveToStackUpCommand_H

#include "../../CommandBase.h"
#include "WPILib.h"

class LowerTowerMoveToStackUpCommand: public CommandBase
{
public:
	LowerTowerMoveToStackUpCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
