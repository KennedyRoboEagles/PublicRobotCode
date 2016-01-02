#ifndef ENTERSTARTINGCONFIGURATIONCOMMANDGROUP_H
#define ENTERSTARTINGCONFIGURATIONCOMMANDGROUP_H

#include "Commands/CommandGroup.h"

/**
 *
 *
 * @author nowireless
 */
class EnterStartingConfigurationCommandGroup: public CommandGroup {
public:	
	EnterStartingConfigurationCommandGroup();
	virtual void Initialize();
	virtual void End();
	virtual void Interrupted();
};

#endif
