#include "Task2_Registration.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include <ctime>

// ANSI Color codes for terminal
const std::string RESET = "\033[0m";
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string BLUE = "\033[34m";
const std::string MAGENTA = "\033[35m";
const std::string CYAN = "\033[36m";
const std::string WHITE = "\033[37m";
const std::string BOLD = "\033[1m";

// Helper functions for enhanced UI
void printBorder(char pattern = '=', int length = 50) {
    std::cout << std::string(length, pattern) << std::endl;
}

void printDoubleBorder() {
    std::cout << "╔════════════════════════════════════════════════╗" << std::endl;
}

void printBottomBorder() {
    std::cout << "╚════════════════════════════════════════════════╝" << std::endl;
}

// Simple player registration without complex templates
std::vector<Player*> priorityPlayers;    // VIP, Early-bird, Wildcard
std::vector<Player*> regularPlayers;     // Regular registrations
std::vector<Player*> checkedInPlayers;   // Tournament participants
std::vector<Player*> waitingList;        // Replacement queue

int maxCapacity = 64;

Task2_Registration::Task2_Registration() {
    std::cout << GREEN << "🎮 Tournament Registration System initialized!" << RESET << std::endl;
}

Task2_Registration::~Task2_Registration() {
    // Destructor
}

void Task2_Registration::registerPlayer() {
    std::string playerIDStr, playerName, university, game;
    int priority;
    
    std::cout << "\n" << CYAN << BOLD << "🎮 PLAYER REGISTRATION" << RESET << std::endl;
    std::cout << CYAN;
    printBorder('=', 22);
    std::cout << RESET;
    
    std::cout << YELLOW << "Enter Player ID: " << WHITE;
    std::getline(std::cin, playerIDStr);
    
    std::cout << YELLOW << "Enter Player Name: " << WHITE;
    std::getline(std::cin, playerName);
    
    std::cout << YELLOW << "Enter University: " << WHITE;
    std::getline(std::cin, university);
    
    std::cout << YELLOW << "Enter Game: " << WHITE;
    std::getline(std::cin, game);
    
    std::cout << RESET << "\n" << BLUE << "Select Priority:" << RESET << std::endl;
    std::cout << RED << "1. VIP Player" << RESET << std::endl;
    std::cout << BLUE << "2. Early-bird Registration" << RESET << std::endl;
    std::cout << WHITE << "3. Regular Registration" << RESET << std::endl;
    std::cout << MAGENTA << "4. Wildcard Entry" << RESET << std::endl;
    std::cout << YELLOW << "Enter choice (1-4): " << WHITE;
    std::cin >> priority;
    std::cin.ignore();
    
    if (priority < 1 || priority > 4) {
        std::cout << YELLOW << "⚠️ Invalid priority. Setting to Regular (3)" << RESET << std::endl;
        priority = 3;
    }
    
    try {
        int playerID = std::stoi(playerIDStr);
        Player* newPlayer = new Player(playerID, playerName, university, game, priority);
        
        if (priority == 1 || priority == 2 || priority == 4) {
            // Priority players (VIP, Early-bird, Wildcard)
            priorityPlayers.push_back(newPlayer);
            std::string priorityName = (priority == 1) ? "VIP" : 
                                     (priority == 2) ? "Early-bird" : "Wildcard";
            std::cout << GREEN << "✅ " << playerName << " registered as " << MAGENTA << priorityName << GREEN << " player" << RESET << std::endl;
        } else {
            // Regular players
            regularPlayers.push_back(newPlayer);
            std::cout << GREEN << "✅ " << playerName << " registered as " << CYAN << "Regular" << GREEN << " player" << RESET << std::endl;
        }
        
    } catch (const std::exception& e) {
        std::cout << RED << "❌ Error: Invalid Player ID format" << RESET << std::endl;
    }
}

void Task2_Registration::checkInPlayer() {
    std::cout << "\n" << BLUE << BOLD << "🎯 Processing Check-ins..." << RESET << std::endl;
    std::cout << BLUE;
    printBorder('=', 43);
    std::cout << RESET;
    
    int processedCount = 0;
    
    // Process priority players first (VIP, Early-bird, Wildcard)
    for (size_t i = 0; i < priorityPlayers.size() && checkedInPlayers.size() < maxCapacity; i++) {
        Player* player = priorityPlayers[i];
        checkedInPlayers.push_back(player);
        processedCount++;
        
        std::string priorityName = (player->getRanking() == 1) ? RED + "VIP" + RESET : 
                                 (player->getRanking() == 2) ? BLUE + "Early-bird" + RESET : 
                                 MAGENTA + "Wildcard" + RESET;
        std::cout << GREEN << "✅ " << WHITE << player->getName() << GREEN << " (" << priorityName << GREEN << ") checked in successfully!" << RESET << std::endl;
    }
    priorityPlayers.clear(); // Clear processed priority players
    
    // Then process regular players
    for (size_t i = 0; i < regularPlayers.size() && checkedInPlayers.size() < maxCapacity; i++) {
        Player* player = regularPlayers[i];
        checkedInPlayers.push_back(player);
        processedCount++;
        std::cout << GREEN << "✅ " << WHITE << player->getName() << GREEN << " (" << CYAN << "Regular" << GREEN << ") checked in successfully!" << RESET << std::endl;
    }
    
    // Remaining regular players go to waiting list
    for (size_t i = checkedInPlayers.size() - processedCount + priorityPlayers.size(); 
         i < regularPlayers.size(); i++) {
        waitingList.push_back(regularPlayers[i]);
        std::cout << YELLOW << "⏳ " << WHITE << regularPlayers[i]->getName() << YELLOW << " moved to waiting list" << RESET << std::endl;
    }
    
    std::cout << BLUE;
    printBorder('=', 43);
    std::cout << RESET;
    std::cout << GREEN << BOLD << "✅ Check-in process completed!" << RESET << std::endl;
    std::cout << CYAN << "🏆 Processed " << YELLOW << BOLD << processedCount << RESET << CYAN << " players" << RESET << std::endl;
}

void Task2_Registration::handleWithdrawal() {
    if (checkedInPlayers.empty()) {
        std::cout << RED << "❌ No players are currently checked in." << RESET << std::endl;
        return;
    }
    
    std::cout << "\n" << MAGENTA << BOLD << "🔄 PLAYER WITHDRAWAL" << RESET << std::endl;
    std::cout << MAGENTA;
    printBorder('=', 19);
    std::cout << RESET;
    std::cout << CYAN << "Current checked-in players:" << RESET << std::endl;
    
    for (size_t i = 0; i < checkedInPlayers.size(); i++) {
        std::cout << YELLOW << (i+1) << ". " << WHITE << checkedInPlayers[i]->getName() 
                  << " (" << CYAN << checkedInPlayers[i]->getUniversity() << WHITE << ")" << RESET << std::endl;
    }
    
    std::cout << YELLOW << "Enter player number to withdraw (0 to cancel): " << WHITE;
    int choice;
    std::cin >> choice;
    std::cin.ignore();
    
    if (choice == 0) {
        std::cout << YELLOW << "❌ Withdrawal cancelled." << RESET << std::endl;
        return;
    }
    
    if (choice < 1 || choice > static_cast<int>(checkedInPlayers.size())) {
        std::cout << RED << "❌ Invalid player number." << RESET << std::endl;
        return;
    }
    
    std::string withdrawnPlayer = checkedInPlayers[choice-1]->getName();
    checkedInPlayers.erase(checkedInPlayers.begin() + (choice-1));
    std::cout << RED << "❌ " << WHITE << withdrawnPlayer << RED << " has withdrawn from the tournament" << RESET << std::endl;
    
    // Get replacement from waiting list if available
    if (!waitingList.empty()) {
        Player* replacement = waitingList.front();
        waitingList.erase(waitingList.begin());
        checkedInPlayers.push_back(replacement);
        std::cout << GREEN << "🔄 " << WHITE << replacement->getName() 
                  << GREEN << " has been moved from waiting list to tournament!" << RESET << std::endl;
    } else {
        std::cout << YELLOW << "⚠️ No replacement players available." << RESET << std::endl;
    }
}

void Task2_Registration::processWaitlist() {
    std::cout << "\n" << YELLOW << BOLD << "📋 WAITLIST PROCESSING" << RESET << std::endl;
    std::cout << YELLOW;
    printBorder('=', 22);
    std::cout << RESET;
    
    if (waitingList.empty()) {
        std::cout << YELLOW << "No players in waiting list." << RESET << std::endl;
        return;
    }
    
    std::cout << CYAN << "Current waiting list size: " << YELLOW << BOLD << waitingList.size() << RESET << std::endl;
    
    if (checkedInPlayers.size() < maxCapacity) {
        int availableSpots = maxCapacity - checkedInPlayers.size();
        std::cout << "\n" << GREEN << "Available tournament spots: " << YELLOW << BOLD << availableSpots << RESET << std::endl;
        std::cout << BLUE << "Move players from waiting list? (y/n): " << WHITE;
        
        char choice;
        std::cin >> choice;
        std::cin.ignore();
        
        if (choice == 'y' || choice == 'Y') {
            int moved = 0;
            while (!waitingList.empty() && 
                   checkedInPlayers.size() < maxCapacity && 
                   moved < availableSpots) {
                Player* player = waitingList.front();
                waitingList.erase(waitingList.begin());
                checkedInPlayers.push_back(player);
                std::cout << GREEN << "✅ " << WHITE << player->getName() << GREEN << " moved to tournament participants!" << RESET << std::endl;
                moved++;
            }
            std::cout << CYAN << "🎯 Moved " << YELLOW << BOLD << moved << RESET << CYAN << " players from waitlist to tournament." << RESET << std::endl;
        }
    } else {
        std::cout << RED << "🔒 Tournament is at full capacity." << RESET << std::endl;
    }
}

void Task2_Registration::displayRegistrationStatus() {
    std::cout << "\n" << BLUE << BOLD << "📊 TOURNAMENT REGISTRATION STATUS" << RESET << std::endl;
    printBorder('━', 50);
    
    std::cout << GREEN << "🏆 Tournament Capacity: " << YELLOW << BOLD << maxCapacity << RESET << std::endl;
    std::cout << GREEN << "✅ Checked-in Players: " << YELLOW << BOLD << checkedInPlayers.size() << RESET << std::endl;
    std::cout << MAGENTA << "🔥 Priority Players Waiting: " << YELLOW << BOLD << priorityPlayers.size() << RESET << std::endl;
    std::cout << CYAN << "⏰ Regular Players Waiting: " << YELLOW << BOLD << regularPlayers.size() << RESET << std::endl;
    std::cout << BLUE << "🔄 Waiting List: " << YELLOW << BOLD << waitingList.size() << RESET << std::endl;
    
    int remainingSpots = maxCapacity - checkedInPlayers.size();
    if (remainingSpots > 0) {
        std::cout << GREEN << "🎯 Remaining Tournament Spots: " << YELLOW << BOLD << remainingSpots << RESET << std::endl;
    } else {
        std::cout << RED << BOLD << "🔒 Tournament is FULL!" << RESET << std::endl;
    }
    
    printBorder('━', 50);
}

void Task2_Registration::displayAllQueues() {
    std::cout << "\n" << MAGENTA << BOLD << "📋 QUEUE SYSTEM STATUS" << RESET << std::endl;
    printBorder('▓', 50);
    
    // Priority Queue
    std::cout << "\n" << RED << BOLD << "🔥 Priority Queue (VIP/Early-bird/Wildcard):" << RESET << std::endl;
    if (priorityPlayers.empty()) {
        std::cout << "   " << YELLOW << "[Empty]" << RESET << std::endl;
    } else {
        std::cout << "   " << GREEN << "Players: " << YELLOW << BOLD << priorityPlayers.size() << RESET << std::endl;
        for (size_t i = 0; i < priorityPlayers.size(); i++) {
            Player* p = priorityPlayers[i];
            std::string priorityName = (p->getRanking() == 1) ? RED + "VIP" + RESET : 
                                     (p->getRanking() == 2) ? BLUE + "Early-bird" + RESET : 
                                     MAGENTA + "Wildcard" + RESET;
            std::cout << "   " << CYAN << "► " << WHITE << p->getName() 
                      << " (" << priorityName << ")" << RESET << std::endl;
        }
    }
    
    // Regular Queue
    std::cout << "\n" << BLUE << BOLD << "⏰ Regular Queue (FIFO):" << RESET << std::endl;
    if (regularPlayers.empty()) {
        std::cout << "   " << YELLOW << "[Empty]" << RESET << std::endl;
    } else {
        std::cout << "   " << GREEN << "Players: " << YELLOW << BOLD << regularPlayers.size() << RESET << std::endl;
        for (size_t i = 0; i < regularPlayers.size(); i++) {
            std::cout << "   " << CYAN << "► " << WHITE << regularPlayers[i]->getName() << RESET << std::endl;
        }
    }
    
    // Waiting List
    std::cout << "\n" << YELLOW << BOLD << "🔄 Waiting List (Circular Queue concept):" << RESET << std::endl;
    if (waitingList.empty()) {
        std::cout << "   " << YELLOW << "[Empty]" << RESET << std::endl;
    } else {
        std::cout << "   " << GREEN << "Players: " << YELLOW << BOLD << waitingList.size() << RESET << std::endl;
        for (size_t i = 0; i < waitingList.size(); i++) {
            std::cout << "   " << CYAN << "► " << WHITE << waitingList[i]->getName() << RESET << std::endl;
        }
    }
    
    printBorder('▓', 50);
}

void Task2_Registration::displayCheckedInPlayers() {
    std::cout << "\n" << GREEN << BOLD << "🏆 TOURNAMENT PARTICIPANTS" << RESET << std::endl;
    printBorder('═', 50);
    if (checkedInPlayers.empty()) {
        std::cout << YELLOW << "No players checked in yet." << RESET << std::endl;
    } else {
        for (size_t i = 0; i < checkedInPlayers.size(); i++) {
            Player* p = checkedInPlayers[i];
            std::cout << CYAN << (i+1) << ". " << WHITE << BOLD << p->getName() 
                      << RESET << " (" << BLUE << p->getUniversity() << RESET << ") - " 
                      << MAGENTA << p->getGame() << RESET << std::endl;
        }
    }
    std::cout << GREEN << "Total: " << YELLOW << BOLD << checkedInPlayers.size() << RESET << GREEN << " players" << RESET << std::endl;
    printBorder('═', 50);
}

void Task2_Registration::addSampleRegistrationData() {
    std::cout << CYAN << "📝 Adding sample registration data..." << RESET << std::endl;
    
    // VIP players
    Player* vip1 = new Player(1001, "ProGamer_Alex", "APU", "Valorant", 1);
    Player* vip2 = new Player(1002, "StreamerSarah", "UCSI", "League of Legends", 1);
    priorityPlayers.push_back(vip1);
    priorityPlayers.push_back(vip2);
    
    // Early-bird players
    Player* eb1 = new Player(2001, "EarlyBird_John", "MMU", "Dota 2", 2);
    Player* eb2 = new Player(2002, "QuickRegister_Lisa", "Taylor's", "CS:GO", 2);
    priorityPlayers.push_back(eb1);
    priorityPlayers.push_back(eb2);
    
    // Regular players
    Player* reg1 = new Player(3001, "RegularPlayer1", "UPM", "League of Legends", 3);
    Player* reg2 = new Player(3002, "RegularPlayer2", "UM", "Dota 2", 3);
    Player* reg3 = new Player(3003, "RegularPlayer3", "USM", "CS:GO", 3);
    regularPlayers.push_back(reg1);
    regularPlayers.push_back(reg2);
    regularPlayers.push_back(reg3);
    
    // Wildcard
    Player* wc1 = new Player(4001, "WildCard_Player", "UNITEN", "Dota 2", 4);
    priorityPlayers.push_back(wc1);
    
    std::cout << GREEN << "✅ Sample registration data added successfully!" << RESET << std::endl;
    std::cout << CYAN << "Added: " << RED << "2 VIP" << RESET << ", " << BLUE << "2 Early-bird" << RESET << ", " 
              << WHITE << "3 Regular" << RESET << ", " << MAGENTA << "1 Wildcard" << RESET << CYAN << " players" << RESET << std::endl;
}

void Task2_Registration::saveRegistrationData() {
    std::cout << "\n" << CYAN << BOLD << "💾 SAVE REGISTRATION DATA" << RESET << std::endl;
    std::cout << CYAN;
    printBorder('=', 25);
    std::cout << RESET;
    
    std::cout << YELLOW << "Enter filename to save (default: data/registration_log.txt): " << WHITE;
    std::string filename;
    std::getline(std::cin, filename);
    
    if (filename.empty()) {
        filename = "data/registration_log.txt";
    }
    
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << RED << "❌ Error opening file for writing: " << filename << RESET << std::endl;
        return;
    }
    
    // Get current time
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    
    // Write header
    file << "APUEC TOURNAMENT REGISTRATION LOG\n";
    file << "Generated: " << std::ctime(&time_t);
    file << "System Capacity: " << maxCapacity << " players\n";
    file << "========================================\n\n";
    
    // Save Priority Players (VIP, Early-bird, Wildcard)
    file << "=== PRIORITY REGISTRATION QUEUE ===\n";
    file << "Total Players: " << priorityPlayers.size() << "\n\n";
    for (size_t i = 0; i < priorityPlayers.size(); i++) {
        Player* p = priorityPlayers[i];
        std::string priorityName = (p->getRanking() == 1) ? "VIP" : 
                                 (p->getRanking() == 2) ? "Early-bird" : "Wildcard";
        file << "Player ID: " << p->getPlayerID() << "\n";
        file << "Name: " << p->getName() << "\n";
        file << "University: " << p->getUniversity() << "\n";
        file << "Game: " << p->getGame() << "\n";
        file << "Priority: " << priorityName << " (" << p->getRanking() << ")\n";
        file << "Status: Waiting for Check-in\n\n";
    }
    
    // Save Regular Players
    file << "=== REGULAR REGISTRATION QUEUE ===\n";
    file << "Total Players: " << regularPlayers.size() << "\n\n";
    for (size_t i = 0; i < regularPlayers.size(); i++) {
        Player* p = regularPlayers[i];
        file << "Player ID: " << p->getPlayerID() << "\n";
        file << "Name: " << p->getName() << "\n";
        file << "University: " << p->getUniversity() << "\n";
        file << "Game: " << p->getGame() << "\n";
        file << "Priority: Regular (3)\n";
        file << "Status: Waiting for Check-in\n\n";
    }
    
    // Save Checked-in Players
    file << "=== TOURNAMENT PARTICIPANTS ===\n";
    file << "Total Players: " << checkedInPlayers.size() << "\n\n";
    for (size_t i = 0; i < checkedInPlayers.size(); i++) {
        Player* p = checkedInPlayers[i];
        file << "Player ID: " << p->getPlayerID() << "\n";
        file << "Name: " << p->getName() << "\n";
        file << "University: " << p->getUniversity() << "\n";
        file << "Game: " << p->getGame() << "\n";
        file << "Status: CHECKED IN - Tournament Participant\n\n";
    }
    
    // Save Waiting List
    file << "=== WAITING LIST (REPLACEMENT QUEUE) ===\n";
    file << "Total Players: " << waitingList.size() << "\n\n";
    for (size_t i = 0; i < waitingList.size(); i++) {
        Player* p = waitingList[i];
        file << "Player ID: " << p->getPlayerID() << "\n";
        file << "Name: " << p->getName() << "\n";
        file << "University: " << p->getUniversity() << "\n";
        file << "Game: " << p->getGame() << "\n";
        file << "Status: Waiting List - Position " << (i+1) << "\n\n";
    }
    
    // Summary Statistics
    file << "=== REGISTRATION SUMMARY ===\n";
    file << "Priority Queue: " << priorityPlayers.size() << " players\n";
    file << "Regular Queue: " << regularPlayers.size() << " players\n";
    file << "Tournament Participants: " << checkedInPlayers.size() << " players\n";
    file << "Waiting List: " << waitingList.size() << " players\n";
    file << "Total Registered: " << (priorityPlayers.size() + regularPlayers.size() + 
                                     checkedInPlayers.size() + waitingList.size()) << " players\n";
    file << "Remaining Spots: " << (maxCapacity - checkedInPlayers.size()) << " spots\n";
    
    file.close();
    
    std::cout << GREEN << "✅ Registration data saved successfully to: " << CYAN << filename << RESET << std::endl;
    std::cout << BLUE << "📄 File contains: " << YELLOW << "All queues, participants, and waiting list" << RESET << std::endl;
}

void Task2_Registration::showDataStructureInfo() {
    std::cout << "\n" << CYAN << BOLD << "📚 DATA STRUCTURE CONCEPTS - TASK 2" << RESET << std::endl;
    printBorder('═', 50);
    
    std::cout << "\n" << BLUE << BOLD << "🔹 PRIORITY QUEUE CONCEPT" << RESET << std::endl;
    std::cout << "   " << WHITE << "Implementation: Vector with priority-based processing" << RESET << std::endl;
    std::cout << "   " << YELLOW << "Purpose: Handle VIP, Early-bird, and Wildcard registrations" << RESET << std::endl;
    std::cout << "   " << GREEN << "Time Complexity: O(1) insert, O(n) for priority processing" << RESET << std::endl;
    std::cout << "   " << CYAN << "Why: Ensures higher-priority players get tournament spots first" << RESET << std::endl;
    
    std::cout << "\n" << MAGENTA << BOLD << "🔹 QUEUE (FIFO) CONCEPT" << RESET << std::endl;
    std::cout << "   " << WHITE << "Implementation: Vector with first-in-first-out processing" << RESET << std::endl;
    std::cout << "   " << YELLOW << "Purpose: Handle regular player registrations" << RESET << std::endl;
    std::cout << "   " << GREEN << "Time Complexity: O(1) insert, O(1) for FIFO processing" << RESET << std::endl;
    std::cout << "   " << CYAN << "Why: Fair processing - first come, first served" << RESET << std::endl;
    
    std::cout << "\n" << RED << BOLD << "🔹 CIRCULAR QUEUE CONCEPT" << RESET << std::endl;
    std::cout << "   " << WHITE << "Implementation: Vector as waiting list with replacement logic" << RESET << std::endl;
    std::cout << "   " << YELLOW << "Purpose: Manage replacement players efficiently" << RESET << std::endl;
    std::cout << "   " << GREEN << "Time Complexity: O(1) for replacement operations" << RESET << std::endl;
    std::cout << "   " << CYAN << "Why: Efficient replacement when players withdraw" << RESET << std::endl;
    
    std::cout << "\n" << GREEN << BOLD << "🎯 SYSTEM WORKFLOW:" << RESET << std::endl;
    std::cout << "   " << CYAN << "1. Players register → sorted by priority (VIP first)" << RESET << std::endl;
    std::cout << "   " << BLUE << "2. Check-in processes Priority players first, then Regular" << RESET << std::endl;
    std::cout << "   " << YELLOW << "3. Overflow goes to Waiting List (Circular Queue concept)" << RESET << std::endl;
    std::cout << "   " << MAGENTA << "4. Withdrawals trigger automatic replacements from waiting list" << RESET << std::endl;
    printBorder('═', 50);
}