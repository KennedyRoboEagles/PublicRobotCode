#ifndef INSDriveStraightCommand_H
#define INSDriveStraightCommand_H

#include "../../CommandBase.h"
#include "WPILib.h"

class INSDriveStraightCommand: public CommandBase
{
private:
	float distance;
	float targetAngle;
	float xInit;
	float yInit;
public:
	INSDriveStraightCommand(float distance);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
