#ifndef UpperTowerSubsystem_H
#define UpperTowerSubsystem_H

#include "Commands/Subsystem.h"
#include "SensorSubsystem.h"
#include "WPILib.h"

class UpperTowerSubsystem: public Subsystem
{
public:
	enum UpperTowerPosition {
		TopPosition,
		PickUpPosition,
		StackPosition,
		StoppedAtCurrentPosition
	};

	enum UpperTowerState {
		EnterCalibration,
		Calibration,
		CalibrationReached,
		Running,
		Stopped
	};

	const float kUpSpeed = 0.25;
	const float kDownSpeed = -0.25;

	UpperTowerSubsystem(SensorSubsystem *sensorSubsystem);
	void InitDefaultCommand();

	CANJaguar *GetVerticalJaguar();
	Encoder *GetEncoder();
	float GetForce();
	bool GetTopLimit();
	int GetEncoderCount();
	void ResetEncoder();

	void MoveDown();
	void MoveUp();
	void StopMotor();

	UpperTowerState GetState();
	void SetState(UpperTowerState state);

	UpperTowerPosition GetPosition();

	void PickUpBin();
	void StackBin();
	void Top();
	void StopAtCurrentPosition();

private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	SensorSubsystem *sensorSubsystem;
	CANJaguar *upperTowerJaguar;
	UpperTowerState state;
	UpperTowerPosition position;
};

#endif
