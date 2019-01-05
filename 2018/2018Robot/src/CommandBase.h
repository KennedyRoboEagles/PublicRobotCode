/*
 * CommandBase.h
 *
 *  Created on: Jan 19, 2018
 *      Author: nowir
 */

#ifndef COMMANDBASE_H_
#define COMMANDBASE_H_

#include <Commands/Command.h>
#include <memory>

#include "Subsystems/Chassis.h"
#include "Subsystems/ElevatorSubsystem.h"
#include "Subsystems/IntakeSubsystem.h"
#include "Subsystems/LEDSubsystem.h"
#include "Subsystems/SensorSubsystem.h"
#include "OI.h"

#include "debug.h"

class CommandBase: public frc::Command {
public:
	static std::shared_ptr<Chassis> chassis;
	static std::shared_ptr<SensorSubsystem> sensors;
	static std::shared_ptr<ElevatorSubsystem> elevator;
	static std::shared_ptr<IntakeSubsystem> intake;
	static std::shared_ptr<LEDSubsystem> leds;
	static std::shared_ptr<OI> oi;

	static void InitSubsystems();

	CommandBase(const std::string& name) : frc::Command(name) {};
	CommandBase() = default;
	virtual ~CommandBase() {}
};

#endif /* COMMANDBASE_H_ */
