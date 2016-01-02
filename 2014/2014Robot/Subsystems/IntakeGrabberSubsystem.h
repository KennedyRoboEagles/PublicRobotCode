#ifndef INTAKEGRABBERSUBSYSTEM_H
#define INTAKEGRABBERSUBSYSTEM_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author nowireless
 */
class IntakeGrabberSubsystem: public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	DoubleSolenoid *grabberSolenoid;
public:
	IntakeGrabberSubsystem();
	void InitDefaultCommand();
	void Open();
	void Close();
	void Stop();
};

#endif
