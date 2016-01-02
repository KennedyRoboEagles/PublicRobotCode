#ifndef SensorUpdateCommand_H
#define SensorUpdateCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class SensorUpdateCommand: public CommandBase
{
private:
	bool imuInit;
public:
	SensorUpdateCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
