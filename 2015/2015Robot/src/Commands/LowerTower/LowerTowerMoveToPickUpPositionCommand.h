#ifndef LowerTowerMoveToPickUpPositionCommand_H
#define LowerTowerMoveToPickUpPositionCommand_H

#include "../../CommandBase.h"
#include "WPILib.h"

class LowerTowerMoveToPickUpPositionCommand: public CommandBase
{
public:
	LowerTowerMoveToPickUpPositionCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
