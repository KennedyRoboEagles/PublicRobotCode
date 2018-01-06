#ifndef ReverseDriveCommand_H
#define ReverseDriveCommand_H

#include "../CommandBase.h"
#include "Subsystems/Chassis.h"

class ReverseDriveCommand : public CommandBase {
public:
	ReverseDriveCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // ReverseDriveCommand_H
