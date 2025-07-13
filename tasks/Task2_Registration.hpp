#ifndef TASK2_REGISTRATION_HPP
#define TASK2_REGISTRATION_HPP

#include "../shared/Player.hpp"
#include "../shared/Queue.hpp"
#include "../shared/PriorityQueue.hpp"

class Task2_Registration {
public:
    Task2_Registration();
    ~Task2_Registration();
    
    void registerPlayer();
    void checkInPlayer();
    void handleWithdrawal();
    void processWaitlist();
};

#endif