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
#include "Commands/Auto/AutoInitCommandGroup.h"
#include "Commands/Auto/AutoLeftCommandGroup.h"
#include "Commands/Auto/AutoCenterCommandGroup.h"
#include "Commands/Auto/AutoRightCommandGroup.h"
#include "Commands/TestCondCommandGroup.h"
#include "Commands/Auto/PassAutoLineCommandGroup.h"

#include <mutex>
#include <thread>

static std::string auto2name[AutoSelection::LastAuto];
static std::string auto2Display[AutoSelection::LastAuto];
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
	auto2name[LeftAuto] = "Left Auto";
	auto2name[CenterAuto] = "Center Auto";
	auto2name[RightAuto] = "Right Auto";
	auto2name[LineAuto] = "Line Auto";

	name2Auto.insert(std::make_pair(auto2name[DefaultAuto], DefaultAuto));
	name2Auto.insert(std::make_pair(auto2name[LeftAuto],   LeftAuto));
	name2Auto.insert(std::make_pair(auto2name[CenterAuto], CenterAuto));
	name2Auto.insert(std::make_pair(auto2name[RightAuto],  RightAuto));
	name2Auto.insert(std::make_pair(auto2name[LineAuto],  LineAuto));

	auto2Display[DefaultAuto] = "INIT";
	auto2Display[LeftAuto] =    "LEFT";
	auto2Display[CenterAuto] =  "CENT";
	auto2Display[RightAuto] =   "RGHT";
	auto2Display[LineAuto] =   "LINE";

	{
		std::lock_guard<std::mutex> lock(selectedAutoMutex);
		selectedAuto = (Auto) frc::Preferences::GetInstance()->GetInt("selected_auto", DefaultAuto);
	}
}

void AutoSelection::Init() {
	auto2cmd[DefaultAuto] = nullptr;
	auto2cmd[LeftAuto] = nullptr;
	auto2cmd[RightAuto] = nullptr;
	auto2cmd[CenterAuto] = nullptr;
	auto2cmd[LineAuto] = new PassAutoLineCommandGroup();

//	auto2cmd[DefaultAuto] = new PrintCommand("Default");
//	auto2cmd[LeftAuto] = new TestCondCommandGroup();
//	auto2cmd[RightAuto] = new PrintCommand("Right");
//	auto2cmd[CenterAuto] = new PrintCommand("Center");
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
		// char buff[20];
		// sprintf(buff, "%i", i->CurrentAuto());
		i->revDigit->Display(i->GetSelctedDisplay().c_str());

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

std::string AutoSelection::GetSelctedDisplay() {
	Auto ret;
	{
		std::lock_guard<std::mutex> lock(selectedAutoMutex);
		ret = selectedAuto;
	}
	return auto2Display[ret];
}
