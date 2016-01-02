#ifndef TowerSupervisorCommnad_H
#define TowerSupervisorCommnad_H

#include "../CommandBase.h"
#include "WPILib.h"

class TowerSupervisorCommnad: public CommandBase
{
public:
	TowerSupervisorCommnad();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
