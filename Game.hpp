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

const int SUITE_SIZE = 26;

class Game {
public:
    Game();
    
    void construct_suite();
    
    void shuffle_suite();

    void print_suite();
    
    void modify_caseList(int target);
    
    bool case_isValid(int target);
    
    void hold_case(int target);
    
    void open_case(int target);
    
    void swap_case(int target);
    
    bool get_terminator();

private:
    std::vector<Case> suite;
    std::vector<Case> modSuite;
    bool ender;
    Case heldCase;
    std::vector<double> caseList = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
    14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26};
};

#endif /* Suite_hpp */
