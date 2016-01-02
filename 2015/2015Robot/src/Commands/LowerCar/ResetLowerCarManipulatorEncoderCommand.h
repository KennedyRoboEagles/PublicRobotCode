#ifndef ResetLowerCarManipulatorEncoderCommand_H
#define ResetLowerCarManipulatorEncoderCommand_H

#include "../../CommandBase.h"
#include "WPILib.h"

class ResetLowerCarManipulatorEncoderCommand: public CommandBase
{
public:
	ResetLowerCarManipulatorEncoderCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
