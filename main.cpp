// File: main.cpp

#include <iostream>
#include <string>
#include <cstdlib>

#include "tasks/Task1_Scheduler.hpp"
#include "tasks/Task2_Registration.hpp"
#include "tasks/Task4_Logger.hpp"

using namespace std;

void displayMainMenu() {
    cout << "\n=========================================\n"
         << "    APUEC SYSTEM - MAIN MENU\n"
         << "=========================================\n"
         << "1. Match Scheduling & Player Progression\n"
         << "2. Tournament Registration & Player Queueing\n"
         << "3. Spectator Management (Not Available)\n"
         << "4. Result Logging & Performance History\n"
         << "0. Exit System\n"
         << "=========================================\n"
         << "Enter your choice: ";
}

void displayTask1Menu() {
    cout << "\n=== MATCH SCHEDULING & PLAYER PROGRESSION ===\n"
         << "1. Load Players from File\n"
         << "2. Add New Player\n"
         << "3. View All Players\n"
         << "4. Generate Match Schedule\n"
         << "5. Conduct Match\n"
         << "6. View Match Schedule\n"
         << "7. View Player Standings\n"
         << "8. View Tournament Bracket\n"
         << "9. View Match History\n"
         << "10. Save Match Results to File\n"
         << "0. Back to Main Menu\n"
         << "Enter your choice: ";
}

void displayTask2Menu() {
    cout << "\n=== TOURNAMENT REGISTRATION & PLAYER QUEUEING ===\n"
         << "1. Register New Player\n"
         << "2. Process Check-ins\n"
         << "3. Handle Player Withdrawal\n"
         << "4. Process Waitlist\n"
         << "5. View Registration Status\n"
         << "6. View All Queues\n"
         << "7. View Tournament Participants\n"
         << "8. Add Sample Registration Data\n"
         << "9. Data Structure Information\n"
         << "10. Save Registration Data to File\n"
         << "0. Back to Main Menu\n"
         << "Enter your choice: ";
}

void displayTask4Menu() {
    cout << "\n=== GAME RESULT LOGGING & PERFORMANCE HISTORY ===\n"
         << "1. Log Completed Match\n"
         << "2. View Recent Results\n"
         << "3. Export Player Statistics\n"
         << "4. Generate Full Report\n"
         << "0. Back to Main Menu\n"
         << "Enter your choice: ";
}

void handleTask1(Task1_Scheduler& scheduler) {
    int choice;
    while (true) {
        displayTask1Menu();
        cin >> choice; cin.ignore();
        if (cin.fail()) { cin.clear(); cin.ignore(10000,'\n'); continue; }
        if (choice == 0) return;

        switch (choice) {
            case 1: {
                cout << "Enter filename (default: data/players.csv): ";
                string fn; getline(cin,fn);
                if (fn.empty()) fn="data/players.csv";
                scheduler.loadPlayersFromFile(fn);
                break;
            }
            case 2: {
                int id, rank; string name, uni, game;
                cout<<"Enter Player ID: "; cin>>id; cin.ignore();
                cout<<"Enter Name: "; getline(cin,name);
                cout<<"Enter University: "; getline(cin,uni);
                cout<<"Enter Game: "; getline(cin,game);
                cout<<"Enter Ranking: "; cin>>rank; cin.ignore();
                scheduler.addPlayer(new Player(id,name,uni,game,rank));
                break;
            }
            case 3:
                for (auto p : scheduler.getPlayers())
                    cout<<p->toString()<<"\n";
                break;
            case 4: scheduler.generateMatchSchedule(); break;
            case 5: {
                int mid; cout<<"Match ID: "; cin>>mid; cin.ignore();
                scheduler.conductMatch(mid);
                break;
            }
            case 6: scheduler.displayMatchSchedule(); break;
            case 7: scheduler.displayPlayerStandings(); break;
            case 8: scheduler.displayTournamentBracket(); break;
            case 9: scheduler.displayMatchHistory(); break;
            case 10: {
                cout<<"Filename (default: data/match_log.txt): ";
                string fn; getline(cin,fn);
                if (fn.empty()) fn="data/match_log.txt";
                scheduler.saveMatchResults(fn);
                break;
            }
            default:
                cout<<"Invalid choice\n";
        }
        cout<<"\nPress Enter to continue..."; cin.get();
    }
}

void handleTask2(Task2_Registration& reg) {
    int choice;
    while (true) {
        displayTask2Menu();
        cin >> choice; cin.ignore();
        if (cin.fail()) { cin.clear(); cin.ignore(10000,'\n'); continue; }
        if (choice == 0) return;

        switch (choice) {
            case 1:  reg.registerPlayer(); break;
            case 2:  reg.checkInPlayer(); break;
            case 3:  reg.handleWithdrawal(); break;
            case 4:  reg.processWaitlist(); break;
            case 5:  reg.displayRegistrationStatus(); break;
            case 6:  reg.displayAllQueues(); break;
            case 7:  reg.displayCheckedInPlayers(); break;
            case 8:  reg.addSampleRegistrationData(); break;
            case 9:  reg.showDataStructureInfo(); break;
            case 10: reg.saveRegistrationData(); break;
            default: cout<<"Invalid choice\n";
        }
        cout<<"\nPress Enter to continue..."; cin.get();
    }
}

void handleTask4(Task1_Scheduler& scheduler) {
    Task4_Logger logger;
    int choice;
    while (true) {
        displayTask4Menu();
        cin >> choice; cin.ignore();
        if (cin.fail()) { cin.clear(); cin.ignore(10000,'\n'); continue; }
        if (choice == 0) return;

        switch (choice) {
            case 1: {
                int mid; cout<<"Match ID: "; cin>>mid; cin.ignore();
                Match* m=nullptr;
                auto ms=scheduler.getMatches();
                for (int i=0;i<ms.getSize();++i)
                    if (ms[i]->matchID==mid && ms[i]->status=="Completed")
                        m=ms[i];
                if (m) {
                    logger.logMatchResult(m);
                    cout<<"Logged match #"<<mid<<"\n";
                } else cout<<"Not found/completed\n";
                break;
            }
            case 2:
                logger.viewRecentResults();
                break;
            case 3:
                logger.exportStatistics("player_stats.txt");
                break;
            case 4:
                logger.generateReport("full_report.txt");
                break;
            default:
                cout<<"Invalid choice\n";
        }
        cout<<"\nPress Enter to continue..."; cin.get();
    }
}

int main() {
    Task1_Scheduler scheduler;
    Task2_Registration registration;
    int choice;

    cout<<"=== APUEC MANAGEMENT SYSTEM ===\n";
    while (true) {
        displayMainMenu();
        cin >> choice; cin.ignore();
        if (cin.fail()) { cin.clear(); cin.ignore(10000,'\n'); continue; }

        switch (choice) {
            case 1: handleTask1(scheduler); break;
            case 2: handleTask2(registration); break;
            case 3: cout<<"\nSpectator Management not available.\n"; break;
            case 4: handleTask4(scheduler); break;
            case 0: cout<<"\nExiting...\n"; return 0;
            default: cout<<"Invalid choice\n";
        }
    }
}
