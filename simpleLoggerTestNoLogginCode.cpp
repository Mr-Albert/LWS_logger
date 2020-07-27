#include "LogRegistery.hpp"
#include "SimpleLogger.hpp"
#include <chrono> // for high_resolution_clock
#include <fstream>
#include <iostream>
// stupid factorial
unsigned long long stupid_factorial(unsigned long long input) {
    if (input == 1)
        return input;
    unsigned long long stupid_var = input * stupid_factorial(input - 1);
    return stupid_var;
}
unsigned long long stupid_fibonecci(unsigned long long input) {
    if (input <= 1)
        return 1;
    unsigned long long stupid_var = stupid_fibonecci(input - 2) + stupid_fibonecci(input - 1);
    return stupid_var;
}
int main(int argc, char **argv) {
    std::fstream *simple_default_file = new std::fstream("simple_default_file.log", std::fstream::out);
    std::fstream *simple_file = new std::fstream("simple_file.log", std::fstream::out);
    auto start = std::chrono::high_resolution_clock::now();
    stupid_factorial(atol(argv[1]));
    stupid_fibonecci(atol(argv[1]));
    delete simple_default_file;
    delete simple_file;
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << elapsed.count() << std::endl;
    return 0;
}