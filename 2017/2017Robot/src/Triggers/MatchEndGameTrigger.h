#ifndef MatchTimeElapsed_H
#define MatchTimeElapsed_H

#include <Buttons/Trigger.h>

class MatchEndGameTrigger : public frc::Trigger {
public:
	MatchEndGameTrigger();
	virtual bool Get();
};

#endif  // MatchTimeElapsed_H
