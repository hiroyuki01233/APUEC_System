#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>

class Player {
private:
    int playerID;
    std::string name;
    std::string university;
    std::string game;
    int ranking;
    int wins;
    int losses;
    bool isActive;

public:
    Player();
    Player(int id, const std::string& playerName, const std::string& uni, 
           const std::string& gameName, int rank);
    
    int getPlayerID() const;
    std::string getName() const;
    std::string getUniversity() const;
    std::string getGame() const;
    int getRanking() const;
    int getWins() const;
    int getLosses() const;
    bool getIsActive() const;
    
    void setPlayerID(int id);
    void setName(const std::string& playerName);
    void setUniversity(const std::string& uni);
    void setGame(const std::string& gameName);
    void setRanking(int rank);
    void setWins(int w);
    void setLosses(int l);
    void setIsActive(bool active);
    
    void addWin();
    void addLoss();
    void updateRanking(int newRank);
    
    std::string toString() const;
};

#endif