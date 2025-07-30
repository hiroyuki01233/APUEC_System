#include <iostream>
#include <string>
#include <cstdlib>
#include "tasks/Task1_Scheduler.hpp"
#include "tasks/Task2_Registration.hpp"

using namespace std;

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void displayMainMenu() {
    cout << "\n=========================================\n";
    cout << "    APUEC SYSTEM - MAIN MENU\n";
    cout << "=========================================\n";
    cout << "1. Match Scheduling & Player Progression\n";
    cout << "2. Tournament Registration & Player Queueing\n";
    cout << "3. Spectator Management (Not Available)\n";
    cout << "4. Result Logging (Not Available)\n";
    cout << "0. Exit System\n";
    cout << "=========================================\n";
    cout << "Enter your choice: ";
}

void displayTask1Menu() {
    cout << "\n=== MATCH SCHEDULING & PLAYER PROGRESSION ===\n";
    cout << "1. Load Players from File\n";
    cout << "2. Add New Player\n";
    cout << "3. View All Players\n";
    cout << "4. Generate Match Schedule\n";
    cout << "5. Conduct Match\n";
    cout << "6. View Match Schedule\n";
    cout << "7. View Player Standings\n";
    cout << "8. View Tournament Bracket\n";
    cout << "9. View Match History\n";
    cout << "10. Save Match Results to File\n";
    cout << "0. Back to Main Menu\n";
    cout << "Enter your choice: ";
}

void displayTask2Menu() {
    cout << "\n=== TOURNAMENT REGISTRATION & PLAYER QUEUEING ===\n";
    cout << "1. Register New Player\n";
    cout << "2. Process Check-ins\n";
    cout << "3. Handle Player Withdrawal\n";
    cout << "4. Process Waitlist\n";
    cout << "5. View Registration Status\n";
    cout << "6. View All Queues\n";
    cout << "7. View Tournament Participants\n";
    cout << "8. Add Sample Registration Data\n";
    cout << "9. Data Structure Information\n";
    cout << "10. Save Registration Data to File\n"; 
    cout << "0. Back to Main Menu\n";
    cout << "Enter your choice: ";
}

void handleTask1(Task1_Scheduler& scheduler) {
    int choice;
    
    while (true) {
        displayTask1Menu();
        cin >> choice;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        
        cin.ignore();
        
        switch (choice) {
            case 1: {
                cout << "Enter filename (default: data/players.csv): ";
                string filename;
                getline(cin, filename);
                if (filename.empty()) {
                    filename = "data/players.csv";
                }
                scheduler.loadPlayersFromFile(filename);
                break;
            }
            
            case 2: {
                int id, ranking;
                string name, university, game;
                
                cout << "Enter Player ID: ";
                cin >> id;
                cin.ignore();
                
                cout << "Enter Player Name: ";
                getline(cin, name);
                
                cout << "Enter University: ";
                getline(cin, university);
                
                cout << "Enter Game (e.g., League of Legends, Valorant): ";
                getline(cin, game);
                
                cout << "Enter Initial Ranking: ";
                cin >> ranking;
                
                Player* newPlayer = new Player(id, name, university, game, ranking);
                scheduler.addPlayer(newPlayer);
                cout << "Player added successfully!\n";
                break;
            }
            
            case 3: {
                LinkedList<Player*> players = scheduler.getPlayers();
                if (players.isEmpty()) {
                    cout << "No players registered yet.\n";
                } else {
                    cout << "\n=== REGISTERED PLAYERS ===\n";
                    for (int i = 0; i < players.getSize(); i++) {
                        cout << "\n" << players[i]->toString() << "\n";
                    }
                }
                break;
            }
            
            case 4: {
                scheduler.generateMatchSchedule();
                break;
            }
            
            case 5: {
                int matchID;
                cout << "Enter Match ID to conduct: ";
                cin >> matchID;
                scheduler.conductMatch(matchID);
                break;
            }
            
            case 6: {
                scheduler.displayMatchSchedule();
                break;
            }
            
            case 7: {
                scheduler.displayPlayerStandings();
                break;
            }
            
            case 8: {
                scheduler.displayTournamentBracket();
                break;
            }
            
            case 9: {
                scheduler.displayMatchHistory();
                break;
            }
            
            case 10: {
                cout << "Enter filename to save results (default: data/match_log.txt): ";
                string filename;
                getline(cin, filename);
                if (filename.empty()) {
                    filename = "data/match_log.txt";
                }
                scheduler.saveMatchResults(filename);
                break;
            }
            
            case 0:
                return;
                
            default:
                cout << "Invalid choice. Please try again.\n";
        }
        
        cout << "\nPress Enter to continue...";
        cin.get();
    }
}

void handleTask2(Task2_Registration& registration) {
    int choice;
    
    while (true) {
        displayTask2Menu();
        cin >> choice;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        
        cin.ignore();
        
        switch (choice) {
            case 1:
                registration.registerPlayer();
                break;
                
            case 2:
                registration.checkInPlayer();
                break;
                
            case 3:
                registration.handleWithdrawal();
                break;
                
            case 4:
                registration.processWaitlist();
                break;
                
            case 5:
                registration.displayRegistrationStatus();
                break;
                
            case 6:
                registration.displayAllQueues();
                break;
                
            case 7:
                registration.displayCheckedInPlayers();
                break;
                
            case 8:
                registration.addSampleRegistrationData();
                break;
                
            case 9:
                registration.showDataStructureInfo();
                break;

             case 10:                                    
                registration.saveRegistrationData();    
                break; 
                
            case 0:
                return;
                
            default:
                cout << "Invalid choice. Please try again.\n";
        }
        
        cout << "\nPress Enter to continue...";
        cin.get();
    }
}

int main() {
    Task1_Scheduler scheduler;
    Task2_Registration registration; // Tournament capacity for registration
    int choice;
    
    cout << "=========================================\n";
    cout << "  WELCOME TO APUEC MANAGEMENT SYSTEM\n";
    cout << "  Asia Pacific University Esports\n";
    cout << "  Championship Management System\n";
    cout << "=========================================\n";
    cout << "Tasks Available:\n";
    cout << "✅ Task 1: Match Scheduling & Player Progression\n";
    cout << "✅ Task 2: Tournament Registration & Player Queueing\n";
    cout << "⏳ Task 3: Spectator Management (Coming Soon)\n";
    cout << "⏳ Task 4: Result Logging (Coming Soon)\n";
    cout << "=========================================\n";
    
    while (true) {
        displayMainMenu();
        cin >> choice;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        
        switch (choice) {
            case 1:
                handleTask1(scheduler);
                break;
                
            case 2:
                handleTask2(registration);
                break;
                
            case 3:
            case 4:
                cout << "\nThis module is not available yet.\n";
                cout << "Currently implemented: Task 1 and Task 2\n";
                break;
                
            case 0:
                cout << "\nThank you for using APUEC System!\n";
                cout << "Tasks completed: Task 1 (Match Scheduling) + Task 2 (Registration)\n";
                cout << "Goodbye!\n";
                return 0;
                
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
    
    return 0;
}