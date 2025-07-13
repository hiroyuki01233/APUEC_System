#include "Player.hpp"
#include <sstream>

Player::Player() : playerID(0), name(""), university(""), game(""), 
                   ranking(0), wins(0), losses(0), isActive(true) {}

Player::Player(int id, const std::string& playerName, const std::string& uni, 
               const std::string& gameName, int rank)
    : playerID(id), name(playerName), university(uni), game(gameName), 
      ranking(rank), wins(0), losses(0), isActive(true) {}

int Player::getPlayerID() const { return playerID; }
std::string Player::getName() const { return name; }
std::string Player::getUniversity() const { return university; }
std::string Player::getGame() const { return game; }
int Player::getRanking() const { return ranking; }
int Player::getWins() const { return wins; }
int Player::getLosses() const { return losses; }
bool Player::getIsActive() const { return isActive; }

void Player::setPlayerID(int id) { playerID = id; }
void Player::setName(const std::string& playerName) { name = playerName; }
void Player::setUniversity(const std::string& uni) { university = uni; }
void Player::setGame(const std::string& gameName) { game = gameName; }
void Player::setRanking(int rank) { ranking = rank; }
void Player::setWins(int w) { wins = w; }
void Player::setLosses(int l) { losses = l; }
void Player::setIsActive(bool active) { isActive = active; }

void Player::addWin() { wins++; }
void Player::addLoss() { losses++; }
void Player::updateRanking(int newRank) { ranking = newRank; }

std::string Player::toString() const {
    std::stringstream ss;
    ss << "Player ID: " << playerID << "\n"
       << "Name: " << name << "\n"
       << "University: " << university << "\n"
       << "Game: " << game << "\n"
       << "Ranking: " << ranking << "\n"
       << "Record: " << wins << "-" << losses << "\n"
       << "Status: " << (isActive ? "Active" : "Inactive");
    return ss.str();
}