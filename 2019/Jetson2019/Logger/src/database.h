#pragma once

#include <cstdint>
#include <ntcore.h>
#include <sqlite3.h>
#include <log4cxx/logger.h>

#include <chrono>
#include <string>

#include <SQLiteCpp/SQLiteCpp.h>
#include <SQLiteCpp/VariadicBind.h>


class Database {
public:
    Database(std::string pathToDb);
    ~Database();

    void AddValue(std::string key, std::shared_ptr<nt::Value> value);
private:
    void createEventDouble(int64_t timestamp, std::string key, double value);
    void createEventString(int64_t timestamp, std::string key, std::string value);
    void createEventBool(int64_t timestamp, std::string key, bool value);

    int createEvent(int64_t timestamp, std::string key, std::string type);

    int createSession();

    // sqlite3* db_;
    SQLite::Database db_;

    int sessionId_;
    std::chrono::time_point<std::chrono::high_resolution_clock> sessionStart_;

    log4cxx::LoggerPtr log_;
};