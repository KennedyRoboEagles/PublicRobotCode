#ifndef COMPRESSORSUBSYSTEM_H
#define COMPRESSORSUBSYSTEM_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author nowireless
 */
class CompressorSubsystem: public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	Compressor *compressor;
public:
	CompressorSubsystem();
	void InitDefaultCommand();
	void Start();
	void Stop();
	bool GetPressureSwitch();
};

#endif
