/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <Timer.h>
#include <PIDController.h>
#include <PIDOutput.h>
#include <PIDSource.h>
#include "CommandBase.h"

class AnySource : public PIDSource {
public:
	AnySource() : value_(0) {}
	virtual ~AnySource() {}
	void Set(double value) {
		value_ = value;
	}

	double PIDGet() {
		return value_;
	}
private:
	double value_;
};


class DriveLinearForwardCommand : public CommandBase, PIDOutput {
public:
	DriveLinearForwardCommand(double goal, double heading);
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

	void PIDWrite(double output) override {};

private:
	enum State {
		kRun,
		kSteadyState,
		kDone
	};

	State state_;
	double goal_;
	double heading_;

	frc::PIDController* angularController_;
	frc::PIDController* linearController_;
	frc::Timer timer_;
	AnySource linearSource_;
};

