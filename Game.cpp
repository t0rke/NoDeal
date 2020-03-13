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
#include <iomanip>
#include "Game.hpp"
#include "Case.hpp"

using namespace std;

auto seed = std::chrono::system_clock::now().time_since_epoch().count();
std::mt19937_64 engine(seed);

vector<string> wordList = {"Awesome!", "Amazing!", "Great Job!", "Go You!", "Fantastic!", "Yes!", "You got it!", "Groovy!", "You're Killin it", "Huzza!", "voila!", "Whew!", "Stupendous!", "Regrettable!", "Unfortunate!", "Sad!", "It's Okay!", "Keep going!", "Better luck next time!", "Youre still in the running!", "Big Mistake!", "So close yet so far!", "Bad Guess!", "Thats alright!", "Dont cry", "Take a deep breath!", "You Dummy!", "How unfortunate!"};

vector<string> possVal = {"0.01", "1", "5", "10", "25", "50", "75", "100", "200", "300", "400", "500", "750", "1000", "5000", "10000", "25000", "50000", "75000", "100000", "200000", "300000", "400000", "500000", "750000", "1000000"};

int possTwo = engine() % 9 + 1;
int possThree = engine() % 9 + 1;
int possFour = engine() % 9 + 1;

void Game::sleep(unsigned int mseconds) {
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

Game::Game() {
    
}
int Game::get_modSuite_size() {
    return int(modSuite.size());
}


void Game::construct_suite() {
    Case temp;
    std::shuffle(std::begin(possVal), std::end(possVal), engine);
    for (int index = 1; index < SUITE_SIZE; ++index) {
        temp = Case(index, possVal[index - 1]);
        suite.push_back(temp);
    }
    temp = Case(27, "sentinel");
    suite.push_back(temp);
    modSuite.clear();
    modSuite = suite;
    
}

void Game::erase_case(int target) {
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
    bool oneExists = false;
    bool twoExists = false;
    bool threeExists = false;
    bool fourExists = false;
    for (int x = 0; x < modSuite.size(); ++x) {
        if (modSuite[x].get_caseIdentifier() == 4) {
            fourExists = true;
        }
        if (modSuite[x].get_caseIdentifier() == 3) {
            threeExists = true;
        }
        if (modSuite[x].get_caseIdentifier() == 2) {
            twoExists = true;
        }
        if (modSuite[x].get_caseIdentifier() == 1) {
            oneExists = true;
        }
    }
    cout << endl;
    cout << "  There are: {" << modSuite.size() - 1 << "} cases left!" << endl;
    size_t len = modSuite.size();
    size_t i = 0;
    if (fourExists) {
        cout << "  >";
        while (i < len) {
            if (modSuite[i].get_caseIdentifier() == 4) {
                cout << "  " << modSuite[i].get_caseFace();
            }
            ++i;
        }
        cout << endl << endl;
    }
    i = 0;
    if (threeExists) {
        while (i < len) {
            if (modSuite[i].get_caseIdentifier() == 3) {
                cout << "  " << modSuite[i].get_caseFace();
            }
            ++i;
        }
        cout << endl << endl;
    }
    i = 0;
    if (twoExists) {
        cout << "  >";
        while (i < len) {
            if (modSuite[i].get_caseIdentifier() == 2) {
                cout << "  " << modSuite[i].get_caseFace();
            }
            ++i;
        }
        cout << endl << endl;
    }
    i = 0;
    if (oneExists) {
        while (i < len) {
            if (modSuite[i].get_caseIdentifier() == 1) {
                cout << "  " << modSuite[i].get_caseFace();
            }
            ++i;
        }
        cout << endl;
    }
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
        cin.clear();
        cout << " Case: " << pickedCase << " is invalid" << endl;
        cout << "Enter a valid case: " << endl;
        cin  >> pickedCase;
        valid = case_isValid(pickedCase);
    }
    sleep(200000);
    cout << "  You've chosen case:  " << suite[pickedCase - 1].get_caseFace() << endl;
    heldCase = suite[pickedCase - 1];
    heldCaseIden = pickedCase;
    erase_case(pickedCase);
}
void print_accompaniment(string num) {
    if (stod(num) <= 750) {
        size_t num = (engine() % (13 + 1 - 0)) + 0;
        cout << "    " << wordList[num] << endl;
    }
    else {
        size_t num = (engine() % (27 + 1 - 14)) + 14;
        cout << "    " << wordList[num] << endl;
    }
}

void Game::open_case() {
    for (int i = 0; i < userChoices.size(); ++i) {
        cout << endl;
        sleep(200000);
        cout << "    Opening case: " << suite[userChoices[i] - 1].get_caseFace() << endl;
        cout << "    It contains: $" << suite[userChoices[i] - 1].get_caseVal() << endl;
        print_accompaniment(suite[userChoices[i] - 1].get_caseVal());
        sleep(200000);
        erase_case(userChoices[i]);
    }
}

size_t Game::gen_num_cases_open() {
    size_t num = (engine() % (3 + 1 - 1)) + 1;
    return num;
}

void Game::input_case_handler() {
    bool valid;
    int temp;
    int num = howMany[howMany.size() - 1];
    cin.clear();
    cout << "  Enter " << num << " valid case(s) to open: ";
    for (int i = 0; i < num; ++i) {
        cin >> temp;
        valid = case_isValid(temp);
        while (valid == false) {
            cout << "  Case: " << temp << " is invalid" << endl;
            cout << "  Enter a valid case: ";
            cin  >> temp;
            cout << endl;
            valid = case_isValid(temp);
        }
        userChoices.push_back(temp);
        update_wall(temp);
    }
    howMany.pop_back();
    open_case();
    userChoices.clear();
    cin.clear();
    fflush(stdin);
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
    return ALIVE;
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
    cout << "    ********CASH WALL********" << endl;
    for (int i = 0; i <wall.size(); ++i) {
        sleep (10000);
        cout << "    "<< wall[i][0] << " " << wall[i + 1][0] << endl;
        ++i;
    }
    cout << "    ************ ************" << endl;
}

void Game::update_round() {
    ++round;
    if (round == 10) {
        ALIVE = false;
    }
}

void Game::broker_handler() {
    if(round == 2 || round == possTwo ||
       round == possThree || round == possFour) {
        the_broker();
    }
}

double Game::generate_broker_offer() {
    double baseOffer = 0;
    double vals = 0;
    double mean = 0;
    double sub = 1 - (round / 10.00);
    for (size_t i = 0; i < modSuite.size(); ++i) {
        if (modSuite[i].get_caseNumber() != 27) {
            baseOffer += stod(modSuite[i].get_caseVal());
            vals++;
        }
    }
    mean = baseOffer/double(vals);
    return (mean - (mean * sub));
}

void Game::the_broker() {
    cin.clear();
    fflush(stdin);
    string input;
    cout << endl << endl;
    cout << "       RING RING RING RING" << endl;
    cout << "       RING RING RING RING" << endl;
    cout << endl << endl;
    sleep(200000);
    cout << "    The banker would like to make you an offer!" << endl;
    cout << fixed;
    cout << setprecision(2);
    cout << "    The offer is :  $" << generate_broker_offer() << endl;
    cout << "    You can take the offer or keep playing" << endl;
    cout << "    Enter: DEAL or NO DEAL D/ND: ";
    getline(cin, input);
    cout << endl;
    if (input == "DEAL" || input == "D" || input == "deal"
        || input == "d" || input == "yes") {
        cout << "  Good choice" << endl;
        cout << endl;
        cout << "  Now that you've chosen to take the DEAL, let's see " << endl;
        cout << "  was in those remaining cases, and your CHOSEN case" << endl;
        cout << "  to see what you could've won!" << endl;
        ALIVE = false;
    }
    else {
        cout << "  Alright, lets continue." << endl;
    }
}
    
void Game::initiate_ending() {
    string input;
    cout << endl;
    cout << "    Lets open the remaining cases:" << endl;
    for (int i = 0; i< modSuite.size() - 1; ++i) {
        cout << "    Opening case: " << modSuite[i].get_caseFace() << endl;
        cout << "    It contains: $" << modSuite[i].get_caseVal() << endl;
        cout << endl;
    }
    cout << "    Let's open your chosen case" << endl;
    cout << "    Opening case: " << heldCase.get_caseFace() << endl;
    cout << "    YOU HAVE WON: $" << heldCase.get_caseVal();
    print_accompaniment(heldCase.get_caseVal());
    cout << "    Congradulations!";
    cout << endl;
}
    
    

