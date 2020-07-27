#include "LogRegistery.hpp"

// Early instantiation
LogRegistery *LogRegistery::m_singelton_registery = new LogRegistery();
std::unordered_map<const char *, std::pair<ILWSLogger *, unsigned short>>
    LogRegistery::m_registery; // what would be the diff if i put it as a member var and not static
std::list<std::unordered_map<const char *, std::pair<ILWSLogger *, unsigned short>>::iterator>
    LogRegistery::m_map_insertion_order;
ILWSLogger *LogRegistery::m_default_logger;
LogRegistery::LogRegistery() {}
LogRegistery *LogRegistery::getInstance() { return m_singelton_registery; }
ILWSLogger *LogRegistery::getRegisteredLogger(const char *logger_name) {
    if (LogRegistery::m_registery.find(logger_name) != LogRegistery::m_registery.end()) {
        return LogRegistery::m_registery[logger_name].first;
    } else {
        // throw an exception
        throw std::runtime_error("Logger was not found in registery");
        return NULL;
    }
}
ILWSLogger *LogRegistery::getRegisteredLoggerByIndex(short registery_idx) {
    for (std::list<std::unordered_map<const char *, std::pair<ILWSLogger *, unsigned short>>::iterator>::iterator
             searcher_it = LogRegistery::m_map_insertion_order.begin();
         searcher_it != LogRegistery::m_map_insertion_order.end(); ++searcher_it, --registery_idx) {
        if (registery_idx == 0)
            return (*searcher_it)->second.first;
    }
    throw std::runtime_error("Logger was not found in registery");
    return NULL;
}
ILWSLogger *LogRegistery::getDefaultLogger() {
    if (LogRegistery::m_default_logger != NULL) {
        return m_default_logger;
    }
    throw std::runtime_error("No Loggers were not found in registery");
    return NULL;
}
bool LogRegistery::registerLogger(const char *logger_name, ILWSLogger *to_be_registered_logger) {
    if (LogRegistery::m_map_insertion_order.size() >= LogRegistery::m_max_entries_count) {
        // throw max entries reached.
        throw std::runtime_error("Logger Registery Max. entries were reached");
        return false;
    }
    if (LogRegistery::m_registery.find(logger_name) == LogRegistery::m_registery.end()) {
        LogRegistery::m_map_insertion_order.push_back(
            m_registery
                .insert(std::make_pair(logger_name, std::make_pair(to_be_registered_logger, m_map_insertion_order.size())))
                .first);
        // first logger to be inserted
        if (m_map_insertion_order.size() == 1)
            LogRegistery::m_default_logger = (*m_map_insertion_order.begin())->second.first;
        return true;
    } else {
        throw std::runtime_error("A logger with this ID already exists");
        return false;
    }
}
bool LogRegistery::unRegisterLogger(const char *logger_name) {
    std::unordered_map<const char *, std::pair<ILWSLogger *, unsigned short>>::iterator searcher_it =
        LogRegistery::m_registery.find(logger_name);
    if (searcher_it != LogRegistery::m_registery.end()) {
        LogRegistery::unRegisterLoggerByIndex(searcher_it->second.second);
        return true;
    } else {
        // should i throw an exception?
        return false;
    }
}
bool LogRegistery::unRegisterLoggerByIndex(short registery_idx) {
    for (std::list<std::unordered_map<const char *, std::pair<ILWSLogger *, unsigned short>>::iterator>::iterator
             searcher_it = LogRegistery::m_map_insertion_order.begin();
         searcher_it != LogRegistery::m_map_insertion_order.end(); ++searcher_it, --registery_idx) {
        if (registery_idx == 0) {
            // erase from map and list
            LogRegistery::m_registery.erase((*searcher_it));
            LogRegistery::m_map_insertion_order.erase(searcher_it);
            // update default logger
            LogRegistery::m_default_logger = (m_map_insertion_order.begin() == m_map_insertion_order.end())
                                                 ? NULL
                                                 : (*m_map_insertion_order.begin())->second.first;
            return true;
        }
    }
    // throw an exception logger not found
    throw std::runtime_error("Logger was not found in registery");
    return false;
}
