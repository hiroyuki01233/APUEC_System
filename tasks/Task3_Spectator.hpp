#ifndef TASK3_SPECTATOR_HPP
#define TASK3_SPECTATOR_HPP

#include "../shared/PriorityQueue.hpp"
#include "../shared/CircularQueue.hpp"

class Task3_Spectator {
public:
    Task3_Spectator();
    ~Task3_Spectator();
    
    void manageVIPSeating();
    void handleAudienceOverflow();
    void organizeLiveStreaming();
};

#endif