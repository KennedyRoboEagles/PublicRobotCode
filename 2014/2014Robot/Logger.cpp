/**
 * Team 3132
 * Logger.h
 * 
 * This class is a simple logging interface. The log filename is specified in the constructor
 * and uses a timestamp to identify the files.
 * 
 * This class uses C functions and not C++ IO, for no real reason, other than it was easier for
 * me to write quickly.
 */        
#include "Logger.h"
#include <time.h>
#include <stdarg.h>
#include <stdio.h>


Logger* Logger::m_instance = NULL;

Logger::Logger()
{
   SetIsLogging(true);
   // Determine the filename
   time_t currentTime = time(NULL);
   struct tm *theTime = localtime(&currentTime);
   
   // Create a filename
   // Format of the filename is "Log-dd-mm-yyyy-hh.mm.ss.txt"
   char filename[28] = {'\0'};
   
   // Print the filename into the string
   sprintf(filename, "Log-%02d-%02d-%4d-%02d.%02d.%02d.txt\0", theTime->tm_mday, (theTime->tm_mon + 1), (theTime->tm_year + 1900), 
            theTime->tm_hour, theTime->tm_min, theTime->tm_sec);
   
   // Open the file to write to
   m_logFile = fopen(filename, "w");
   
   // Print a header into the file
   if (m_logFile != NULL)
   {
      fprintf(m_logFile, "New log started at %s", asctime(theTime));
      fprintf(m_logFile, "-------------------------------------------------------------\n");
   }
}

Logger::~Logger()
{
   // Close file
   if (m_logFile != NULL)
   {
      fflush(m_logFile);
      fclose(m_logFile);
   }
   
   // Set reference to null
   m_logFile = NULL;
}

void Logger::Log(MessageType type, const char* message, ...)
{
   if (m_logFile != NULL && IsLogging())
   {
      // First print the message type
      switch (type)
      {
      case kERROR:
         fprintf(m_logFile, "ERROR\t");
         break;
      case kWARNING:
         fprintf(m_logFile, "WARN\t");
         break;
      case kINFO:
         fprintf(m_logFile, "INFO\t");
         break;
      default:
         fprintf(m_logFile, "INFO\t");
         break;
      }
      
      va_list args;
      va_start(args, message);
      
      // Write to the file
      vfprintf(m_logFile, message, args);
      fprintf(m_logFile, "\n");
      
      va_end(args);
      
      fflush(m_logFile);
   }
}

void Logger::SetIsLogging(bool isLogging)
{
   m_isLogging = isLogging;
}

bool Logger::IsLogging()
{
   return m_isLogging;
}

Logger* Logger::GetInstance()
{
   if (m_instance == NULL)
   {
      m_instance = new Logger();
   }
   
   return m_instance;
}

