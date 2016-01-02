#ifndef THROWERSUBSYSTEM_H
#define THROWERSUBSYSTEM_H
#include "Commands/Subsystem.h"
//#include "../Commands/ThrowerSupervisiorCommand.h"
#include "WPILib.h"

#define THROWER_MAX_POWER (10)
#define THROWER_MIN_POWER (1)

/**
 *
 *
 * @author nowireless
 */
class ThrowerSubsystem: public Subsystem {
friend class ThrowerSupervisiorCommand;
private:
	Solenoid *leftSolenoidIn;
	Solenoid *leftSolenoidOut;
	Solenoid *rightSolenoidIn;
	Solenoid *rightSolenoidOut;
	
	void setInSide(bool open);
	void setOutSide(bool open);
	
	void startThrow();
	void stopThrow();
	void startRetract();
	void stopRetract();
	void stop();
public:
	ThrowerSubsystem();
	void InitDefaultCommand();
	
	void Throw();
	void Retract();
	void Stop();
	void SetInSolenoids(bool open);
	void SetOutSolenois(bool open);
	void TurnOnElectromagenet();
	void TurnOffElectromagnet();
};

#endif
