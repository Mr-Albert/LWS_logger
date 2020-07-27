#ifndef HASHLOGGER_H
#define HASHLOGGER_H

#include "ILWSLogger.hpp"
#include <ostream>
#include <unordered_map>
class HashLogger : public ILWSLogger {
  private:
    static std::unordered_map<const char *, unsigned int> m_symbol_map;
    static unsigned int m_count_hash;

  public:
    HashLogger(std::ostream *private_stream);
    void log(const char *debug_level, unsigned int line, const char *file, const char *msg);
    unsigned int HashLogger::do_get_hash(const char *key);
    void HashLogger::log_variable_msg(const char *var_msg);
    void flush();
    virtual ~HashLogger();
};

#endif