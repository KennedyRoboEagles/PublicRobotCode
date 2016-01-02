#ifndef TestLowerCarManipulatorMoveInwardCommand_H
#define TestLowerCarManipulatorMoveInwardCommand_H

#include "../../CommandBase.h"
#include "WPILib.h"

class TestLowerCarManipulatorMoveInwardCommand: public CommandBase
{
public:
	TestLowerCarManipulatorMoveInwardCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
