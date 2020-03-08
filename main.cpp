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
    cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" << endl;
    cout << "-*-*-*-*-*-*-*-*-*-*{DEAL or no DEAL}*-*-*-*-*-*-*-*-*-*-*-" << endl;
    cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" << endl;
}

void print_status() {
    cout << "Generating A New Game " << " [{";
    int timer = 9;
    while(timer > 0)
    {
        if (timer == 1) {
            cout << ">";
            //sleep(10000);
        }
        else {
            cout << "==";
        }
        //sleep(200000);
        --timer;
    }
    cout << "}]" << endl;
    //sleep(200000);
}

int main() {

    int CaseNumber;
    
    print_header();
    print_status();
    
    Game game = Game();
    game.construct_suite();
    game.hold_case();
    game.construct_wall();
    //game.print_suite_vals();
    //game.print_wall();
    //game.print_suite_vals();
    while (game.get_status() == false) {
        game.print_suite();
        game.input_case_handler();
        game.print_wall();
        //game.print_suite_vals();
        if (game.get_modSuite_size() == 5 || game.get_modSuite_size() == 16
            || game.get_modSuite_size() == 10) {
            game.call_the_broker();
        }
        if (game.get_modSuite_size() == 7 || game.get_modSuite_size() == 11) {
            game.swap_case();
            }
        }
    game.initiate_ending();
    
}
