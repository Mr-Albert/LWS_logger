#ifndef LOGREGISTERY_H
#define LOGREGISTERY_H

#include "ILWSLogger.hpp"
#include <list>
#include <unordered_map>
/** A singlton registery of logs
 * This LogRegistery registery-singleton implementation follows the singelton early instantiation principle
 *  as the getInstance() function will be used in every macro call; an optimized version is needed, and thus
 *  it will not do any NULL checking nor object creation, and the singleton object will be created
 *  at application startup.
 */
class LogRegistery {
  private:
    // singleton instance
    static LogRegistery *m_singelton_registery;
    // bug; by design unordered map doesn't keep insertion order should use a diff solution or ditch all the *Byindex()
    // functions
    static std::unordered_map<const char *, std::pair<ILWSLogger *, unsigned short>>
        m_registery; // what would be the diff if i put it as a member var and not static
    // A list of std::unordered_map iterators to keep track of map-insertion ordering
    static std::list<std::unordered_map<const char *, std::pair<ILWSLogger *, unsigned short>>::iterator>
        m_map_insertion_order;
    // A ILWSLogger that gets saved during unregisteration or registration of new loggers instead of accessing the first
    // element from the list of loggers on every default logger request.
    static ILWSLogger *m_default_logger;
    // Registery limit
    static const short m_max_entries_count = 255; // a magic number, and not extendable
    LogRegistery();

  public:
    // Singelton getter
    static LogRegistery *getInstance();
    /** Gets the registered logger associated with the parameter logger_name
     *@param logger_name the logger name that the logger is identified by, it is recommended to have it the same as the
     *buffer/file name.
     */
    ILWSLogger *getRegisteredLogger(const char *logger_name);
    /** Gets the registery_idx'th registered logger, or the first (0'th) logger by default.
     *@param registery_idx the registery_idx'th registered logger , with 0-based index.
     */
    ILWSLogger *getRegisteredLoggerByIndex(short registery_idx = 0);
    /** Gets the default (the 0'th, or earliest inserted) logger.
     */
    ILWSLogger *getDefaultLogger();
    /** Registers a logger associating it with the parameter logger_name
     *@param logger_name the logger name that the logger is identified by, it is recommended to have it the same as the
     *buffer/file name.
     *@param to_be_registered_logger the logger instance to be saved in the registery.
     */
    bool registerLogger(const char *logger_name, ILWSLogger *to_be_registered_logger);
    /** un-registers the logger associated with the parameter logger_name
     *@param logger_name the logger name that the logger is identified by, it is recommended to have it the same as the
     *buffer/file name.
     */
    bool unRegisterLogger(const char *logger_name);
    /** un-registers the logger associated with the parameter logger_name
     *@param registery_idx the registery_idx'th registered logger , with 0-based index.
     */
    bool unRegisterLoggerByIndex(short registery_idx);
};

#endif