#ifndef CameraForwardCommand_H
#define CameraForwardCommand_H

#include "../../CommandBase.h"
#include "WPILib.h"

class CameraForwardCommand: public CommandBase
{
public:
	CameraForwardCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
