#ifndef TestLowerTowerMoveUpCommand_H
#define TestLowerTowerMoveUpCommand_H

#include "../../CommandBase.h"
#include "WPILib.h"

class TestLowerTowerMoveUpCommand: public CommandBase
{
public:
	TestLowerTowerMoveUpCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
