#include <csignal>

#include <chrono>
#include <iostream>
#include <thread>
#include <memory>

#include <ntcore.h>
#include <networktables/NetworkTableInstance.h>
#include <cscore.h>
#include <cameraserver/CameraServer.h>

#include <gflags/gflags.h>
#include <log4cxx/log4cxx.h>
#include <log4cxx/basicconfigurator.h>
#include <log4cxx/propertyconfigurator.h>

// CLI Arguments
DEFINE_string(logconfig, "config/logger.config", "Path to logger configuration");
DEFINE_bool(debug, false, "Enable debugging output");
DEFINE_bool(trace, false, "Enable debugging trace output");

DEFINE_bool(server, false, "Network tables server");
DEFINE_int32(team, 3081, "Team number");

DEFINE_string(cameraName, "Jetson Camera", "Name of camera");
DEFINE_string(cameraPath, "/dev/video0", "Device path of the camera");

// Logging
log4cxx::LoggerPtr logger;
log4cxx::LoggerPtr ntcoreLogger;

bool running = true;
void signalHandler(int) {
    running = false;
}


int main(int argc, char* argv[]) {
    // Setup signal handler for graceful exit
    signal(SIGINT, signalHandler);

    // Command line parsing
    gflags::SetUsageMessage("Usage Message");
    gflags::SetVersionString("0.0.1");
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    // Setup Logging
    std::cout << "Logging config: " << FLAGS_logconfig << std::endl;
    // log4cxx::BasicConfigurator::configure();
    log4cxx::PropertyConfigurator::configure(FLAGS_logconfig);
    logger = log4cxx::Logger::getLogger("main");
    ntcoreLogger = log4cxx::Logger::getLogger("ntcore");

    if (FLAGS_trace) {
        LOG4CXX_INFO(logger, "Logging set to trace level");
        logger->setLevel(log4cxx::Level::getTrace());
    } else if (FLAGS_debug) {
        LOG4CXX_INFO(logger, "Logging set to debug level");
        logger->setLevel(log4cxx::Level::getDebug());
    }

    // Setup NTCore
    auto ntinst = nt::NetworkTableInstance::GetDefault();
    if (FLAGS_server) {
        LOG4CXX_INFO(logger, "Setting up NetworkTables Server");
        ntinst.StartServer();
    } else {
        LOG4CXX_INFO(logger, "Setting up NetworkTables client for team " << FLAGS_team);
        ntinst.StartClientTeam(FLAGS_team);
    }

    // Make NTCore use log4cxx
    nt::AddLogger(ntinst.GetHandle(), [](const nt::LogMessage &msg) {
        switch(msg.level) {
        case NT_LOG_CRITICAL:
            LOG4CXX_FATAL(ntcoreLogger, msg.message);
            break;
        case NT_LOG_ERROR:
            LOG4CXX_ERROR(ntcoreLogger, msg.message);
            break;
        case NT_LOG_WARNING:
            LOG4CXX_WARN(ntcoreLogger, msg.message);
            break;
        case NT_LOG_INFO:
            LOG4CXX_INFO(ntcoreLogger, msg.message);
            break;
        case NT_LOG_DEBUG:
            LOG4CXX_DEBUG(ntcoreLogger, msg.message);
            break;
        default:
            LOG4CXX_TRACE(ntcoreLogger, msg.message);
        }
    }, 0, UINT_MAX);

    // Setup Camera Server
    LOG4CXX_INFO(logger, "Camera Name: " << FLAGS_cameraName)
    LOG4CXX_INFO(logger, "Camera Device Path: " << FLAGS_cameraPath)
    auto camera = frc::CameraServer::GetInstance()->StartAutomaticCapture(FLAGS_cameraName, FLAGS_cameraPath);
    camera.SetVideoMode(cs::VideoMode::PixelFormat::kMJPEG, 320, 240, 15);

    // Loop forever
    while(running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    gflags::ShutDownCommandLineFlags();
    return 0;
}
