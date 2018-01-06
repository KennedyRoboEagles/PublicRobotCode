#ifndef JerkForwardCommand_H
#define JerkForwardCommand_H

#include "../CommandBase.h"

class JerkForwardCommand : public CommandBase {
public:
	JerkForwardCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // JerkForwardCommand_H
