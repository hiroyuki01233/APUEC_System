#include "Task1_Scheduler.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>

Task1_Scheduler::Task1_Scheduler() : nextMatchID(1) {}

Task1_Scheduler::~Task1_Scheduler() {
    for (int i = 0; i < players.getSize(); i++) {
        delete players[i];
    }
    for (int i = 0; i < matches.getSize(); i++) {
        delete matches[i];
    }
    
    LinkedList<std::string> games = playersByGame.keys();
    for (int i = 0; i < games.getSize(); i++) {
        delete playersByGame[games[i]];
    }
}

void Task1_Scheduler::addPlayer(Player* player) {
    players.pushBack(player);
    
    std::string game = player->getGame();
    if (!playersByGame.contains(game)) {
        playersByGame[game] = new LinkedList<Player*>();
    }
    playersByGame[game]->pushBack(player);
}

void Task1_Scheduler::removePlayer(int playerID) {
    for (int i = 0; i < players.getSize(); i++) {
        if (players[i]->getPlayerID() == playerID) {
            players[i]->setIsActive(false);
            return;
        }
    }
}

Player* Task1_Scheduler::findPlayer(int playerID) {
    for (int i = 0; i < players.getSize(); i++) {
        if (players[i]->getPlayerID() == playerID) {
            return players[i];
        }
    }
    return nullptr;
}

void Task1_Scheduler::generateMatchSchedule() {
    std::cout << "Generating tournament schedule...\n";
    
    generateQualifierMatches();
    generateGroupMatches();
    generateKnockoutMatches();
    
    std::cout << "Schedule generated successfully!\n";
    std::cout << "Total matches scheduled: " << matches.getSize() << "\n";
}

void Task1_Scheduler::generateQualifierMatches() {
    LinkedList<std::string> games = playersByGame.keys();
    
    for (int g = 0; g < games.getSize(); g++) {
        std::string game = games[g];
        LinkedList<Player*> gamePlayers = getActivePlayers(game);
        
        if (gamePlayers.getSize() < 2) continue;
        
        sortPlayersByRanking(gamePlayers);
        
        for (int i = 0; i < gamePlayers.getSize() - 1; i += 2) {
            Match* match = new Match(nextMatchID++, gamePlayers[i], 
                                   gamePlayers[i + 1], "Qualifier");
            matches.pushBack(match);
        }
    }
}

void Task1_Scheduler::generateGroupMatches() {
    LinkedList<std::string> games = playersByGame.keys();
    
    for (int g = 0; g < games.getSize(); g++) {
        std::string game = games[g];
        LinkedList<Player*> qualifiedPlayers;
        
        for (int i = 0; i < matches.getSize(); i++) {
            Match* match = matches[i];
            if (match->stage == "Qualifier" && match->winner != nullptr &&
                match->player1->getGame() == game) {
                qualifiedPlayers.pushBack(match->winner);
            }
        }
        
        if (qualifiedPlayers.getSize() >= 4) {
            for (int i = 0; i < qualifiedPlayers.getSize(); i++) {
                for (int j = i + 1; j < qualifiedPlayers.getSize(); j++) {
                    Match* match = new Match(nextMatchID++, qualifiedPlayers[i],
                                           qualifiedPlayers[j], "Group");
                    matches.pushBack(match);
                }
            }
        }
    }
}

void Task1_Scheduler::generateKnockoutMatches() {
    LinkedList<std::string> games = playersByGame.keys();
    
    for (int g = 0; g < games.getSize(); g++) {
        std::string game = games[g];
        LinkedList<Player*> topPlayers;
        
        LinkedList<Player*>* gamePlayers = playersByGame[game];
        for (int i = 0; i < gamePlayers->getSize(); i++) {
            Player* player = (*gamePlayers)[i];
            if (player->getIsActive() && player->getWins() >= 2) {
                topPlayers.pushBack(player);
            }
        }
        
        sortPlayersByRanking(topPlayers);
        
        if (topPlayers.getSize() >= 2) {
            if (topPlayers.getSize() >= 4) {
                Match* semifinal1 = new Match(nextMatchID++, topPlayers[0],
                                            topPlayers[3], "Semifinal");
                Match* semifinal2 = new Match(nextMatchID++, topPlayers[1],
                                            topPlayers[2], "Semifinal");
                matches.pushBack(semifinal1);
                matches.pushBack(semifinal2);
            }
            
            Match* finalMatch = new Match(nextMatchID++, nullptr, nullptr, "Final");
            matches.pushBack(finalMatch);
        }
    }
}

LinkedList<Player*> Task1_Scheduler::getActivePlayers(const std::string& game) {
    LinkedList<Player*> activePlayers;
    LinkedList<Player*>* gamePlayers = playersByGame[game];
    
    if (gamePlayers != nullptr) {
        for (int i = 0; i < gamePlayers->getSize(); i++) {
            if ((*gamePlayers)[i]->getIsActive()) {
                activePlayers.pushBack((*gamePlayers)[i]);
            }
        }
    }
    
    return activePlayers;
}

void Task1_Scheduler::sortPlayersByRanking(LinkedList<Player*>& playerList) {
    playerList.mergeSort([](Player* const& a, Player* const& b) {
        return a->getRanking() < b->getRanking();
    });
}

void Task1_Scheduler::conductMatch(int matchID) {
    Match* targetMatch = nullptr;
    
    for (int i = 0; i < matches.getSize(); i++) {
        if (matches[i]->matchID == matchID) {
            targetMatch = matches[i];
            break;
        }
    }
    
    if (targetMatch != nullptr && targetMatch->status == "Scheduled") {
        std::cout << "\nConducting Match #" << matchID << "\n";
        std::cout << "Player 1: " << targetMatch->player1->getName() << " (Rank: " 
                  << targetMatch->player1->getRanking() << ")\n";
        std::cout << "Player 2: " << targetMatch->player2->getName() << " (Rank: " 
                  << targetMatch->player2->getRanking() << ")\n";
        
        int winner;
        std::cout << "Enter winner (1 or 2): ";
        std::cin >> winner;
        
        if (winner == 1) {
            updateMatchResult(matchID, targetMatch->player1->getPlayerID());
        } else if (winner == 2) {
            updateMatchResult(matchID, targetMatch->player2->getPlayerID());
        }
    } else {
        std::cout << "Match not found or already completed.\n";
    }
}

void Task1_Scheduler::updateMatchResult(int matchID, int winnerID) {
    Match* targetMatch = nullptr;
    
    for (int i = 0; i < matches.getSize(); i++) {
        if (matches[i]->matchID == matchID) {
            targetMatch = matches[i];
            break;
        }
    }
    
    if (targetMatch != nullptr) {
        Player* winner = findPlayer(winnerID);
        
        if (winner == targetMatch->player1 || winner == targetMatch->player2) {
            targetMatch->winner = winner;
            targetMatch->status = "Completed";
            
            winner->addWin();
            Player* loser = (winner == targetMatch->player1) ? 
                           targetMatch->player2 : targetMatch->player1;
            loser->addLoss();
            
            matchHistory.push(targetMatch);
            
            std::cout << "Match result updated successfully!\n";
            std::cout << "Winner: " << winner->getName() << "\n";
            
            advanceWinners();
            updatePlayerRankings();
        }
    }
}

void Task1_Scheduler::displayMatchSchedule() {
    std::cout << "\n=== MATCH SCHEDULE ===\n";
    std::cout << std::left << std::setw(10) << "Match ID" 
              << std::setw(20) << "Player 1" 
              << std::setw(20) << "Player 2"
              << std::setw(15) << "Stage"
              << std::setw(15) << "Status" << "\n";
    std::cout << std::string(80, '-') << "\n";
    
    for (int i = 0; i < matches.getSize(); i++) {
        Match* match = matches[i];
        if (match->player1 && match->player2) {
            std::cout << std::left << std::setw(10) << match->matchID
                      << std::setw(20) << match->player1->getName()
                      << std::setw(20) << match->player2->getName()
                      << std::setw(15) << match->stage
                      << std::setw(15) << match->status << "\n";
        }
    }
}

void Task1_Scheduler::displayMatchHistory() {
    std::cout << "\n=== MATCH HISTORY ===\n";
    
    Stack<Match*> tempStack;
    while (!matchHistory.isEmpty()) {
        tempStack.push(matchHistory.pop());
    }
    
    while (!tempStack.isEmpty()) {
        Match* match = tempStack.pop();
        std::cout << "Match #" << match->matchID << ": "
                  << match->player1->getName() << " vs "
                  << match->player2->getName() << " - Winner: "
                  << match->winner->getName() << " (" << match->stage << ")\n";
        matchHistory.push(match);
    }
}

void Task1_Scheduler::displayPlayerStandings() {
    std::cout << "\n=== PLAYER STANDINGS ===\n";
    
    LinkedList<std::string> games = playersByGame.keys();
    
    for (int g = 0; g < games.getSize(); g++) {
        std::string game = games[g];
        std::cout << "\n" << game << " Division:\n";
        std::cout << std::left << std::setw(25) << "Player"
                  << std::setw(15) << "University"
                  << std::setw(10) << "Ranking"
                  << std::setw(10) << "Wins"
                  << std::setw(10) << "Losses" << "\n";
        std::cout << std::string(70, '-') << "\n";
        
        LinkedList<Player*>* gamePlayers = playersByGame[game];
        LinkedList<Player*> sortedPlayers;
        
        for (int i = 0; i < gamePlayers->getSize(); i++) {
            sortedPlayers.pushBack((*gamePlayers)[i]);
        }
        
        for (int i = 0; i < sortedPlayers.getSize() - 1; i++) {
            for (int j = 0; j < sortedPlayers.getSize() - i - 1; j++) {
                Player* a = sortedPlayers[j];
                Player* b = sortedPlayers[j + 1];
                
                bool shouldSwap = false;
                if (a->getWins() != b->getWins()) {
                    shouldSwap = a->getWins() < b->getWins();
                } else {
                    shouldSwap = a->getRanking() > b->getRanking();
                }
                
                if (shouldSwap) {
                    sortedPlayers[j] = b;
                    sortedPlayers[j + 1] = a;
                }
            }
        }
        
        for (int i = 0; i < sortedPlayers.getSize(); i++) {
            Player* player = sortedPlayers[i];
            if (player->getIsActive()) {
                std::cout << std::left << std::setw(25) << player->getName()
                          << std::setw(15) << player->getUniversity()
                          << std::setw(10) << player->getRanking()
                          << std::setw(10) << player->getWins()
                          << std::setw(10) << player->getLosses() << "\n";
            }
        }
    }
}

void Task1_Scheduler::displayTournamentBracket() {
    std::cout << "\n=== TOURNAMENT BRACKET ===\n";
    
    LinkedList<std::string> games = playersByGame.keys();
    
    for (int g = 0; g < games.getSize(); g++) {
        std::string game = games[g];
        std::cout << "\n" << game << " Tournament:\n";
        
        std::cout << "\nQualifiers:\n";
        for (int i = 0; i < matches.getSize(); i++) {
            Match* match = matches[i];
            if (match->stage == "Qualifier" && match->player1->getGame() == game) {
                std::cout << "  " << match->player1->getName() << " vs "
                          << match->player2->getName();
                if (match->winner) {
                    std::cout << " -> Winner: " << match->winner->getName();
                }
                std::cout << "\n";
            }
        }
        
        std::cout << "\nSemifinals:\n";
        for (int i = 0; i < matches.getSize(); i++) {
            Match* match = matches[i];
            if (match->stage == "Semifinal" && match->player1 && 
                match->player1->getGame() == game) {
                std::cout << "  " << match->player1->getName() << " vs "
                          << match->player2->getName();
                if (match->winner) {
                    std::cout << " -> Winner: " << match->winner->getName();
                }
                std::cout << "\n";
            }
        }
        
        std::cout << "\nFinal:\n";
        for (int i = 0; i < matches.getSize(); i++) {
            Match* match = matches[i];
            if (match->stage == "Final" && match->player1 && 
                match->player1->getGame() == game) {
                std::cout << "  " << match->player1->getName() << " vs "
                          << match->player2->getName();
                if (match->winner) {
                    std::cout << " -> CHAMPION: " << match->winner->getName();
                }
                std::cout << "\n";
            }
        }
    }
}

void Task1_Scheduler::advanceWinners() {
    for (int i = 0; i < matches.getSize(); i++) {
        Match* match = matches[i];
        if (match->stage == "Semifinal" && match->winner != nullptr) {
            for (int j = 0; j < matches.getSize(); j++) {
                Match* finalMatch = matches[j];
                if (finalMatch->stage == "Final" && 
                    finalMatch->player1 == nullptr &&
                    match->winner->getGame() == match->player1->getGame()) {
                    finalMatch->player1 = match->winner;
                    break;
                } else if (finalMatch->stage == "Final" && 
                           finalMatch->player2 == nullptr &&
                           finalMatch->player1 != nullptr &&
                           match->winner->getGame() == finalMatch->player1->getGame()) {
                    finalMatch->player2 = match->winner;
                    break;
                }
            }
        }
    }
}

void Task1_Scheduler::updatePlayerRankings() {
    LinkedList<std::string> games = playersByGame.keys();
    
    for (int g = 0; g < games.getSize(); g++) {
        std::string game = games[g];
        LinkedList<Player*>* gamePlayers = playersByGame[game];
        
        for (int i = 0; i < gamePlayers->getSize() - 1; i++) {
            for (int j = 0; j < gamePlayers->getSize() - i - 1; j++) {
                Player* a = (*gamePlayers)[j];
                Player* b = (*gamePlayers)[j + 1];
                
                double winRateA = (a->getWins() + a->getLosses() > 0) ? 
                    (double)a->getWins() / (a->getWins() + a->getLosses()) : 0;
                double winRateB = (b->getWins() + b->getLosses() > 0) ? 
                    (double)b->getWins() / (b->getWins() + b->getLosses()) : 0;
                
                bool shouldSwap = false;
                if (winRateA != winRateB) {
                    shouldSwap = winRateA < winRateB;
                } else if (a->getWins() != b->getWins()) {
                    shouldSwap = a->getWins() < b->getWins();
                } else {
                    shouldSwap = a->getRanking() > b->getRanking();
                }
                
                if (shouldSwap) {
                    (*gamePlayers)[j] = b;
                    (*gamePlayers)[j + 1] = a;
                }
            }
        }
        
        for (int i = 0; i < gamePlayers->getSize(); i++) {
            (*gamePlayers)[i]->updateRanking(i + 1);
        }
    }
}

void Task1_Scheduler::saveMatchResults(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error opening file for writing.\n";
        return;
    }
    
    file << "APUEC MATCH RESULTS LOG\n";
    file << "Generated: " << std::time(nullptr) << "\n\n";
    
    file << "=== COMPLETED MATCHES ===\n";
    for (int i = 0; i < matches.getSize(); i++) {
        Match* match = matches[i];
        if (match->status == "Completed") {
            file << "Match #" << match->matchID << "\n";
            file << "Stage: " << match->stage << "\n";
            file << "Player 1: " << match->player1->getName() << " (Rank: "
                 << match->player1->getRanking() << ")\n";
            file << "Player 2: " << match->player2->getName() << " (Rank: "
                 << match->player2->getRanking() << ")\n";
            file << "Winner: " << match->winner->getName() << "\n\n";
        }
    }
    
    file << "=== PLAYER STATISTICS ===\n";
    for (int i = 0; i < players.getSize(); i++) {
        file << players[i]->toString() << "\n\n";
    }
    
    file.close();
    std::cout << "Match results saved to " << filename << "\n";
}

void Task1_Scheduler::loadPlayersFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error opening file: " << filename << "\n";
        return;
    }
    
    std::string line;
    std::getline(file, line);
    
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string idStr, name, university, game, rankStr;
        
        std::getline(ss, idStr, ',');
        std::getline(ss, name, ',');
        std::getline(ss, university, ',');
        std::getline(ss, game, ',');
        std::getline(ss, rankStr, ',');
        
        try {
            int id = std::stoi(idStr);
            int rank = std::stoi(rankStr);
            
            Player* player = new Player(id, name, university, game, rank);
            addPlayer(player);
        } catch (...) {
            std::cout << "Error parsing line: " << line << "\n";
        }
    }
    
    file.close();
    std::cout << "Loaded " << players.getSize() << " players from file.\n";
}

LinkedList<Player*> Task1_Scheduler::getPlayers() const {
    return players;
}

LinkedList<Match*> Task1_Scheduler::getMatches() const {
    return matches;
}