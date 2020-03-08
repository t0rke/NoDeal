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


auto seed = std::chrono::system_clock::now().time_since_epoch().count();
std::mt19937_64 engine(seed);

vector<string> wordList = {"Awesome!", "Amazing!", "Great Job!", "Go You!", "Fantastic!", "Yes!", "You got it!", "Groovy!", "You're Killin it", "Huzza!", "voila!", "Whew!", "Stupendous!", "Regrettable!", "Unfortunate!", "Sad!", "It's Okay!", "Keep going!", "Better luck next time!", "Youre still in the running!", "Big Mistake!", "So close yet so far!", "Bad Guess!", "Thats alright!", "Dont cry", "Take a deep breath!", "Life Sucks!", "How unfortunate!"};

vector<string> possVal = {"0.01", "1", "5", "10", "25", "50", "75", "100", "200", "300", "400", "500", "750", "1000", "5000", "10000", "25000", "50000", "75000", "100000", "200000", "300000", "400000", "500000", "750000", "1000000"};

void Game::sleep(unsigned int mseconds) {
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

Game::Game() {
    
}
int Game::get_modSuite_size() {
    return modSuite.size();
}


void Game::construct_suite() {
    std::shuffle(std::begin(possVal), std::end(possVal), engine);
    for (int index = 1; index < SUITE_SIZE + 1; ++index) {
        Case temp = Case(index, possVal[index - 1]);
        suite.push_back(temp);
    }
    modSuite.clear();
    modSuite = suite;
    
}

void Game::erase_case(int target) {
    /*
    cout << modSuite.size() << endl;
    for (int i = 0; i < SUITE_SIZE + 0; ++i) {
      cout << modSuite[i].get_caseNumber() << ": " << modSuite[i].get_caseVal() << endl;
    }
    */
    for (int i = 0; i < SUITE_SIZE + 0; ++i) {
        
        if (modSuite.back().get_caseNumber() == target) {
            modSuite.pop_back();
        }
        else if (modSuite[i - 1].get_caseNumber() == target) {
            modSuite.erase(modSuite.begin() + i - 1);
            break;
        }
        
    }
}

void Game::print_suite() {
    cout << endl;
    cout << "  There are: {" << modSuite.size() << "} cases left!" << endl;
    size_t len = modSuite.size();
    cout << "  >";
    size_t i = 0;
    while (i < len) {
        if (modSuite[i].get_caseIdentifier() == 4) {
            cout << "  " << modSuite[i].get_caseFace();
        }
        ++i;
    }
    cout << endl << endl;
    i = 0;
    while (i < len) {
        if (modSuite[i].get_caseIdentifier() == 3) {
            cout << "  " << modSuite[i].get_caseFace();
        }
        ++i;
    }
    cout << endl << endl;
    cout << "  >";
    i = 0;
    while (i < len) {
        if (modSuite[i].get_caseIdentifier() == 2) {
            cout << "  " << modSuite[i].get_caseFace();
        }
        ++i;
    }
    cout << endl << endl;
    i = 0;
    while (i < len) {
        if (modSuite[i].get_caseIdentifier() == 1) {
            cout << "  " << modSuite[i].get_caseFace();
        }
        ++i;
    }
    cout << endl << endl;
}

void Game::print_suite_vals() {
    size_t i = 0;
    while (i < modSuite.size()) {
        cout << "  " << modSuite[i].get_caseFace() << ": " << modSuite[i].get_caseVal() << endl;
        ++i;
    }
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

void Game::hold_case() {
    print_suite();
    int pickedCase;
    cout << "  Please enter a case to hold: ";
    cin >> pickedCase;
    bool valid = case_isValid(pickedCase);
    while (valid == false) {
        cout << "  Enter a valid case: ";
        cin  >> pickedCase;
        valid = case_isValid(pickedCase);
    }
    sleep(200000);
    cout << "  You've chosen case:  " << suite[pickedCase - 1].get_caseFace() << endl;
    heldCase = suite[pickedCase - 1];
    heldCaseIden = pickedCase;
    erase_case(pickedCase);
}

void Game::open_case() {
    for (int i = 0; i < userChoices.size(); ++i) {
        cout << endl;
        sleep(200000);
        cout << "    Opening case: " << suite[userChoices[i] - 1].get_caseFace() << endl;
        cout << "    It contains: $" << suite[userChoices[i] - 1].get_caseVal() << endl;
        if (stod(suite[userChoices[i] - 1].get_caseVal()) <= 750) {
            size_t num = (engine() % (13 + 1 - 0)) + 0;
            cout << "    " << wordList[num] << endl;
        }
        else {
            size_t num = (engine() % (27 + 1 - 14)) + 14;
            cout << "    " << wordList[num] << endl;
        }
        erase_case(userChoices[i]);
    }
}

size_t Game::gen_num_cases_open() {
    size_t num = (engine() % (3 + 1 - 1)) + 1;
    return num;
}

void Game::input_case_handler() {
    bool valid;
    size_t set = gen_num_cases_open();
    int temp;
    cout << "  Enter " << set << " valid case(s) to open: ";
    for (int i; i < set; ++i) {
        cin >> temp;
        valid = case_isValid(temp);
        while (valid == false) {
            cin.clear();
            cout << "  Enter a valid case: ";
            cin  >> temp;
            valid = case_isValid(temp);
        }
        userChoices.push_back(temp);
        update_wall(temp);
    }
    open_case();
    userChoices.clear();
}

void Game::swap_case() {
    string input;
    int pickedCase;
    cout << "  would you like to swap cases (Y/N): ";
    cin >> input;
    if (input == "YES" || input == "Y" || input == "yes" || input == "y") {
        cout << "Which case do you want to swap with: ";
        cin >> pickedCase;
        cout << endl;
        case_isValid(pickedCase);
        modSuite.push_back(heldCase);
        heldCase = suite[pickedCase - 1];
        cout << "  Your case was just swapped" << endl;
    }
    cout << "  Okay nevermind!" << endl;
}

bool Game::get_status() {
    return DEAL;
}

void Game::construct_wall() {
    vector<vector<string>> blank =
    {   {"[          ]",      "0.01"}, {"[          ]",      "1000"},
        {"[          ]",         "1"}, {"[          ]",      "5000"},
        {"[          ]",         "5"}, {"[          ]",     "10000"},
        {"[          ]",        "10"}, {"[          ]",     "25000"},
        {"[          ]",        "25"}, {"[          ]",     "50000"},
        {"[          ]",        "50"}, {"[          ]",     "75000"},
        {"[          ]",        "75"}, {"[          ]",    "100000"},
        {"[          ]",       "100"}, {"[          ]",    "200000"},
        {"[          ]",       "200"}, {"[          ]",    "300000"},
        {"[          ]",       "300"}, {"[          ]",    "400000"},
        {"[          ]",       "400"}, {"[          ]",    "500000"},
        {"[          ]",       "500"}, {"[          ]",    "750000"},
        {"[          ]",       "750"}, {"[          ]",   "1000000"} };
    
    wall = blank;
}

void Game::update_wall(int approved) {
    vector<vector<string>>filled =
     {   {"[$     0.01]",      "0.01"}, {"[$    1,000]",      "1000"},
         {"[$        1]",         "1"}, {"[$    5,000]",      "5000"},
         {"[$        5]",         "5"}, {"[$   10,000]",     "10000"},
         {"[$       10]",        "10"}, {"[$   25,000]",     "25000"},
         {"[$       25]",        "25"}, {"[$   50,000]",     "50000"},
         {"[$       50]",        "50"}, {"[$   75,000]",     "75000"},
         {"[$       75]",        "75"}, {"[$  100,000]",    "100000"},
         {"[$      100]",       "100"}, {"[$  200,000]",    "200000"},
         {"[$      200]",       "200"}, {"[$  300,000]",    "300000"},
         {"[$      300]",       "300"}, {"[$  400,000]",    "400000"},
         {"[$      400]",       "400"}, {"[$  500,000]",    "500000"},
         {"[$      500]",       "500"}, {"[$  750,000]",    "750000"},
         {"[$      750]",      "750"}, {"[$1,000,000]",    "1000000"} };
    
    for (int i = 0; i <wall.size(); i++) {
        if (wall[i][1] == suite[approved - 1].get_caseVal()) {
            wall[i][0] = filled[i][0];
        }
    }
}

void Game::print_wall() {
    cout << endl;
    cout << "    ********GAME WALL********" << endl;
    for (int i = 0; i <wall.size(); ++i) {
        sleep (10000);
        cout << "    "<< wall[i][0] << " " << wall[i + 1][0] << endl;
        ++i;
    }
    cout << "    ************ ************" << endl;
}

double Game::generate_broker_offer() {
    vector<double> range;
    for (size_t i = 0; i < modSuite.size(); ++i) {
        range.push_back(stod(modSuite[i].get_caseVal()));
    }
    sort(range.begin(), range.end());
    int first = range[2];
    int last = range[range.size() - 3];
    size_t fixed = (engine() % ((last) + 1 - first)) + first;
    return fixed;
}

void Game::call_the_broker() {
    string input;
    cout << endl;
    cout << endl;
    cout << "      RING RING RING RING" << endl;
    cout << "      RING RING RING RING" << endl;
    cout << endl;
    sleep(200000);
    cout << "    The banker would like to make you an offer!" << endl;
    cout << "    The offer is :  " << generate_broker_offer() << endl;
    cout << "    You can take the offer or keep playing" << endl;
    cout << "    Enter: DEAL or NO DEAL D/ND: ";
    cin >> input;
    cout << endl;
    cout << endl;
    
    if (input == "DEAL" || input == "D" || input == "yes") {
        cout << "  good choice" << endl;
        initiate_ending();
    }
    else {
        cout << "  Alright, lets keep going" << endl;
    }
   
}
    
void Game::initiate_ending() {
    string input;
    if ((modSuite.size() == 1)) {
        cout << "  We're in the Endgame" << endl;
        if (gen_num_cases_open() == 3) {
            swap_case();
        }
        cout << endl;
        cout << "  Lets open up that final casee" << endl;
        cout << "    Opening case: " << modSuite[0].get_caseFace() << endl;
        cout << "    It contains: $" << modSuite[0].get_caseVal() << endl;
        cout << endl;
        
        cout << "  Let's open your chosen case" << endl;
        cout << "    Opening case: " << heldCase.get_caseFace() << endl;
        cout << "    It contains: $" << heldCase.get_caseVal() << endl;
            cout << "congrats!";
        cout << endl;
        DEAL = true;
    }
    
    if (modSuite.size() == 2 || modSuite.size() == 3) {
        if (gen_num_cases_open() == 3) {
            swap_case();
        }
        cout << endl;
        cout << "    Let's open up those last few cases" << endl;
        cout << "    Opening case: " << modSuite[2].get_caseFace() << endl;
        cout << "    It contains: $" << modSuite[2].get_caseVal() << endl;
        cout << endl;
        
        cout << "    Opening case: " << modSuite[1].get_caseFace() << endl;
        cout << "    It contains: $" << modSuite[1].get_caseVal() << endl;
        cout << endl;
        
        cout << "    Opening case: " << modSuite[0].get_caseFace() << endl;
        cout << "    It contains: $" << modSuite[0].get_caseVal() << endl;
    
    
        cout << "    Let's open your chosen case" << endl;
        cout << "    Opening case: " << heldCase.get_caseFace() << endl;
        cout << "    It contains: $" << heldCase.get_caseVal() << endl;
        cout << endl;
        cout << endl;
        
        cout << "game over periodT" << endl;
        DEAL = true;
    }
}
    
    

