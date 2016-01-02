#ifndef CascadedPIDDriceDistanceCommand_H
#define CascadedPIDDriceDistanceCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class CascadedPIDDriveDistanceCommand: public CommandBase, PIDOutput
{
private:
	PIDController *controller0;
	PIDController *controller1;
	float distance;

	void cleanUp();
public:
	CascadedPIDDriveDistanceCommand(float distance);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

	void PIDWrite(float output);
};

#endif
