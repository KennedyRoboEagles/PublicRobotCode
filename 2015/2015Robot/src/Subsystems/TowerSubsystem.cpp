#include "TowerSubsystem.h"
#include "../RobotMap.h"
#include "../Commands/TowerSupervisorCommnad.h"

TowerSubsystem::TowerSubsystem(SensorSubsystem *sensorSubsystem) : Subsystem("TowerSubsystem") {
	this->sensorSubsystem = sensorSubsystem;
}

void TowerSubsystem::InitDefaultCommand() {
	//SetDefaultCommand(new TowerSupervisorCommnad());
}

bool TowerSubsystem::GetBottomLimit() {
	return sensorSubsystem->TowerLowLimit();
}
