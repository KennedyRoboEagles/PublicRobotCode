#ifndef ElevatorMoveToPositionCommand_H
#define ElevatorMoveToPositionCommand_H

#include "CommandBase.h"

class ElevatorMoveToPositionCommand : public CommandBase {
public:
	ElevatorMoveToPositionCommand(double height);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	double goal_;
	bool done_;
};

#endif  // ElevatorMoveToPositionCommand_H
