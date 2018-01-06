#ifndef ClimberIndexCommand_H
#define ClimberIndexCommand_H

#include "../CommandBase.h"
#include "../OI.h"

class ClimberIndexCommand : public CommandBase {
public:
	ClimberIndexCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // ClimberCommand_H
