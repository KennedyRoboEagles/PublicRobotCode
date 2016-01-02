#ifndef CameraTestCommand_H
#define CameraTestCommand_H

#include "../../CommandBase.h"
#include "WPILib.h"

class CameraTestCommand: public CommandBase
{
public:
	CameraTestCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
