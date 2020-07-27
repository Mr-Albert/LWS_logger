#include "HashLogger.hpp"
#include "LogRegistery.hpp"
#include <fstream>
#include <iostream>

// stupid factorial
int stupid_factorial(int input) {
    LOG_LWS_CRITICAL("hash_default_file", "Entered stupid factorial\n");
    LOG_LWS_CRITICAL("Entered stupid factorial with default logger\n");
    LOG_LWS_ALERT("hash_default_file", "Before base condiiton\n");
    LOG_LWS_ALERT("Before base condiiton with default logger\n");
    if (input == 1)
        return input;
    LOG_LWS_INFO("hash_default_file", "After base condition\n");
    LOG_LWS_INFO("After base condition with default logger\n");
    LOG_LWS_NOTICE("hash_default_file", "Before recursive call\n");
    LOG_LWS_NOTICE("Before recursive call with default logger\n");
    int stupid_var = input * stupid_factorial(input - 1);
    LOG_LWS_WARNING("hash_default_file", "After recursive call\n");
    LOG_LWS_WARNING("After recursive call with default logger\n");
    LOG_LWS_ERROR("hash_default_file", "Before return\n");
    LOG_LWS_ERROR("Before return with default logger\n");
    LOG_LWS_EMERGENCY("hash_default_file", "Exiting stupid_factorial\n");
    LOG_LWS_EMERGENCY("Exiting stupid_factorial with default logger\n");
    return stupid_var;
}

int main(int argc, char **argv) {
    std::fstream *hash_default_file = new std::fstream("hash_default_file.log", std::fstream::out);
    std::fstream *hash_file = new std::fstream("hash_file.log", std::fstream::out);
#ifdef LWS_LOGGING_ENABLED
    SimpleLogger *test_default_logger = new HashLogger(hash_default_file);
    SimpleLogger *test_logger = new HashLogger(hash_file);
    LogRegistery::getInstance()->registerLogger("hash_default_file", test_default_logger);
    LogRegistery::getInstance()->registerLogger("hash_file", test_logger);
#endif
    LOG_LWS_DEBUG("hash_default_file", "Before Entering stupid factorial\n");
    LOG_LWS_DEBUG("Before Entering stupid factorial with default logger\n");
    std::cout << stupid_factorial(atoi(argv[1])) << std::endl;
    LOG_LWS_DEBUG("hash_default_file", "After exiting stupid factorial\n");
    LOG_LWS_DEBUG("After exiting stupid factorial with default logger\n");
    return 0;
}