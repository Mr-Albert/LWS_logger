#ifndef ILWSLOGGER_H
#define ILWSLOGGER_H

#include <ostream>
// severity levels, following sysLog conventions
#define LWS_EMERGENCY 0
#define LWS_ALERT 1
#define LWS_CRITICAL 2
#define LWS_ERROR 3
#define LWS_WARNING 4
#define LWS_NOTICE 5
#define LWS_INFO 6
#define LWS_DEBUG 7
#ifndef LWS_LOG_LEVEL
#define LWS_LOG_LEVEL 8 // no logging
#endif
#ifndef LWS_LOG_LEVEL_SPECIFIC
#define LWS_LOG_LEVEL_SPECIFIC 8 // no specific level
#endif
#if LWS_LOG_LEVEL_SPECIFIC < 8 || LWS_LOG_LEVEL < 8
#define LWS_LOGGING_ENABLED // logging is enabled
#endif
// logger macros
#define GET_MACRO(_1, _2, NAME, ...) NAME // allows overloading of macros on number of parameters(max 2 params allowed)
#if LWS_LOG_LEVEL <= LWS_DEBUG || LWS_LOG_LEVEL_SPECIFIC == LWS_DEBUG
#define LOG_LWS_DEBUG(...) GET_MACRO(__VA_ARGS__, LOG_LWS_DEBUG2, LOG_LWS_DEBUG1)(__VA_ARGS__)
#define LOG_LWS_DEBUG2(log_entry, msg)                                                                                      \
    LogRegistery::getInstance()->getRegisteredLogger(log_entry)->log("debug", __LINE__, __FILE__, msg);
#define LOG_LWS_DEBUG1(msg)                                                                                                 \
    LogRegistery::getInstance()->getDefaultLogger()->log("debug", __LINE__, __FILE__, msg); // default logger
#else
#define LOG_LWS_DEBUG(...)
#endif
#if LWS_LOG_LEVEL <= LWS_INFO || LWS_LOG_LEVEL_SPECIFIC == LWS_INFO
#define LOG_LWS_INFO(...) GET_MACRO(__VA_ARGS__, LOG_LWS_INFO2, LOG_LWS_INFO1)(__VA_ARGS__)
#define LOG_LWS_INFO2(log_entry, msg)                                                                                       \
    LogRegistery::getInstance()->getRegisteredLogger(log_entry)->log("info", __LINE__, __FILE__, msg);
#define LOG_LWS_INFO1(msg) LogRegistery::getInstance()->getDefaultLogger()->log("info", __LINE__, __FILE__, msg);
#else
#define LOG_LWS_INFO(...)
#endif
#if LWS_LOG_LEVEL <= LWS_NOTICE || LWS_LOG_LEVEL_SPECIFIC == LWS_NOTICE
#define LOG_LWS_NOTICE(...) GET_MACRO(__VA_ARGS__, LOG_LWS_NOTICE2, LOG_LWS_NOTICE1)(__VA_ARGS__)
#define LOG_LWS_NOTICE2(log_entry, msg)                                                                                     \
    LogRegistery::getInstance()->getRegisteredLogger(log_entry)->log("notice", __LINE__, __FILE__, msg);
#define LOG_LWS_NOTICE1(msg) LogRegistery::getInstance()->getDefaultLogger()->log("notice", __LINE__, __FILE__, msg);
#else
#define LOG_LWS_NOTICE(...)
#endif
#if LWS_LOG_LEVEL <= LWS_WARNING || LWS_LOG_LEVEL_SPECIFIC == LWS_WARNING
#define LOG_LWS_WARNING(...) GET_MACRO(__VA_ARGS__, LOG_LWS_WARNING2, LOG_LWS_WARNING1)(__VA_ARGS__)
#define LOG_LWS_WARNING2(log_entry, msg)                                                                                    \
    LogRegistery::getInstance()->getRegisteredLogger(log_entry)->log("warning", __LINE__, __FILE__, msg);
#define LOG_LWS_WARNING1(msg) LogRegistery::getInstance()->getDefaultLogger()->log("warning", __LINE__, __FILE__, msg);
#else
#define LOG_LWS_WARNING(...)
#endif
#if LWS_LOG_LEVEL <= LWS_ERROR || LWS_LOG_LEVEL_SPECIFIC == LWS_ERROR
#define LOG_LWS_ERROR(...) GET_MACRO(__VA_ARGS__, LOG_LWS_ERROR2, LOG_LWS_ERROR1)(__VA_ARGS__)
#define LOG_LWS_ERROR2(log_entry, msg)                                                                                      \
    LogRegistery::getInstance()->getRegisteredLogger(log_entry)->log("error", __LINE__, __FILE__, msg);
#define LOG_LWS_ERROR1(msg) LogRegistery::getInstance()->getDefaultLogger()->log("error", __LINE__, __FILE__, msg);
#else
#define LOG_LWS_ERROR(...)
#endif
#if LWS_LOG_LEVEL <= LWS_CRITICAL || LWS_LOG_LEVEL_SPECIFIC == LWS_CRITICAL
#define LOG_LWS_CRITICAL(...) GET_MACRO(__VA_ARGS__, LOG_LWS_CRITICAL2, LOG_LWS_CRITICAL1)(__VA_ARGS__)
#define LOG_LWS_CRITICAL2(log_entry, msg)                                                                                   \
    LogRegistery::getInstance()->getRegisteredLogger(log_entry)->log("critical", __LINE__, __FILE__, msg);
#define LOG_LWS_CRITICAL1(msg) LogRegistery::getInstance()->getDefaultLogger()->log("critical", __LINE__, __FILE__, msg);
#else
#define LOG_LWS_CRITICAL(...)
#endif
#if LWS_LOG_LEVEL <= LWS_ALERT || LWS_LOG_LEVEL_SPECIFIC == LWS_ALERT
#define LOG_LWS_ALERT(...) GET_MACRO(__VA_ARGS__, LOG_LWS_ALERT2, LOG_LWS_ALERT1)(__VA_ARGS__)
#define LOG_LWS_ALERT2(log_entry, msg)                                                                                      \
    LogRegistery::getInstance()->getRegisteredLogger(log_entry)->log("alert", __LINE__, __FILE__, msg);
#define LOG_LWS_ALERT1(msg) LogRegistery::getInstance()->getDefaultLogger()->log("alert", __LINE__, __FILE__, msg);
#else
#define LOG_LWS_ALERT(...)
#endif
#if LWS_LOG_LEVEL <= LWS_EMERGENCY || LWS_LOG_LEVEL_SPECIFIC == LWS_EMERGENCY
#define LOG_LWS_EMERGENCY(...) GET_MACRO(__VA_ARGS__, LOG_LWS_EMERGENCY2, LOG_LWS_EMERGENCY1)(__VA_ARGS__)
#define LOG_LWS_EMERGENCY2(log_entry, msg)                                                                                  \
    LogRegistery::getInstance()->getRegisteredLogger(log_entry)->log("emergency", __LINE__, __FILE__, msg);
#define LOG_LWS_EMERGENCY1(msg) LogRegistery::getInstance()->getDefaultLogger()->log("emergency", __LINE__, __FILE__, msg);
#else
#define LOG_LWS_EMERGENCY(...)
#endif

class ILWSLogger {
  protected:
    std::ostream *m_protected_ostream;

  public:
    ILWSLogger(std::ostream *param_ostream);
    virtual void log(const char *debug_level, unsigned int line, const char *file, const char *msg) = 0;
    virtual void flush() = 0;
    virtual ~ILWSLogger();
};

#endif