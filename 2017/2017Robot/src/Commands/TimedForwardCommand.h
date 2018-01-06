#ifndef TimedForwardCommand_H
#define TimedForwardCommand_H

#include "../CommandBase.h"

class TimedForwardCommand : public CommandBase {
private:
	Timer *timer;
public:
	TimedForwardCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // TimedForwardCommand_H
