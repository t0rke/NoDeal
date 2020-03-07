//
//  Suite.cpp
//  NoDeal
//
//  Created by Suneeth Torke on 3/6/20.
//  Copyright © 2020 Suneeth Torke. All rights reserved.
//
#include <iostream>   
#include <vector>
#include <random>
#include "Game.hpp"
#include "Case.hpp"

using namespace std;

auto rng = std::default_random_engine {};

vector<double> possVal = {0.01, 1, 5, 10, 25, 50, 75, 100, 200, 300, 400, 500, 750, 1000, 5000, 10000, 25000, 50000, 75000, 100000, 200000, 300000, 400000, 500000, 750000, 1000000};


Game::Game() {
    
}

void Game::construct_suite() {
    std::shuffle(std::begin(possVal), std::end(possVal), rng);
    for (int index = 1; index < SUITE_SIZE + 1; ++index) {
        Case temp = Case(index, possVal[index]);
        suite.push_back(temp);
    }
    modSuite = suite;
}

void Game::print_suite() {
    cout << endl;
    cout << "  ";
    for (int i = 20; i < 26; ++i) {
        cout << "  " << modSuite[i].get_caseFace();
    }
    cout << endl;
    cout << endl;
    for (int i = 13; i < 20; ++i) {
        cout << "  " << modSuite[i].get_caseFace();
    }
    cout << endl;
    cout << endl;
    cout << "  ";
    for (int i = 6; i < 13; ++i) {
        cout << "  " << modSuite[i].get_caseFace();
    }
    cout << endl;
    cout << endl;
    cout << "    ";
    for (int i = 0; i < 6; ++i) {
        cout << "  " << modSuite[i].get_caseFace();
    }
    cout << endl;
}

bool Game::case_isValid(int pickedCase) {
    for (int i = 0; i < caseList.size(); ++i) {
        if (caseList[i] == pickedCase) {
            caseList.erase(caseList.begin() + i);
            return true;
        }
    }
    return false;
}

void Game::hold_case(int pickedCase) {
    bool valid = case_isValid(pickedCase);
    while (valid == false) {
        cout << "Enter a valid case: ";
        cin  >> pickedCase;
        valid = case_isValid(pickedCase);
    }
    cout << "Youve chosen to hold case: " << pickedCase << endl;
    heldCase = modSuite[pickedCase - 1];
    modSuite[pickedCase - 1].set_caseFace();
}

void Game::open_case(int pickedCase) {
    bool valid = case_isValid(pickedCase);
    while (valid == false) {
        cout << "Enter a valid case: ";
        cin  >> pickedCase;
        valid = case_isValid(pickedCase);
    }
        
    cout << "Opening case: " << pickedCase << endl;
    cout << "It contains: " << modSuite[pickedCase - 1].get_caseVal() << endl;
    modSuite[pickedCase - 1].set_caseFace();
    // modSuite.erase(modSuite.begin() + pickedCase);
}

void Game::swap_case(int pickedCase) {
        
}

bool Game::get_terminator() {
    return ender;
}
    
    
    

    //std::vector<Case> setup;
    
    

