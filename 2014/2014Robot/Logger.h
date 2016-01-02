/**
 * Team 3132
 * Logger.h
 * 
 * This class is a simple logging interface.
 */        
#ifndef LOGGER_H_
#define LOGGER_H_

#include <stdio.h>

class Logger
{
public:
   typedef enum 
   {
      kERROR = 0, 
      kWARNING = 1, 
      kINFO = 2
   } MessageType;
   
   static Logger* GetInstance();
   virtual ~Logger();
   
   void Log(MessageType type, const char* message, ...);
   void SetIsLogging(bool isLogging);
   bool IsLogging();

protected:
   Logger();
   
private:
   static Logger *m_instance;
   FILE *m_logFile;
   bool m_isLogging;
};


#endif
