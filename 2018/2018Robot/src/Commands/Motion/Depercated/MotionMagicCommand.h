#ifndef MotionMagicCommand_H
#define MotionMagicCommand_H

#include "CommandBase.h"

class MotionMagicCommand : public CommandBase {
public:
	MotionMagicCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // MotionMagicCommand_H
