#ifndef TurnCommand_H
#define TurnCommand_H

#include "../CommandBase.h"

class TurnCommand : public CommandBase {
public:
	TurnCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // TurnCommand_H
