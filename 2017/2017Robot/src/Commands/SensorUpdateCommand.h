#ifndef SensorUpdateCommand_H
#define SensorUpdateCommand_H

#include "../Subsystems/SensorSubsystem.h"
#include "../CommandBase.h"

class SensorUpdateCommand : public CommandBase {
public:
	SensorUpdateCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // SensorUpdateCommand_H
