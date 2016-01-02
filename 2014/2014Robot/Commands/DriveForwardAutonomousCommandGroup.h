#ifndef DRIVEFORWARDAUTONOMOUSCOMMANDGROUP_H
#define DRIVEFORWARDAUTONOMOUSCOMMANDGROUP_H

#include "Commands/CommandGroup.h"

/**
 *
 *
 * @author scum
 */
class DriveForwardAutonomousCommandGroup: public CommandGroup {
public:	
	DriveForwardAutonomousCommandGroup(int distance);
};

#endif
