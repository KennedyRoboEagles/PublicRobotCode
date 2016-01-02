#include "ExitStartingConfigurationCommandGroup.h"
#include "OpenIntakeCommand.h"
#include "TiltIntakeDownCommand.h"
#include "RetractCommand.h"

ExitStartingConfigurationCommandGroup::ExitStartingConfigurationCommandGroup() {
	AddParallel(new OpenIntakeCommand());
	AddParallel(new TiltIntakeDownCommand());
	AddSequential(new RetractCommand());
}

void ExitStartingConfigurationCommandGroup::Initialize() {
	printf("[ExitStartingConfigurationCommandGroup] Starting\n");
}

void ExitStartingConfigurationCommandGroup::End() {
	printf("[ExitStartingConfigurationCommandGroup] Ending\n");
}

void ExitStartingConfigurationCommandGroup::Interrupted() {
	printf("[ExitStartingConfigurationCommandGroup] Interrupted\n");
}
