#ifndef SharonCommand_H
#define SharonCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class SharonCommand: public CommandBase
{
public:
	SharonCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
