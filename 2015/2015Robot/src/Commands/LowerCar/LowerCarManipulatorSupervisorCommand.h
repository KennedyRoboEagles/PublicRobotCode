#ifndef GrabberSupervisorCommand_H
#define GrabberSupervisorCommand_H

#include "../../CommandBase.h"
#include "WPILib.h"

class LowerCarManipulatorSupervisorCommand: public CommandBase
{
public:
	LowerCarManipulatorSupervisorCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
