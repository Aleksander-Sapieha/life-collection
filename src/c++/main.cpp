#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <stdlib.h>
#include <vector>

#ifdef _WIN64
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

using namespace std;

inline bool exists (const std::string& name) {
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }   
}

string playerName;
class Player {
public:
    string name;
    int age;
    int health;
    int happiness;
    int money;
    int social;
    string job;
    bool married;
    int children;
    bool ownsHouse;
    bool retired;

    Player(string n) {
        name = n;
        age = 18;
        health = 100;
        happiness = 50;
        money = 100;
        social = 50;
        job = "Unemployed";
        married = false;
        children = 0;
        ownsHouse = false;
        retired = false;
    }

    void showStatus() {
        cout << "\n--- Status ---\n";
        cout << "Name: " << name << "\nAge: " << age << "\nHealth: " << health
             << "\nHappiness: " << happiness << "\nMoney: $" << money
             << "\nSocial: " << social << "\nJob: " << job
             << "\nMarried: " << (married ? "Yes" : "No")
             << "\nChildren: " << children
             << "\nOwns House: " << (ownsHouse ? "Yes" : "No")
             << "\nRetired: " << (retired ? "Yes" : "No") << endl;
    }

    bool isAlive() {
        return health > 0 && happiness > 0;
    }
};

void randomEvent(Player &p) {
    int event = rand() % 5;
    switch(event) {
        case 0:
            cout << "You found a small gift! Money +10, Happiness +5\n";
            p.money += 10; p.happiness += 5;
            break;
        case 1:
            cout << "You caught a cold. Health -10, Happiness -5\n";
            p.health -= 10; p.happiness -= 5;
            break;
        case 2:
            cout << "Your friend invited you out. Social +10, Happiness +10, Money -5\n";
            p.social += 10; p.happiness += 10; p.money -= 5;
            break;
        case 3:
            cout << "Unexpected car repair! Money -20, Happiness -5\n";
            p.money -= 20; p.happiness -= 5;
            break;
        case 4:
            cout << "You exercised and ate healthy today. Health +10, Happiness +5\n";
            p.health += 10; p.happiness += 5;
            break;
    }

    // Keep stats in bounds
    if(p.health > 100) p.health = 100;
    if(p.happiness > 100) p.happiness = 100;
    if(p.social > 100) p.social = 100;
    if(p.health < 0) p.health = 0;
    if(p.happiness < 0) p.happiness = 0;
    if(p.social < 0) p.social = 0;
}

void chooseAction(Player &p) {
    cout << "\nWhat do you want to do today?\n";
    cout << "1. Work\n2. Relax\n3. Exercise\n4. Socialize\n5. Look for a job\n";
    int choice;
    cin >> choice;

    switch(choice) {
        case 1:
            if(p.job == "Unemployed") {
                #ifdef CLEAR
                    system(CLEAR);
                #endif
                cout << "You are unemployed, cannot work.\n";
            }

            else {
                #ifdef CLEAR
                    system(CLEAR);
                #endif
                cout << "You worked at your job. Money +50, Happiness -10, Health -5\n";
                p.money += 50; p.happiness -= 10; p.health -= 5;
            }
            break;
        case 2:
            #ifdef CLEAR
                system(CLEAR);
            #endif
            cout << "You relaxed. Happiness +15, Health +5\n";
            p.happiness += 15; p.health += 5; p.social -= 5;
            break;

        case 3:
            #ifdef CLEAR
                system(CLEAR);
            #endif
            cout << "You exercised. Health +15, Happiness +5\n";
            p.health += 15; p.happiness += 5;
            break;

        case 4:
            #ifdef CLEAR
                system(CLEAR);
            #endif
            cout << "You socialized. Social +20, Happiness +10, Money -10\n";
            p.social += 20; p.happiness += 10; p.money -= 10;
            break;

        case 5:
            #ifdef CLEAR
                system(CLEAR);
            #endif
            cout << "Choose a job:\n1. Engineer (Money +70/day)\n2. Artist (Money +30/day, Happiness +10)\n3. Teacher (Money +40/day, Social +10)\n";
            int jobChoice;
            cin >> jobChoice;
            switch(jobChoice) {
                case 1: p.job = "Engineer"; break;
                case 2: p.job = "Artist"; break;
                case 3: p.job = "Teacher"; break;
                default: cout << "Invalid choice.\n"; break;
            }
            break;

        case 6:
            #ifdef CLEAR
                system(CLEAR);
            #endif
            if(!p.ownsHouse && p.money >= 100) {
                cout << "You bought a house! Money -100, Happiness +20\n";
                p.ownsHouse = true; p.money -= 100; p.happiness += 20;
            } else if(p.ownsHouse) {
                cout << "You already own a house.\n";
            } else {
                cout << "Not enough money to buy a house.\n";
            }
            break;

            case 7:
                #ifdef CLEAR
                    system(CLEAR);
                #endif
                if(p.married) {
                    cout << "You had a child! Happiness +20, Social +10, Money -20\n";
                    p.children += 1; p.happiness += 20; p.social += 10; p.money -= 20;
                } else {
                    cout << "You must be married to have a child.\n";
                }
            break;

        default:
            #ifdef CLEAR
                system(CLEAR);
            #endif
            cout << "You did nothing today.\n";
            break;
    }

    // Keep stats in bounds
    if(p.health > 100) p.health = 100;
    if(p.happiness > 100) p.happiness = 100;
    if(p.social > 100) p.social = 100;
    if(p.health < 0) p.health = 0;
    if(p.happiness < 0) p.happiness = 0;
    if(p.social < 0) p.social = 0;
}

int main() {
    cout << "Enter your name: ";
    cin >> playerName;
    Player player(playerName);

    while(player.isAlive() && player.age <= 100) {
        player.showStatus();
        randomEvent(player);
        chooseAction(player);

        // Retire at 65
        if(player.age >= 65 && !player.retired) {
            cout << "You have reached retirement age. You are now retired.\n";
            player.retired = true;
            player.job = "Retired";
        }

        player.age += 1;
    }

    cout << "\nGame Over! " << player.name << " lived until age " << player.age << "." << endl;
    cout << "Final Stats: Happiness " << player.happiness << ", Health " << player.health
         << ", Money $" << player.money << ", Social " << player.social
         << ", Children " << player.children << ", House " << (player.ownsHouse ? "Yes" : "No") << endl;

    return 0;
}