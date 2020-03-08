//
//  Case.hpp
//  NoDeal
//
//  Created by Suneeth Torke on 3/6/20.
//  Copyright © 2020 Suneeth Torke. All rights reserved.
//

#ifndef Case_hpp
#define Case_hpp

#include <iostream>
#include <string>

// creates the cases and assigns values to each case during each run of the game.

class Case {
public:
    Case();
    
    Case(int case_number, std::string poss_val);
    
    std::string construct_case();
    
    void set_caseFace();
    
    std::string get_caseFace();
    
    int get_caseNumber();
    
    std::string get_caseVal();
    
    int get_caseIdentifier();
    
    
    
private:
    std::string caseFace = "null";
    double caseNumber = -1;
    std::string caseVal;
    int caseIdentifier = -1;
};


#endif /* Case_hpp */
