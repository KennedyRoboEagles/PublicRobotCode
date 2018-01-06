/*
 * Logger.h
 *
 *  Created on: Jan 28, 2017
 *      Author: steve
 */

#ifndef SRC_UTIL_LOGGER_H_
#define SRC_UTIL_LOGGER_H_

#include <cstdio>
#include <string>

/**
 * @author Patrick Fairbank
 *
 * Class for writing to a log file on the cRIO's filesystem.
 */
class Logger {
 public:
  /**
   * Constructor.
   * @param filename The file path on the cRIO to log to
   * @param loggingInterval Only log once per this many lines to reduce verbosity (optional)
   */
  Logger(const char* filename, int loggingInterval = 1);

  virtual ~Logger();

  /**
   * Writes the given output to the log. Uses printf syntax.
   */
  void Log(const char* format, ...);

  /**
   * Empties the log file of data.
   */
  void ClearLog();

  /**
   * Returns the Logger of the entire system.
   *
   * Instantiates the Logger instance if not yet defined. Writes output
   * to file "robot.log".
   * @return static system Logger instance
   */
  static Logger* GetSysLog();

 private:
  FILE* logfile_;
  int loggingInterval_;
  int intervalCounter_;
  std::string filename_;
  static Logger* instance_;
};

#endif /* SRC_UTIL_LOGGER_H_ */
