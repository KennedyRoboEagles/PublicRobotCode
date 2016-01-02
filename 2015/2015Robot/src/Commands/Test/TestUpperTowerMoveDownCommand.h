#ifndef TestUpperTowerMoveDownCommand_H
#define TestUpperTowerMoveDownCommand_H

#include "../../CommandBase.h"
#include "WPILib.h"

class TestUpperTowerMoveDownCommand: public CommandBase
{
public:
	TestUpperTowerMoveDownCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
