//
// Created by Teagu on 9/15/2021.
//

#include "R_Paren.h"

void R_ParenAutomaton::S0(const std::string& input) {
    if (input[index] == ')') {
        inputRead = 1;
    }
    else {
        Serr();
    }
}