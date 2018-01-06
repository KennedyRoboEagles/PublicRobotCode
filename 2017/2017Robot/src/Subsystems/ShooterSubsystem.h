#ifndef ShooterSubsystem_H
#define ShooterSubsystem_H

#include <Commands/Subsystem.h>
#include <Jaguar.h>

class ShooterSubsystem : public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	SpeedController *jag;
public:
	ShooterSubsystem();
	void InitDefaultCommand();
	void Shoot();
	void Stop();
};

#endif  // ShooterSubsystem_H
