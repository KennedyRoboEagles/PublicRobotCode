#ifndef TestLowerTowerMoveDownCommand_H
#define TestLowerTowerMoveDownCommand_H

#include "../../CommandBase.h"
#include "WPILib.h"

class TestLowerTowerMoveDownCommand: public CommandBase
{
public:
	TestLowerTowerMoveDownCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
