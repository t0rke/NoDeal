//
//  Case.cpp
//  NoDeal
//
//  Created by Suneeth Torke on 3/6/20.
//  Copyright © 2020 Suneeth Torke. All rights reserved.
//

#include "Case.hpp"

using namespace std;

Case::Case() { };

Case::Case(int case_number, string chosen_poss_val) {
    // front end
    caseFace = "[ " + to_string(case_number) +" ]";
    // case identifier
    caseNumber = case_number;
    // monetary amount
    caseVal = chosen_poss_val;
}
int Case::get_caseIdentifier() {
    if (caseNumber > 0 && caseNumber < 7) {
        return 1;
    }
    else if (caseNumber >= 7 && caseNumber < 14) {
        return 2;
    }
    else if (caseNumber >= 14 && caseNumber < 21) {
        return 3;
    }
    else {
        return 4;
    }
}


void Case::set_caseFace() {
    caseFace = "      ";
}

string Case::get_caseFace() {
    return caseFace;
}

int Case::get_caseNumber() {
    return caseNumber;
}

string Case::get_caseVal() {
    return caseVal;
}
