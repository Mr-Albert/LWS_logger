#include "SimpleLogger.hpp"
#include "LogRegistery.hpp"
#include <chrono> // for high_resolution_clock
#include <fstream>
#include <iostream>

// stupid factorial
unsigned long long stupid_factorial(unsigned long long input) {
    LOG_LWS_CRITICAL("simple_file", "Entered stupid factorial\n");
    LOG_LWS_CRITICAL("Entered stupid factorial with default logger\n");
    LOG_LWS_ALERT("simple_file", "Before base condition\n");
    LOG_LWS_ALERT("Before base condiiton with default logger\n");
    if (input == 1)
        return input;
    LOG_LWS_INFO("simple_file", "After base condition\n");
    LOG_LWS_INFO("After base condition with default logger\n");
    LOG_LWS_NOTICE("simple_file", "Before recursive call\n");
    LOG_LWS_NOTICE("Before recursive call with default logger\n");
    unsigned long long stupid_var = input * stupid_factorial(input - 1);
    LOG_LWS_WARNING("simple_file", "After recursive call\n");
    LOG_LWS_WARNING("After recursive call with default logger\n");
    LOG_LWS_ERROR("simple_file", "Before return\n");
    LOG_LWS_ERROR("Before return with default logger\n");
    LOG_LWS_EMERGENCY("simple_file", "Exiting stupid_factorial\n");
    LOG_LWS_EMERGENCY("Exiting stupid_factorial with default logger\n");
    return stupid_var;
}
unsigned long long stupid_fibonecci(unsigned long long input) {
    LOG_LWS_CRITICAL("simple_file", "Entered stupid_fibonecci\n");
    LOG_LWS_CRITICAL("Entered stupid_fibonecci  with default logger\n");
    LOG_LWS_ALERT("simple_file", "Before base condition\n");
    LOG_LWS_ALERT("Before base condiiton with default logger\n");
    if (input <= 1)
        return 1;
    LOG_LWS_INFO("simple_file", "After base condition\n");
    LOG_LWS_INFO("After base condition with default logger\n");
    LOG_LWS_NOTICE("simple_file", "Before recursive call\n");
    LOG_LWS_NOTICE("Before recursive call with default logger\n");
    unsigned long long stupid_var = stupid_fibonecci(input - 2) + stupid_fibonecci(input - 1);
    LOG_LWS_WARNING("simple_file", "After recursive call\n");
    LOG_LWS_WARNING("After recursive call with default logger\n");
    LOG_LWS_ERROR("simple_file", "Before return\n");
    LOG_LWS_ERROR("Before return with default logger\n");
    LOG_LWS_EMERGENCY("simple_file", "Exiting stupid_fibonecci\n");
    LOG_LWS_EMERGENCY("Exiting stupid_fibonecci with default logger\n");
    return stupid_var;
}
int main(int argc, char **argv) {
    std::fstream *simple_default_file = new std::fstream("simple_default_file.log", std::fstream::out);
    std::fstream *simple_file = new std::fstream("simple_file.log", std::fstream::out);
#ifdef LWS_LOGGING_ENABLED
    SimpleLogger *test_default_logger = new SimpleLogger(simple_default_file);
    SimpleLogger *test_logger = new SimpleLogger(simple_file);
    LogRegistery::getInstance()->registerLogger("simple_default_file", test_default_logger);
    LogRegistery::getInstance()->registerLogger("simple_file", test_logger);
#endif
    auto start = std::chrono::high_resolution_clock::now();
    LOG_LWS_DEBUG("simple_file", "Before Entering stupid factorial\n");
    LOG_LWS_DEBUG("Before Entering stupid factorial with default logger\n");
    stupid_factorial(atol(argv[1]));
    LOG_LWS_DEBUG("simple_file", "After exiting stupid factorial\n");
    LOG_LWS_DEBUG("After exiting stupid factorial with default logger\n");

    LOG_LWS_DEBUG("simple_file", "Before Entering stupid_fibonecci\n");
    LOG_LWS_DEBUG("Before Entering stupid_fibonecci with default logger\n");
    stupid_fibonecci(atol(argv[1]));
    LOG_LWS_DEBUG("simple_file", "After exiting stupid_fibonecci\n");
    LOG_LWS_DEBUG("After exiting stupid_fibonecci with default logger\n");
    delete simple_default_file;
    delete simple_file;
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << elapsed.count() << std::endl;

    return 0;
}