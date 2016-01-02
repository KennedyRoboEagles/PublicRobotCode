#include "CompressorSubsystem.h"
#include "../Robotmap.h"
#include "../Commands/RunCompressorCommand.h"

CompressorSubsystem::CompressorSubsystem() : Subsystem("CompressorSubsystem") {
	printf("[CompressorSubsystem] Starting Construction\n");
	this->compressor = new Compressor(PRESSURE_SWITCH_CHANNEL, COMPRESSOR_RELAY_CHANNEL);
	printf("[CompressorSubsystem] Finished Construction\n");
}
    
void CompressorSubsystem::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	SetDefaultCommand(new RunCompressorCommand());
}
 void CompressorSubsystem::Start() {
	 printf("[CompressorSubsystem] Starting Compressor\n");
	 this->compressor->Start();
 }
 
 void CompressorSubsystem::Stop() {
	 printf("[CompressorSubsystem] Stopping Compressor\n");
	 this->compressor->Stop();
 }

 bool CompressorSubsystem::GetPressureSwitch() {
	 return this->compressor->GetPressureSwitchValue() == 1;
 }
