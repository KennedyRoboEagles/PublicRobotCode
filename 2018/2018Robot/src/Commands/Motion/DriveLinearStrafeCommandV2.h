/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "CommandBase.h"
#include <PIDController.h>
#include "Util/GenericPIDSource.h"
#include "Timer.h"

class DriveLinearStrafeCommandV2 : public CommandBase {
public:
	DriveLinearStrafeCommandV2(double goalX, double goalY, double heading);
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
private:
	frc::PIDController* angularController_;
	frc::PIDController* linearXController_;
	frc::PIDController* linearYController_;

	GenericPIDSource linearXSource_;
	GenericPIDSource linearYSource_;

	frc::Timer timer_;

	enum State {
		kRun,
		kSteadyState,
		kDone
	};

	State state_;
	double goalX_;
	double goalY_;
	double heading_;
};

