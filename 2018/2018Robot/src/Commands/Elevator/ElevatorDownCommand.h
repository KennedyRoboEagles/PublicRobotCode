#ifndef ElevatorDownCommand_H
#define ElevatorDownCommand_H

#include "CommandBase.h"

class ElevatorDownCommand : public CommandBase {
public:
	ElevatorDownCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // ElevatorDownCommand_H
