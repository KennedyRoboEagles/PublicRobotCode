#include "database.h"

#include <iostream>

using namespace std;
using namespace nt;
using namespace wpi;
using namespace log4cxx;

Database::Database(std::string pathToDb) : db_(pathToDb, SQLite::OPEN_READWRITE) {
    log_ = Logger::getLogger("Database");

    LOG4CXX_INFO(log_, "Opening database at " << pathToDb); 
    sessionId_ = this->createSession();
}

Database::~Database() {
}

void Database::AddValue(string key, shared_ptr<Value> ntValue) {
    auto now = std::chrono::high_resolution_clock::now();
    auto diff = now - sessionStart_ ;
    // Get time stamp to nanoseconds
    uint64_t timeStamp = std::chrono::duration_cast<std::chrono::nanoseconds>(diff).count();

    switch(ntValue->type()) {
    case NT_Type::NT_BOOLEAN:
        this->createEventBool(timeStamp, key, ntValue->GetBoolean());
        break;
    case NT_Type::NT_DOUBLE:
        this->createEventDouble(timeStamp, key, ntValue->GetDouble());
        break;
    case NT_Type::NT_STRING:
        this->createEventString(timeStamp, key, ntValue->GetString());
        break;
    default:
        LOG4CXX_DEBUG(log_, "Ingoring value, unsupported datatype: " << key);
        break;         
    }
}


void Database::createEventDouble(int64_t timestamp, std::string key, double value) {
    LOG4CXX_DEBUG(log_, "Inserting Event Double");
    SQLite::Transaction transaction(db_);

    int eventId = this->createEvent(timestamp, key, "double");

    SQLite::Statement valueInsert(db_, "INSERT INTO ValueNumber(Id, Value) VALUES (?, ?)");
    valueInsert.bind(1, eventId);
    valueInsert.bind(2, value);

    LOG4CXX_DEBUG(log_, "Inserting bool value");
    int rows = valueInsert.exec();
    LOG4CXX_DEBUG(log_, "Rows modifed: " << rows);

    transaction.commit(); 
}

void Database::createEventString(int64_t timestamp, std::string key, std::string value) {
    LOG4CXX_DEBUG(log_, "Inserting Event String");
    SQLite::Transaction transaction(db_);

    int eventId = this->createEvent(timestamp, key, "string");

    SQLite::Statement valueInsert(db_, "INSERT INTO ValueString(Id, Value) VALUES (?, ?)");
    valueInsert.bind(1, eventId);
    valueInsert.bind(2, value);

    LOG4CXX_DEBUG(log_, "Inserting string value");
    int rows = valueInsert.exec();
    LOG4CXX_DEBUG(log_, "Rows modifed: " << rows);

    transaction.commit(); 
}

void Database::createEventBool(int64_t timestamp, std::string key, bool value) {
    LOG4CXX_DEBUG(log_, "Inserting Event Bool");
    SQLite::Transaction transaction(db_);

    int eventId = this->createEvent(timestamp, key, "bool");
    
    SQLite::Statement valueInsert(db_, "INSERT INTO ValueBool(Id, Value) VALUES (?, ?)");
    valueInsert.bind(1, eventId);
    valueInsert.bind(2, value);

    LOG4CXX_DEBUG(log_, "Inserting bool value");
    int rows = valueInsert.exec();
    LOG4CXX_DEBUG(log_, "Rows modifed: " << rows);

    transaction.commit(); 
}

int Database::createEvent(int64_t timestamp, std::string key, std::string type) {
    LOG4CXX_DEBUG(log_, "Inserting Event ("  << sessionId_ << timestamp << "," << timestamp << ", " << key << ", " << type << ")");
    SQLite::Statement eventInsert(db_, "INSERT INTO Event(TimeStamp, SessionId, Key, Type) VALUES (?, ?, ?, ?)");    
    eventInsert.bind(1, timestamp);
    eventInsert.bind(2, sessionId_);
    eventInsert.bind(3, key);
    eventInsert.bind(4, type);
 
    int rows = eventInsert.exec();
    LOG4CXX_DEBUG(log_, "Rows modifed: " << rows);

    int eventId = db_.getLastInsertRowid();
    LOG4CXX_DEBUG(log_, "Inserted with id: " << eventId);
    
    return eventId;

    // std::string insertEvent = "INSERT INTO Event(Name, Type) VALUES (:name, :type)";

    // sqlite3_stmt* stmt;
    // int ret = sqlite3_prepare_v2(db_, insertEvent.c_str(), -1, &stmt, NULL);
    // if (ret) {
    //     cerr << "Cant prepare statement: " << sqlite3_errmsg(db_) << endl;
    // }
    
    // int index = sqlite3_bind_parameter_index(stmt, "name");
    // assert(index == 0);

    // ret = sqlite3_bind_text(stmt, index, key.c_str(), -1, SQLITE_TRANSIENT);
    // assert(ret == 0);


    // int typeIndex = sqlite3_bind_parameter_index(stmt, "type");
    // assert(index == 0);
    // ret = sqlite3_bind_text(stmt, typeIndex, type.c_str(), -1, SQLITE_TRANSIENT);
    // assert(ret == 0);

    // return sqlite3_last_insert_rowid(db_);
}

int Database::createSession() {
    LOG4CXX_DEBUG(log_, "Inserting Session ("  << ")");

    sessionStart_ = std::chrono::high_resolution_clock::now();
    LOG4CXX_DEBUG(log_, "Session Start: " << sessionStart_.time_since_epoch().count());
   
    SQLite::Statement insert(db_, "INSERT INTO [Session] DEFAULT VALUES;");    
 
    int rows = insert.exec();
    LOG4CXX_DEBUG(log_, "Rows modifed: " << rows);

    int sessionId = db_.getLastInsertRowid();
    LOG4CXX_DEBUG(log_, "Inserted with id: " << sessionId); 

    return sessionId;
}