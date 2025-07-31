// File: Task4_Logger.cpp
#include "Task4_Logger.hpp"

// Default constructor: uses default Queue ctor
Task4_Logger::Task4_Logger()
  : recentQueue() {
}

Task4_Logger::~Task4_Logger() {
    // Clean up all PerformanceEntry objects
    LinkedList<int> keys = perfMap.keys();
    for (int i = 0; i < keys.getSize(); ++i) {
        delete perfMap[keys[i]];
    }
}

PerformanceEntry* Task4_Logger::getEntry(Player* p) {
    int id = p->getPlayerID();
    if (!perfMap.contains(id)) {
        perfMap[id] = new PerformanceEntry(p);
    }
    return perfMap[id];
}

void Task4_Logger::logMatchResult(Match* m) {
    recentQueue.enqueue(m);
    if (m->winner) {
        getEntry(m->winner)->wins++;
        Player* loser = (m->winner == m->player1) ? m->player2 : m->player1;
        getEntry(loser)->losses++;
    }
}

void Task4_Logger::viewRecentResults() const {
    std::cout << "\n=== RECENT MATCHES ===\n";
    if (recentQueue.isEmpty()) {
        std::cout << "  [No matches recorded]\n";
        return;
    }
    Queue<Match*> copy = recentQueue;
    while (!copy.isEmpty()) {
        Match* m = copy.dequeue();
        std::cout
          << "  #" << m->matchID
          << " [" << m->stage << "] "
          << m->player1->getName() << " vs "
          << m->player2->getName()
          << " -> Winner: " << m->winner->getName()
          << "\n";
    }
}

void Task4_Logger::exportStatistics(const std::string& filename) {
    std::ofstream ofs(filename);
    if (!ofs) {
        std::cerr << "Error: cannot open " << filename << "\n";
        return;
    }
    ofs << "=== PLAYER STATISTICS ===\n";
    LinkedList<int> keys = perfMap.keys();
    for (int i = 0; i < keys.getSize(); ++i) {
        PerformanceEntry* e = perfMap[keys[i]];
        ofs << e->player->getName()
            << " | Wins: " << e->wins
            << " | Losses: " << e->losses
            << "\n";
    }
    std::cout << "Statistics exported to " << filename << "\n";
}

void Task4_Logger::generateReport(const std::string& filename) {
    std::ofstream ofs(filename);
    if (!ofs) {
        std::cerr << "Error: cannot open " << filename << "\n";
        return;
    }
    ofs << "APUEC FULL GAME REPORT\n\n";
    ofs << "--- RECENT MATCHES ---\n";
    Queue<Match*> copy = recentQueue;
    while (!copy.isEmpty()) {
        Match* m = copy.dequeue();
        ofs << "Match #" << m->matchID
            << " [" << m->stage << "] "
            << m->player1->getName() << " vs "
            << m->player2->getName()
            << " -> Winner: " << m->winner->getName()
            << "\n";
    }
    ofs << "\n--- PLAYER STATISTICS ---\n";
    LinkedList<int> keys2 = perfMap.keys();
    for (int i = 0; i < keys2.getSize(); ++i) {
        PerformanceEntry* e = perfMap[keys2[i]];
        ofs << e->player->getName()
            << " | Wins: " << e->wins
            << " | Losses: " << e->losses
            << "\n";
    }
    std::cout << "Report generated at " << filename << "\n";
}

