#ifndef INTAKETILTSUBSYSTEM_H
#define INTAKETILTSUBSYSTEM_H
#include "Commands/Subsystem.h"
#include "WPILib.h"


/**
 *
 *
 * @author nowireless ft. A$AP rolfy
 */
class IntakeTiltSubsystem: public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	DoubleSolenoid *tiltDoubleSolenoid;
public:
	IntakeTiltSubsystem();
	void InitDefaultCommand();
	void TiltDown();
	void TiltUp();
	void Stop();
};

#endif
