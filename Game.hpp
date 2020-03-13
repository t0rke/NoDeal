//
//  Suite.hpp
//  NoDeal
//
//  Created by Suneeth Torke on 3/6/20.
//  Copyright © 2020 Suneeth Torke. All rights reserved.
//

#ifndef Suite_hpp
#define Suite_hpp
#include "Case.hpp"
#include <vector>

const int SUITE_SIZE = 27;

class Game {
public:
    Game();
    
    void sleep(unsigned int mseconds);
    
    //suite funcs
    void construct_suite();
    
    int get_modSuite_size();
    
    void shuffle_suite();
    
    void split_suite();

    void print_suite();
    
    void print_suite_vals();
    
    // wall funcs
    void construct_wall();
    
    void update_wall(int approved);
    
    void print_wall();
    
    size_t gen_num_cases_open();
    
    void input_case_handler();
    
    std::vector<Case> find_row(int target);
    
    void erase_case(int target);
    
    void modify_caseList(int target);
    
    bool case_isValid(int target);
    
    void hold_case();
    
    void open_case();
    
    void swap_case();
    
    void initiate_ending();
    
    bool get_status();
    
    void update_round();
    
    //broker funcs
    void broker_handler();
    
    void the_broker();
    
    double generate_broker_offer();
    
    
private:
    std::vector<Case> suite;
    std::vector<Case> modSuite;
    bool ALIVE = true;
    Case heldCase;
    int heldCaseIden;
    std::vector<double> caseList = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
    14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26};
    std::vector<int> howMany = {1, 1, 1, 1, 2, 3, 4, 5, 6};
    std::vector<std::vector<std::string>> wall;
    int caseListsize = caseList.size();
    std::vector<int> userChoices;
    double round = 1;
};

#endif /* Suite_hpp */
