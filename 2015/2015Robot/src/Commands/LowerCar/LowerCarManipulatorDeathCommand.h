#ifndef LowerCarManipulatorDeathCommand_H
#define LowerCarManipulatorDeathCommand_H

#include "../../CommandBase.h"
#include "WPILib.h"

class LowerCarManipulatorDeathCommand: public CommandBase
{
private:
	Timer *timer;
	bool oppening;
	bool encoderCal;
public:
	LowerCarManipulatorDeathCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
