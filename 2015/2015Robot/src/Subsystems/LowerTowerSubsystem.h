#ifndef LowerTowerSubsystem_H
#define LowerTowerSubsystem_H

#include "Commands/Subsystem.h"
#include "SensorSubsystem.h"
#include "WPILib.h"

static const float kTowerOffset = 9.5;

class LowerTowerSubsystem: public Subsystem
{
public:
	enum LowerTowerPosition {
		LowerTotePosition,
		BottomPosition,
		BottomToteMovementPosition,
		PickUpPosition,
		SecondToteAcquisitionPosition,
		StackPosition,
		PickedUpBinPosition,
		ClearPlayerStationPosition,
		BinClear4StackPosition
	};

	enum LowerTowerState {
		EnterCalibration,
		Calibration,
		CalibrationReached,
		Running,
		Stopped
	};

	const float kForwardSpeed = 0.25;
	const float kBackwardSpeed = -0.75;

	LowerTowerSubsystem(SensorSubsystem *sensorSubsystem);
	void InitDefaultCommand();

	CANJaguar *GetVerticalJaguar();
	Servo *GetDogGearServo();

	Encoder *GetEncoder();
	float GetForce();
	bool GetTopLimit();
	int GetEncoderCount();
	float GetEncoderDistance();
	void ResetEncoder();

	void DogGearForward();
	void DogGearForward(float speed);
	void DogGearBackward();
	void DogGearBackward(float speed);
	void DogGearStop();
	void DogGearRun();
	bool DogGearReady();

	LowerTowerState GetState();
	void SetState(LowerTowerState state);

	bool DidStateChange();
	void SetStateChange(bool changed);

	LowerTowerPosition GetPosition();

	void ReEnable();

	void SetAtPosition(bool val);
	bool IsAtPosition();

	void PositionLowerTote();
	void PositionPickUpTote();
	void PositionStackTote();
	void PositionBottom();
	void PositionPickedUpBin();
	void PositionSecondToteAcquisition();
	void PositionClearPlayerStation();
	void PositionBottomToteMovementPosition();
	void PositionBinClear4Stack();

private:
	enum LowerTowerDogGearState {
		DG_Forward,
		DG_Backward,
		DG_Stop
	};

	enum DogGearForwardSubState {
		DGF_Start,
		DGF_MoveBackward,
		DGF_MoveForward,
	};

	enum DogGearBackwardSubState {
		DGR_Start,
		DGR_Backward,
	};

	const float kDGFBackwardTime = 0.1;
	const float kDGServoUpPosition = 0.7;
	const float kDGServoDownPosition = -0.2;

	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	SensorSubsystem *sensorSubsystem;
	CANJaguar *lowerTowerJaguar;
	Servo *dgServo;
	//SpeedController *lowerTowerJaguar;

	void MoveForward();
	void MoveForward(float speed);
	void MoveBackward();
	void MoveBackward(float speed);
	void StopMotor();

	void ServoUp();
	void ServoDown();

	void UpdateDogGearStateToSD();

	Timer *dgTimer;
	float dgGearSpeed;

	LowerTowerState state;
	LowerTowerPosition position;
	bool stateChange;

	LowerTowerDogGearState dgState;
	DogGearForwardSubState dgForwardSubState;
	DogGearBackwardSubState dgBackwardSubState;
	bool dogGearReady;
	bool atPosition;
};

#endif
