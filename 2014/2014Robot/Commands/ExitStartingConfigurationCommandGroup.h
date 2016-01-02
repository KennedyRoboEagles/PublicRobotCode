#ifndef EXITSTARTINGCONFIGURATIONCOMMANDGROUP_H
#define EXITSTARTINGCONFIGURATIONCOMMANDGROUP_H

#include "Commands/CommandGroup.h"

/**
 *
 *
 * @author nowireless
 */
class ExitStartingConfigurationCommandGroup: public CommandGroup {
public:	
	ExitStartingConfigurationCommandGroup();
	virtual void Initialize();
	virtual void End();
	virtual void Interrupted();
};

#endif
