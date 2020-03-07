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

Case::Case(int case_number, int chosen_poss_val) {
    // front end
    caseFace = "[=" + to_string(case_number) +"=]";
    // case identifier
    caseNumber = case_number;
    // monetary amount
    caseVal = chosen_poss_val;
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

double Case::get_caseVal() {
    return caseVal;
}
