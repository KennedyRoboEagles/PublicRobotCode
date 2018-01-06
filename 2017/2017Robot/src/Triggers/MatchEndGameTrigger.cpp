#include <DriverStation.h>
#include <Triggers/MatchEndGameTrigger.h>

MatchEndGameTrigger::MatchEndGameTrigger() {
}

bool MatchEndGameTrigger::Get() {
	return frc::DriverStation::GetInstance().GetMatchTime() < 30.0
			&& frc::DriverStation::GetInstance().IsOperatorControl();
}

