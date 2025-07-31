#ifndef TASK4_LOGGER_HPP
#define TASK4_LOGGER_HPP

#include "Task1_Scheduler.hpp"
#include "../shared/Queue.hpp"
#include "../shared/HashMap.hpp"
#include "../shared/LinkedList.hpp"
#include <string>
#include <iostream>
#include <fstream>

// Tracks wins/losses for a single player
struct PerformanceEntry {
    Player* player;
    int wins;
    int losses;
    PerformanceEntry(Player* p)
      : player(p), wins(0), losses(0) {}
};

// Logs completed matches and maintains player stats
class Task4_Logger {
private:
    Queue<Match*>                  recentQueue;  // circular buffer
    HashMap<int, PerformanceEntry*> perfMap;     // playerID → stats

    // get-or-create stats entry
    PerformanceEntry* getEntry(Player* p);

public:
    Task4_Logger();
    ~Task4_Logger();

    // Record a completed match
    void logMatchResult(Match* m);

    // Display the recent matches
    void viewRecentResults() const;

    // Export just win/loss stats
    void exportStatistics(const std::string& filename);

    // Export full report (matches + stats)
    void generateReport(const std::string& filename);
};

#endif // TASK4_LOGGER_HPP
