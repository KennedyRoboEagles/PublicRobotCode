#ifndef ResetChassisEncodersCommand_H
#define ResetChassisEncodersCommand_H

#include "../CommandBase.h"

class ResetChassisEncodersCommand : public CommandBase {
public:
	ResetChassisEncodersCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // ResetChassisEncodersCommand_H
