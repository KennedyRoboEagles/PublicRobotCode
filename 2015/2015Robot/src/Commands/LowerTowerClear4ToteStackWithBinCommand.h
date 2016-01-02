#ifndef LowerTowerClear4ToteStackWithBinCommand_H
#define LowerTowerClear4ToteStackWithBinCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class LowerTowerClear4ToteStackWithBinCommand: public CommandBase
{
public:
	LowerTowerClear4ToteStackWithBinCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
