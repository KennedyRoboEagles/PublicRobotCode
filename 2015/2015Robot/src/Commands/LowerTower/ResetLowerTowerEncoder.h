#ifndef ResetLowerTowerEncoder_H
#define ResetLowerTowerEncoder_H

#include "../../CommandBase.h"
#include "WPILib.h"

class ResetLowerTowerEncoder: public CommandBase
{
public:
	ResetLowerTowerEncoder();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
