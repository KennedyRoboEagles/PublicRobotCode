#include "LEDSubsytem.h"
#include "../Robotmap.h"
#include "../Commands/LEDcontrolcommand.h"

LEDSubsytem::LEDSubsytem() : Subsystem("LEDSubsytem") {
	this->greenRing = new Solenoid(LED_MODULE,LED_GREEN_RING);
	this->blueStrip = new Solenoid(LED_MODULE,LED_BLUE_STRIP);
	this->redStrip = new Solenoid(LED_MODULE,LED_RED_STRIP);
}
    
void LEDSubsytem::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
	SetDefaultCommand(new LEDcontrolcommand());
}

void LEDSubsytem::Run() {
	this->greenRing->Set(true);
}
void LEDSubsytem::Blueonoff(bool active){
	this->blueStrip->Set(active);
}
void LEDSubsytem::Redonoff(bool active){
	this->redStrip->Set(active);
}
