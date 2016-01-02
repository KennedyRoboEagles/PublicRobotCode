#ifndef LowerTowerMoveToPickupBinPositionCommand_H
#define LowerTowerMoveToPickupBinPositionCommand_H

#include "../../CommandBase.h"
#include "WPILib.h"

class LowerTowerMoveToPickupBinPositionCommand: public CommandBase
{
public:
	LowerTowerMoveToPickupBinPositionCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
