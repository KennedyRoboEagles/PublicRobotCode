#ifndef RumbleController_H
#define RumbleController_H

#include "../CommandBase.h"

class RumbleControllerCommand : public CommandBase {
public:
	RumbleControllerCommand(double timeout);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // RumbleController_H
