#ifndef ResetIMU_H
#define ResetIMU_H

#include "../CommandBase.h"

class ResetIMU : public CommandBase {
public:
	ResetIMU();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // ResetIMU_H
