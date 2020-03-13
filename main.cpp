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
#include <random>

using namespace std;


void print_header() {
    cout << " |  ||  |  |  ||  |  |  |  |  |  |  |  |  |  ||  |  |  |  ||  | " << endl;
    cout << "  |  ||  |  |  ||  |  |DEAL OR NO DEAL|  |  ||  |  |  |  ||  | " << endl;
    cout << " |  ||  |  |  ||  |  |  |  |  |  |  |  |  |  ||  |  |  |  ||  |" << endl;
}

void print_intro() {
    cout << endl;
    cout << "  Welcome to Deal or No Deal. I’m your host, Howie Mandel," << endl;
    cout << "  and we're in for an exciting time! One million dollars is" << endl;
    cout << "  at stake tonight. Will our contestant be able to win some " << endl;
    cout << "  money, or will our banker be able to get the best of them?" << endl;
}

void print_rules() {
    cout << endl;
    cout << "  The rules are ~simple: " << endl;
    cout << "    1. Pick a case to hold (personal case)" << endl;
    cout << "    2. Select the prompted number of cases to open" << endl;
    cout << "    3. If the banker offers you a deal choose DEAL or NO DEAL!" << endl;
    cout << endl;
    cout << "  Good Luck!" << endl;
}

void print_closer() {
    cout << " |  ||  |  |  ||  |  |  | Thanks |  |  |  |  |  | |  |  | | " << endl;
    cout << "  |  ||  |  |  ||  |  |For Playing |  |  ||  |  |  |  ||  | ";
}

int main() {
    print_header();
    print_intro();
    print_rules();
    Game game = Game();
    game.construct_suite();
    game.hold_case();
    game.construct_wall();
    while (game.get_status()) {
        game.print_suite();
        game.input_case_handler();
        game.print_wall();
        game.broker_handler();
        game.update_round();
    }
    game.initiate_ending();
    print_closer();
}
