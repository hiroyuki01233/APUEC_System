#ifndef TASK2_REGISTRATION_HPP
#define TASK2_REGISTRATION_HPP

#include "../shared/Player.hpp"

class Task2_Registration {
public:
    Task2_Registration();
    ~Task2_Registration();
    
    // Core Task 2 functionality
    void registerPlayer();
    void checkInPlayer();
    void handleWithdrawal();
    void processWaitlist();
    
    // Display and management functions  
    void displayRegistrationStatus();
    void displayAllQueues();
    void displayCheckedInPlayers();
    void addSampleRegistrationData();
    void saveRegistrationData();
    void showDataStructureInfo();
};

#endif