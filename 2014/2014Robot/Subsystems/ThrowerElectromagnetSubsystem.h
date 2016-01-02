#ifndef THROWERELECTROMAGNETSUBSYSTEM_H
#define THROWERELECTROMAGNETSUBSYSTEM_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author nowireless
 */
class ThrowerElectromagnetSubsystem: public Subsystem {
public:
	enum ElectromagnetState {
		BeginThrow,
		Throwing,
		EndThrow,
		On,
		Off
	};
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	Relay *electromagnet;
	float electromagnetTime;
	ElectromagnetState state;
public:
	ThrowerElectromagnetSubsystem();
	void InitDefaultCommand();
	void TurnOn();
	void TurnOff();
	float GetElectromagetTime();
	ElectromagnetState GetState();
	void SetState(ElectromagnetState state);
	
	void StartThrow(float electromagnetTime);
};

#endif
