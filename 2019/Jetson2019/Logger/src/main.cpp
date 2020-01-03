

#include <csignal>

#include <chrono>
#include <iostream>
#include <thread>
#include <memory>

#include <ntcore.h>
#include <networktables/NetworkTableInstance.h>
#include <gflags/gflags.h>
#include <log4cxx/log4cxx.h>
#include <log4cxx/basicconfigurator.h>
#include <log4cxx/propertyconfigurator.h>
#include "database.h"

// CLI Arguments
DEFINE_string(logconfig, "config/logger.config", "Path to logger configuration");
DEFINE_bool(debug, false, "Enable debugging output");
DEFINE_bool(trace, false, "Enable debugging trace output");

DEFINE_string(db, "logger.db", "Database file");

DEFINE_bool(server, false, "Network tables server");
DEFINE_int32(team, 3081, "Team number");

// Logging
log4cxx::LoggerPtr logger;
log4cxx::LoggerPtr ntcoreLogger;

// Database
std::unique_ptr<Database> db;

bool running = true;
void signalHandler(int) {
    running = false;
}

void entryListener(const nt::EntryNotification& event) {
    LOG4CXX_INFO(logger, "Listener: " << event.name);
    db->AddValue(event.name, event.value);
}

// void timeListener(const nt::EntryNotification& event) {
//     LOGC4CXX_INFO(logger, "Timer Listener: " << event.name);
//     if (event.value->type() == NT_Type::NT_DOUBLE) {
//         int64_t unixEpoch = event.value->GetDouble();
//         auto time = std::chrono::system_clock::from_time_t(unixEpoch);
//     }
// }

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

    // Setup Database
    db = std::make_unique<Database>(FLAGS_db);

    // Setup NTCore
    auto ntinst = nt::NetworkTableInstance::GetDefault();
    if (FLAGS_server) {
        LOG4CXX_INFO(logger, "Setting up NetworkTables Server");
        ntinst.StartServer();
    } else {
        LOG4CXX_INFO(logger, "Setting up NetworkTables client for team " << FLAGS_team);
        ntinst.StartClientTeam(FLAGS_team);
    }
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

    // Listen to all
    nt::AddEntryListener(
        ntinst.GetHandle(), 
        wpi::Twine("/"), 
        entryListener, 
        NT_NOTIFY_NEW | NT_NOTIFY_UPDATE | NT_NOTIFY_DELETE | NT_NOTIFY_IMMEDIATE
    );

    // // Setup time listener
    // auto timeEntry = nt::GetEntry(ntinst.GetHandle(), wpi::Twine("/rio/time"));
    // nt::AddEntryListener(
    //     timeEntry,
    //     timeListener,  
    //     NT_NOTIFY_NEW | NT_NOTIFY_UPDATE
    // );

    auto sd = ntinst.GetTable("SmartdDashboard");
    sd->PutNumber("Foo", 5);

    while(running) {
        // LOG4CXX_INFO(logger, "hello");
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    gflags::ShutDownCommandLineFlags();
    return 0;
}

