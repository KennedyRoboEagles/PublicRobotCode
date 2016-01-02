#include "RunCompressorCommand.h"

RunCompressorCommand::RunCompressorCommand() : CommandBase("RunCompressorCommand") {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(compressorSubsystem);
}

// Called just before this Command runs the first time
void RunCompressorCommand::Initialize() {
	printf("[RunCompressorCommand] Starting Compressor\n");
	compressorSubsystem->Start();
}

// Called repeatedly when this Command is scheduled to run
void RunCompressorCommand::Execute() {
	
}

// Make this return true when this Command no longer needs to run execute()
bool RunCompressorCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void RunCompressorCommand::End() {
	printf("[RunCompressorCommand] Stopping Compressor\n");
	compressorSubsystem->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RunCompressorCommand::Interrupted() {
	printf("[RunCompressorCommand] Stopping Compressor\n");
	compressorSubsystem->Stop();
}
