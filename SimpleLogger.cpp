#include "SimpleLogger.hpp"
SimpleLogger::SimpleLogger(std::ostream *param_ostream) : ILWSLogger(param_ostream) {}
void SimpleLogger::log(const char *debug_level, unsigned int line, const char *file, const char *msg) {
    (*m_protected_ostream) << debug_level << " | " << file << ":" << line << " | " << msg << "\n";
}
void SimpleLogger::flush() { m_protected_ostream->flush(); }
SimpleLogger::~SimpleLogger() { this->flush(); }
