#ifndef TestUpperTowerMoveUpCommand_H
#define TestUpperTowerMoveUpCommand_H

#include "../../CommandBase.h"
#include "WPILib.h"

class TestUpperTowerMoveUpCommand: public CommandBase
{
public:
	TestUpperTowerMoveUpCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
