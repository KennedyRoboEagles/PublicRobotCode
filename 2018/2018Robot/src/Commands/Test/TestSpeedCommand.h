#ifndef TestSpeedCommand_H
#define TestSpeedCommand_H

#include "CommandBase.h"

class TestSpeedCommand : public CommandBase {
public:
	TestSpeedCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // TestSpeedCommand_H
