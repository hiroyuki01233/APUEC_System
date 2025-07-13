#ifndef TASK4_LOGGER_HPP
#define TASK4_LOGGER_HPP

#include "../shared/Stack.hpp"
#include "../shared/Queue.hpp"
#include <string>

class Task4_Logger {
public:
    Task4_Logger();
    ~Task4_Logger();
    
    void logMatchResult();
    void viewRecentResults();
    void exportStatistics();
    void generateReport();
};

#endif