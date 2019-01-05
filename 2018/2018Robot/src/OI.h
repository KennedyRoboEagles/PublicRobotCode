/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <Joystick.h>
#include <Buttons/JoystickButton.h>
#include <Util/RevDigit.h>

#include "Triggers/XboxDPadTrigger.h"

#include <memory>

class OI {
private:
	RevDigit* revDigit_;

	frc::XboxController* stick_;
	frc::Joystick* test_;

public:
	static std::shared_ptr<OI> GetInstance();

	OI();

	frc::XboxController* GetStick() { return stick_; }
	RevDigit* GetRevDigit() { return revDigit_; }

	double GetStickStrafe();
	double GetStickMove();
	double GetStickRotate();
};
