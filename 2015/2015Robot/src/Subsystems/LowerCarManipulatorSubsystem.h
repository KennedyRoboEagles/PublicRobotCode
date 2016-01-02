#ifndef LowerCarManipulatorSubsystem_H
#define LowerCarManipulatorSubsystem_H

#include "Commands/Subsystem.h"
#include "SensorSubsystem.h"
#include "DiasyFilter/DaisyFilter.h"
#include "WPILib.h"
#include "Util/GrabberSD.h"

class LowerCarManipulatorSubsystem: public Subsystem
{
public:
	enum LowerCarManipulatorState {
		MS_Unknown,
		MS_Calibrating,
		MS_OpenForWideTote,
		MS_OpenForNarrowTote,
		MS_CloseForNarrowTote,
		MS_AcquireTote,
		MS_ReleaseTote,
		MS_CloseForBin
		};

	enum ToteState {
			NoTote,
			AcquiringTote,
			HaveTote,
			NoToteFound,
		};

	LowerCarManipulatorSubsystem(SensorSubsystem * sensorSubsystem);


	void InitDefaultCommand();

	LowerCarManipulatorState GetCurrentState();
	void SetCurrentState(LowerCarManipulatorState newState);

	void Calibrate();
	void AcquireTote();
	void ReleaseTote();
	void SetSize(double sizeInInches);

	void ResetToteState();
	ToteState GetToteState();
	bool IsDone();
	void ResetIsDone();

	CANJaguar *GetManipulatorMotor();
	bool GetManipulatorForwardLimit();
	bool GetManipulatorReverseLimit();

	bool IsCurrentOk();
	void UpdateCurrent();

	GrabberSD *GetSD();

	double GetManipulatorMotorCurrent();
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

	LowerCarManipulatorState subsystemState;
	enum CalibrationState {
		Uncalibrated,
		StartClosing,
		Closing,
		Calibrated,
	};
	CalibrationState calibrationState;

	ToteState toteState;

	CANJaguar* manipulatorMotor;
	SensorSubsystem *sensorSubsystem;

	DaisyFilter *currentFilter;
	float filteredCurrent;

	// True when the subsystem reaches it positon
	bool isDone;

	// Number of samples of zero current observed
	int zeroCurrentSampleCount = 0;

	// Widest position that the manipulator can be open
	double maxPosition = 0;

	// This is the last held position during grabbing a tote.
	double heldPosition = 0;

	const float openingSpeed = -0.5;
	const float closingSpeed = 0.5;

	double GetManipulatorPosition();

	GrabberSD *sd;
};

#endif
