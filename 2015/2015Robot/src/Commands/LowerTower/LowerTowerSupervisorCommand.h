#ifndef LowerTowerSupervisorCommand_H
#define LowerTowerSupervisorCommand_H

#include "../../CommandBase.h"
#include "WPILib.h"
#include "../../DiasyFilter/DaisyFilter.h"
#include "../../Util/TowerSD.h"

class LowerTowerSupervisorCommand: public CommandBase
{
private:
	Timer *timer;
	float setpoint;
	bool isCalibrated;
	bool isStopped;
	bool bottomPosition;

	void run();
	void cleanUp();

	bool paused;

	bool inPosition;

	DaisyFilter *towerForceVotlageFilter;

	TowerSD *towerSD;

public:
	LowerTowerSupervisorCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
