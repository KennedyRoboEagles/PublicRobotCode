#ifndef SelectPreviousCommand_H
#define SelectPreviousCommand_H

#include "../../CommandBase.h"

class SelectPreviousAutoCommand : public CommandBase {
public:
	SelectPreviousAutoCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // SelectPreviousCommand_H
