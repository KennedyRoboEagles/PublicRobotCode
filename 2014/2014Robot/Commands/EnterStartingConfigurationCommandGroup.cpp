#include "EnterStartingConfigurationCommandGroup.h"
//#include "ThrowerEnterStartingConfigurationCommand.h"
#include "TiltIntakeUpCommand.h"
#include "CloseIntakeCommand.h"
#include "ThrowCommand.h"

EnterStartingConfigurationCommandGroup::EnterStartingConfigurationCommandGroup() {
	AddSequential(new ThrowCommand());
	AddSequential(new WaitCommand(0.5));
	AddParallel(new TiltIntakeUpCommand());
	AddParallel(new CloseIntakeCommand());
}

void EnterStartingConfigurationCommandGroup::Initialize() {
	printf("[EnterStartingConfigurationCommandGroup] Initializing\n");
}
void EnterStartingConfigurationCommandGroup::End() {
	printf("[EnterStartingConfigurationCommandGroup] Ending\n");
}
void EnterStartingConfigurationCommandGroup::Interrupted() {
	printf("[EnterStartingConfigurationCommandGroup] Interrupted\n");
}
