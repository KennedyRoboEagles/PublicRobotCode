#ifndef LEDSUBSYTEM_H
#define LEDSUBSYTEM_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author scum
 */
class LEDSubsytem: public Subsystem {
private:
	Solenoid *greenRing;
	Solenoid *blueStrip;
	Solenoid *redStrip;
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	LEDSubsytem();
	void InitDefaultCommand();
	void Run();
	void Redonoff(bool active);
	void Blueonoff(bool active);
};

#endif
