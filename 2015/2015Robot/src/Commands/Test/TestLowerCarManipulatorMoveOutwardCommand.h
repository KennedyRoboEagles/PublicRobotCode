#ifndef TestLowerCarManipulatorMoveOutwardCommand_H
#define TestLowerCarManipulatorMoveOutwardCommand_H

#include "../../CommandBase.h"
#include "WPILib.h"

class TestLowerCarManipulatorMoveOutwardCommand: public CommandBase
{
public:
	TestLowerCarManipulatorMoveOutwardCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
