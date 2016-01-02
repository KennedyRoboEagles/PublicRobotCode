#include "DriveForwardAutonomousCommandGroup.h"
#include "MoveForwardCommand.h"
#include "DriveDistancePIDCommand.h"

#define DRIVE_FORWARD_SPEED (.75)

DriveForwardAutonomousCommandGroup::DriveForwardAutonomousCommandGroup(int distance) {
		AddSequential(new DriveDistancePIDCommand(distance));
}
