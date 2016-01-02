#ifndef TURNSPECIFIEDDEGREESENCODERCOUNTCOMMAND_H
#define TURNSPECIFIEDDEGREESENCODERCOUNTCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author nowireless
 */
class TurnSpecifiedDegreesEncoderCountCommand: public CommandBase , PIDOutput{
public:
	enum RotationCenter {
		kRight,
		kLeft,
		kCenter
	};
private:
	float degreesToTurn;
	float calcSetpont();
	float calcPTerm();
	float clacInputRange();
	int getRaduis();
	void cleanUp();
	RotationCenter rotationCenter;
	PIDController *controller;
public:
	TurnSpecifiedDegreesEncoderCountCommand(float degreesToTurn);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	virtual void PIDWrite(float output);
};

#endif
