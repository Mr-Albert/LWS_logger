#include "HashLogger.hpp"
static std::unordered_map<const char *, unsigned int> m_symbol_map;
static unsigned int count_hash;
HashLogger::HashLogger(std::ostream *param_ostream) : ILWSLogger(param_ostream) {}

void HashLogger::log(const char *debug_level, unsigned int line, const char *file, const char *msg) {
    char *buff;
    itoa(line, buff, 10);
    (*m_protected_ostream) << do_get_hash(debug_level) << " " << do_get_hash(" | ") << " " << do_get_hash(file) << " "
                           << do_get_hash(":") << " " << do_get_hash(buff) << " " << do_get_hash(" | ") << " ";
    log_variable_msg(msg);
    (*m_protected_ostream) << do_get_hash("\n") << " ";
}

void HashLogger::flush() { m_protected_ostream->flush(); }

unsigned int HashLogger::do_get_hash(const char *key) {
    if (HashLogger::m_symbol_map.find(key) != HashLogger::m_symbol_map.end()) {
        HashLogger::m_symbol_map[key] = HashLogger::m_count_hash++;
        return HashLogger::m_count_hash - 1;
    }
    return HashLogger::m_symbol_map[key];
}

void HashLogger::log_variable_msg(const char *var_msg) {
    // split on spaces and append each symbol hash to the ostream
    const char *next_word;
    while (next_word = get_next_word(var_msg, r_current_idx) && next_word) {
        (*m_protected_ostream) << do_get_hash(next_word) << " ";
    }
}

HashLogger::~HashLogger() { this->flush(); }
