#ifndef LowerTowerClearPlayerStationCommand_H
#define LowerTowerClearPlayerStationCommand_H

#include "../../CommandBase.h"
#include "WPILib.h"

class LowerTowerClearPlayerStationCommand: public CommandBase
{
public:
	LowerTowerClearPlayerStationCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
