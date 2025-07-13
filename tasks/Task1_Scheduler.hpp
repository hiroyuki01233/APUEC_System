#ifndef TASK1_SCHEDULER_HPP
#define TASK1_SCHEDULER_HPP

#include "../shared/Player.hpp"
#include "../shared/Stack.hpp"
#include "../shared/LinkedList.hpp"
#include "../shared/HashMap.hpp"
#include <string>

struct Match {
    int matchID;
    Player* player1;
    Player* player2;
    Player* winner;
    std::string stage;
    std::string status;
    
    Match(int id, Player* p1, Player* p2, const std::string& stg)
        : matchID(id), player1(p1), player2(p2), winner(nullptr), 
          stage(stg), status("Scheduled") {}
};

class Task1_Scheduler {
private:
    LinkedList<Player*> players;
    LinkedList<Match*> matches;
    Stack<Match*> matchHistory;
    HashMap<std::string, LinkedList<Player*>*> playersByGame;
    int nextMatchID;
    
    void generateQualifierMatches();
    void generateGroupMatches();
    void generateKnockoutMatches();
    LinkedList<Player*> getActivePlayers(const std::string& game);
    void sortPlayersByRanking(LinkedList<Player*>& playerList);

public:
    Task1_Scheduler();
    ~Task1_Scheduler();
    
    void addPlayer(Player* player);
    void removePlayer(int playerID);
    Player* findPlayer(int playerID);
    
    void generateMatchSchedule();
    void conductMatch(int matchID);
    void updateMatchResult(int matchID, int winnerID);
    
    void displayMatchSchedule();
    void displayMatchHistory();
    void displayPlayerStandings();
    void displayTournamentBracket();
    
    LinkedList<Player*> getPlayers() const;
    LinkedList<Match*> getMatches() const;
    
    void advanceWinners();
    void updatePlayerRankings();
    
    void saveMatchResults(const std::string& filename);
    void loadPlayersFromFile(const std::string& filename);
};

#endif