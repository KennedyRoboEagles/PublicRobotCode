/*
 * LIDARLite.cpp
 *
 *  Created on: Feb 8, 2015
 *      Author: Steve
 */

#include <Sensors/LIDARLite.h>
#include <time.h>

/*
 * Ported from https://gist.github.com/tech2077/c4ba2d344bdfcddd48d2
 */
LIDARLite::LIDARLite(I2C::Port port) : semaphore(0) {
	printf("[LIDARLite] initializing\n");
	this->Lidar = new I2C(port, LIDAR_ADDR);
	if (this->Lidar->AddressOnly())
	{
		printf("[LIDARLite] Device found.\n");
	}
	else
	{
		printf("[LIDARLite] Device not found.\n");
	}
	this->updateNotifier = new Notifier(LIDARLite::CallReadValue, this);
	printf("[LIDARLite] initialized\n");
}

LIDARLite::~LIDARLite() {
	delete this->Lidar;
}

int LIDARLite::GetDistance() {
	return this->distance;
}

double LIDARLite::PIDGet() {
	return this->GetDistance();
}

void LIDARLite::Start() {
	this->updateNotifier->StartPeriodic(.02);
}

void LIDARLite::Stop() {
	this->updateNotifier->Stop();
}

void LIDARLite::Update() {
	this->ReadValue();
}

void LIDARLite::CallReadValue(void* lidarLite) {
	LIDARLite *target = (LIDARLite *) lidarLite;
	target->ReadValue();
}

void LIDARLite::i2cSleep()
{
	   struct timespec tim, tim2;
	   tim.tv_sec = 1;
	   tim.tv_nsec = NS_PER_MS;

	   nanosleep(&tim , &tim2);
}

void LIDARLite::ReadValue() {
	bool ack = false;
	int count = 0;

	if (!this->Lidar->AddressOnly())
	{
		printf("[LIDARLite] Can't address device.\n");
	}
	while (!ack && count++ < RETRIES)
	{
		ack = this->Lidar->Write(LIDAR_CONFIG_REGISTER, LIDAR_MEASURE);
		i2cSleep();
		printf("[LIDARLite] Waiting for config to complete %d\n", count);
	}
	if (!ack)
	{
		printf("[LIDARLite] config failed.\n");
		return;
	}

	ack = false;
	count = 0;
	while (!ack && count++ < RETRIES)
	{
		unsigned char data;
		ack = this->Lidar->Read(0x04, 1, &data);
		//ack = this->Lidar->Read(LIDAR_DISTANCE_REGISTER, 2, this->readBytes);
		i2cSleep();
		printf("[LIDARLite] Waiting for read to complete %d\n", count);
	}

	if (!ack)
	{
		printf("[LIDARLite] read failed.\n");
		return;
	}
	printf("[LIDARLite] read completed.\n");


	CRITICAL_REGION(semaphore)
	{
		this->distance = this->readBytes[0] << 8 | this->readBytes[1];
	}
	END_REGION;
}

