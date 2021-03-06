/*
 * AutoSelection.cpp
 *
 *  Created on: Feb 21, 2017
 *      Author: Ryan
 */

#include "AutoSelection.h"
#include <map>
#include <iostream>
#include <Preferences.h>
#include <SmartDashboard/SmartDashboard.h>
#include <Commands/PrintCommand.h>
#include "Commands/Autonomous/BoilerCommandGroup.h"
#include "Commands/Autonomous/CenterPegCommandGroup.h"
#include "Commands/Autonomous/LoadingStationCommandGroup.h"

#include <mutex>
#include <thread>

static std::string auto2name[AutoSelection::LastAuto];
static frc::Command* auto2cmd[AutoSelection::LastAuto];
static std::map<std::string,AutoSelection::Auto> name2Auto;

AutoSelection* AutoSelection::instance = nullptr;

void AutoSelection::Initialize(RevDigit* revDigit) {
	if(instance == nullptr) {
		instance = new AutoSelection(revDigit);
	} else {
		std::cerr << "Tried to reinitialize AutoSlection" << std::endl;
		return;
	}
	instance->Init();
}

AutoSelection* AutoSelection::GetInstance() {
	return instance;
}

AutoSelection::AutoSelection(RevDigit* revDigit) {
	this->revDigit = revDigit;

	auto2name[DefaultAuto] = "Default Auto";
	auto2name[LoadingStationAutoBlue] = "Loading Station Blue";
	auto2name[LoadingStationAutoRed] = "Loading Station Red";
	auto2name[CenterPegAuto] = "Center Peg Auto";
	auto2name[BoilerAutoBlue] = "Boiler Auto Blue";
	auto2name[BoilerAutoRed] = "Boiler Auto Red";

	name2Auto.insert(std::make_pair(auto2name[DefaultAuto], DefaultAuto));
	name2Auto.insert(std::make_pair(auto2name[LoadingStationAutoBlue], LoadingStationAutoBlue));
	name2Auto.insert(std::make_pair(auto2name[LoadingStationAutoRed], LoadingStationAutoRed));
	name2Auto.insert(std::make_pair(auto2name[CenterPegAuto], CenterPegAuto));
	name2Auto.insert(std::make_pair(auto2name[BoilerAutoBlue], BoilerAutoBlue));
	name2Auto.insert(std::make_pair(auto2name[BoilerAutoRed], BoilerAutoRed));

	{
		std::lock_guard<std::mutex> lock(selectedAutoMutex);
		selectedAuto = (Auto) frc::Preferences::GetInstance()->GetInt("selected_auto", LoadingStationAutoRed);
	}
}

void AutoSelection::Init() {
	auto2cmd[DefaultAuto] = new PrintCommand("Doing nothing");
	auto2cmd[LoadingStationAutoBlue] = new LoadingStationCommandGroup(true);
	auto2cmd[LoadingStationAutoRed] = new LoadingStationCommandGroup(false);
	auto2cmd[CenterPegAuto] = new CenterPegCommandGroup();
	auto2cmd[BoilerAutoBlue] = new BoilerCommandGroup(true);
	auto2cmd[BoilerAutoRed] = new BoilerCommandGroup(false);

	{
		std::lock_guard<std::mutex> lock(selectedAutoMutex);
		this->UpdateSmartDashboard(selectedAuto);
	}

	t = std::thread(WorkerThread, this);
}

AutoSelection::~AutoSelection() {}

void AutoSelection::WorkerThread(AutoSelection* i) {
	while(true) {
		if(i->revDigit->GetA()) {
			//Goto next auto
			i->NextAuto();
		} else if(i->revDigit->GetB()) {
			//Goto previous auto
			i->PreviousAuto();
		} else {
			// Do nothing
		}

		//Update Display
		char buff[20];
		sprintf(buff, "%i", i->CurrentAuto());
		i->revDigit->Display(buff);

		//Update at a rate of 10hz
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

void AutoSelection::UpdateSmartDashboard(Auto selected) {
	frc::Preferences::GetInstance()->PutInt("selected_auto", selected);
	SmartDashboard::PutString("Selected Auto", auto2name[selected]);
}

void AutoSelection::NextAuto() {
	std::lock_guard<std::mutex> lock(selectedAutoMutex);
	selectedAuto = (Auto) ((selectedAuto + 1) % LastAuto);
	this->UpdateSmartDashboard(selectedAuto);
}

void AutoSelection::PreviousAuto() {
	std::lock_guard<std::mutex> lock(selectedAutoMutex);
	selectedAuto = (Auto) (selectedAuto - 1);
	if(selectedAuto < 0) {
		selectedAuto = (Auto) (LastAuto - 1);
	}
	this->UpdateSmartDashboard(selectedAuto);
}

AutoSelection::Auto AutoSelection::CurrentAuto() {
	Auto ret;
	{
		std::lock_guard<std::mutex> lock(selectedAutoMutex);
		ret = selectedAuto;
	}
	return ret;
}

frc::Command* AutoSelection::GetSelected() {
	Command* ret;
	{
		std::lock_guard<std::mutex> lock(selectedAutoMutex);
		ret = auto2cmd[selectedAuto];
	}
	return ret;
}
