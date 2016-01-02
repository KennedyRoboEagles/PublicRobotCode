#ifndef RESETSWAPCOMMANDCOMMAND_H
#define RESETSWAPCOMMANDCOMMAND_H

#include "../CommandBase.h"
#include "SwapCommandCommand.h"

/**
 *
 *
 * @author nowireless
 */
class ResetSwapCommandCommand: public CommandBase {
private:
	SwapCommandCommand *swapCommand;
public:
	ResetSwapCommandCommand(SwapCommandCommand *swapCommand);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
