#include "../../include/base/logger.hpp"
#include <fstream>
#include <chrono>


namespace clim{
namespace base{

char *Logger::logLevelToString(Logger::LogLevel log){
    switch(log){
    case VERBOSE:
        return "Verbose: ";
        break;
    case LOG:
        return "Log: ";
        break;
    case WARNING:
        return "Warning: ";
        break;
    case CRITICAL:
        return "Critical: ";
        break;
    case ERROR:
        return "Error: ";
        break;
    default:
        return "Default:";
        break;
    }
}

Logger::Logger():m_fileName("DefaultLog.txt")
{
   m_stream = new std::ofstream;
   m_stream->open(m_fileName,std::ios_base::out |std::ios_base::app);

}

Logger::Logger(const char *filename): m_fileName(filename)
{
    m_stream = new std::ofstream;
    m_stream->open(filename,std::ios_base::out |std::ios_base::app);
}

Logger::Logger(const char *filename, Logger::FileAttr attributes):m_fileName(filename)
{
        m_stream = new std::ofstream;
        switch(attributes){
        case APPEND:
            m_stream->open(filename,std::ios_base::out | std::ios_base::app);
            break;
        case OVERWRITE:
            m_stream->open(filename,std::ios_base::out |std::ios_base::trunc);
            break;
        case FROMEND:
            m_stream->open(filename,std::ios_base::out |std::ios_base::ate);
        default:
            break;
        }
}

Logger::~Logger()
{
    m_stream->close();
    delete m_stream;
}

void Logger::write(const char *message, Logger::LogLevel level)
{
    std::time_t time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    *m_stream << logLevelToString(level) << std::endl << "\t" << message << std::endl << "\t" << std::ctime(&time);
}



}
}
