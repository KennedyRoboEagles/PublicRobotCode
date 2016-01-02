#ifndef LowerTowerMoveToSecondToteAqusitionPositionCommand_H
#define LowerTowerMoveToSecondToteAqusitionPositionCommand_H

#include "../../CommandBase.h"
#include "WPILib.h"

class LowerTowerMoveToSecondToteAqusitionPositionCommand: public CommandBase
{
public:
	LowerTowerMoveToSecondToteAqusitionPositionCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
