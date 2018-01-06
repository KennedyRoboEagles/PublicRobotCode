#ifndef SelectNextAutoCommand_H
#define SelectNextAutoCommand_H

#include "../../CommandBase.h"

class SelectNextAutoCommand : public CommandBase {
public:
	SelectNextAutoCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // SelectNextAutoCommand_H
