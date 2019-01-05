#ifndef ZeroYawCommand_H
#define ZeroYawCommand_H

#include "CommandBase.h"

class ZeroYawCommand : public CommandBase {
public:
	ZeroYawCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // ZeroYawCommand_H
