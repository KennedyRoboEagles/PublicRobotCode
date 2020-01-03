cmake_minimum_required (VERSION 3.5)

project (Logger)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads)
find_package(ntcore REQUIRED)
find_package(wpiutil REQUIRED)

find_package(PkgConfig)
pkg_check_modules(LOG4CXX REQUIRED liblog4cxx)
pkg_search_module(SQLite3 REQUIRED sqlite3)

include_directories(
  /usr/local/wpilib/include
  /usr/local/wpilib/include/wpiutil
  /usr/local/wpilib/include/ntcore
  include
  ${SQLite3_INCLUDE_DIRS}
  ${CMAKE_CURRENT_LIST_DIR}/SQLiteCpp/include
)

add_executable(logger 
    src/main.cpp
    src/database.cpp
)

target_link_libraries(logger
    ${LOG4CXX_LIBRARIES}
    ${SQLite3_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
    ntcore
    wpiutil
    gflags::gflags
    SQLiteCpp
    sqlite3
)

install(TARGETS logger DESTINATION bin)
install(FILES config/logger.config DESTINATION config/Logger)

#get_cmake_property(_variableNames VARIABLES)
#list (SORT _variableNames)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()
