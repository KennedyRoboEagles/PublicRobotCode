#ifndef ElevatorUpCommand_H
#define ElevatorUpCommand_H

#include "CommandBase.h"

class ElevatorUpCommand : public CommandBase {
public:
	ElevatorUpCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // ElevatorUpCommand_H
