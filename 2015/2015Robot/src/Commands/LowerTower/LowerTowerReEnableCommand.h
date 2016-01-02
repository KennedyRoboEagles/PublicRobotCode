#ifndef LowerTowerReEnableCommand_H
#define LowerTowerReEnableCommand_H

#include "../../CommandBase.h"
#include "WPILib.h"

class LowerTowerReEnableCommand: public CommandBase
{
public:
	LowerTowerReEnableCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
