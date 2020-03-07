//
//  main.cpp
//  NoDeal
//
//  Created by Suneeth Torke on 3/6/20.
//  Copyright © 2020 Suneeth Torke. All rights reserved.
//

#include <iostream>
#include <vector>
#include "Game.hpp"
#include "Case.hpp"

using namespace std;

void sleep(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

void print_header() {
    cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" << endl;
    cout << "-*-*-*-*-*-*-*-*-*-*-*{DEAL or no DEAL}*-*-*-*-*-*-*-*-*-*-" << endl;
    cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" << endl;
}

void print_status() {
    cout << "Generating A New Game " << " [{";
    int timer = 9;
    while(timer > 0)
    {
        if (timer == 1) {
            cout << ">";
            sleep(10000);
        }
        else {
            cout << "==";
        }
        sleep(200000);
        --timer;
    }
    cout << "}]" << endl;
    cout << endl;
    sleep(200000);
}

int main() {
    bool endGame = false;
    int CaseNumber;
    
    print_header();
    print_status();
    
    Game game = Game();
    game.construct_suite();
    game.print_suite();
    
    cout << "please enter a case to hold: ";
    cin >> CaseNumber;
    game.hold_case(CaseNumber);
    while (endGame == false) {
        game.print_suite();
        cout << "please enter a case to open: ";
        cin >> CaseNumber;
        game.open_case(CaseNumber);
        
        
        endGame = game.get_terminator();
    }
}
