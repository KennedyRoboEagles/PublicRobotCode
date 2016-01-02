#ifndef LowerTowerMoveToBottomToteMovementPositionCommand_H
#define LowerTowerMoveToBottomToteMovementPositionCommand_H

#include "../../CommandBase.h"
#include "WPILib.h"

class LowerTowerMoveToBottomToteMovementPositionCommand: public CommandBase
{
public:
	LowerTowerMoveToBottomToteMovementPositionCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
