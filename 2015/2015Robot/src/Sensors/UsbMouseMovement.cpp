/*
 * UsbMouse.cpp
 *
 *  Created on: Mar 12, 2015
 *      Author: nowireless
 */

/**
 * Note: For this class to work /dev/input/mouse0 needs to be readable by the lvuser.
 * As normally only root can have access to this device. lvuser needs to be added to a group that has access to the /dev,
 * or a udev rule is set.
 */
#include <Sensors/UsbMouseMovement.h>
#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <HAL/cpp/Synchronized.hpp>
#include <Timer.h>

#define MOUSEFILE "/dev/input/mouse0"

const double MOVEMENT_TIMEOUT = 0.5;

ReentrantSemaphore STATE_SEMAPHORE;

void UsbMouseMovement::Run(UsbMouseMovement *instance) {
	instance->Init();
	while(instance->IsRunning() && instance->IsMouseOpen()) {
		if(instance->IsEnabled()) {
			instance->Update();
		}
	}
}

UsbMouseMovement::UsbMouseMovement() {
	this->updateThread = new std::thread(UsbMouseMovement::Run, this);
	this->SetEnabled(false);
}

UsbMouseMovement::~UsbMouseMovement() {
	this->SetRunning(false);
	this->updateThread->join();
	delete this->updateThread;
}

void UsbMouseMovement::Init() {
	CRITICAL_REGION(STATE_SEMAPHORE)
		this->fd = open(MOUSEFILE, O_RDONLY);
		if(this->fd == -1) {
			printf("Failed to Open mouse\n");
		} else {
			printf("Opened the mouse");
		}
		this->lastCheckIn = Timer::GetFPGATimestamp();
	END_REGION
}

void UsbMouseMovement::Update() {
	CRITICAL_REGION(STATE_SEMAPHORE)
		if(read(this->fd, &ie, sizeof(struct input_event))) {
			//When read returns new data is available, meaning that the mouse moved.
			this->lastCheckIn = Timer::GetFPGATimestamp();
		}
	END_REGION
}

bool UsbMouseMovement::IsMouseOpen() {
	Synchronized sync(STATE_SEMAPHORE);
	return this->fd != -1;
}

void UsbMouseMovement::SetEnabled(bool enabled) {
	Synchronized sync(STATE_SEMAPHORE);
	this->enabled = enabled;
}

bool UsbMouseMovement::IsEnabled() {
	Synchronized sync(STATE_SEMAPHORE);
	return this->enabled;
}

void UsbMouseMovement::SetRunning(bool run) {
	Synchronized sync(STATE_SEMAPHORE);
	this->running = run;
}

bool UsbMouseMovement::IsRunning() {
	Synchronized sync(STATE_SEMAPHORE);
	return this->running;
}

bool UsbMouseMovement::IsMoving() {
	double ts = 0;

	CRITICAL_REGION(STATE_SEMAPHORE)
		ts = this->lastCheckIn;
	END_REGION

	return (Timer::GetFPGATimestamp() - ts) < MOVEMENT_TIMEOUT;
}
