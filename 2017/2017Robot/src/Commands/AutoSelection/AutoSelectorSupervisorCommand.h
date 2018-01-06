#ifndef AutoSelectorSupervisorCommand_H
#define AutoSelectorSupervisorCommand_H

#include "../../CommandBase.h"

class AutoSelectorSupervisorCommand : public CommandBase {
public:
	AutoSelectorSupervisorCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // AutoSelectorSupervisorCommand_H
