#ifndef SIMPLELOGGER_H
#define SIMPLELOGGER_H
#include "ILWSLogger.hpp"
#include <ostream>
class SimpleLogger : public ILWSLogger {
  public:
    SimpleLogger(std::ostream *private_stream);
    void log(const char *debug_level, unsigned int line, const char *file, const char *msg);
    void flush();
    virtual ~SimpleLogger();
};
#endif