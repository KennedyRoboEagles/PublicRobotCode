#ifndef LowerTowerLowerToteCommand_H
#define LowerTowerLowerToteCommand_H

#include "../../CommandBase.h"
#include "WPILib.h"

class LowerTowerLowerToteCommand: public CommandBase
{
public:
	LowerTowerLowerToteCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
