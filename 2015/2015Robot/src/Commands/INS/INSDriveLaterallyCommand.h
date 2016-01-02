#ifndef INSDriveLaterallyCommand_H
#define INSDriveLaterallyCommand_H

#include "../../CommandBase.h"
#include "WPILib.h"

class INSDriveLaterallyCommand: public CommandBase
{
private:
	float distance;
	float targetAngle;
	float xInit;
	float yInit;
public:
	INSDriveLaterallyCommand(float distance);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
