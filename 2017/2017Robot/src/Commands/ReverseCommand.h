#ifndef ReverseCommand_H
#define ReverseCommand_H

#include "../CommandBase.h"

class ReverseCommand : public CommandBase {
public:
	ReverseCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
};

#endif  // ReverseCommand_H
