//
// Created by Teagu on 9/15/2021.
//

#include "L_ParenAutomaton.h"

void L_ParenAutomaton::S0(const std::string& input) {
    if (input[index] == '(') {
        inputRead = 1;
    }
    else {
        Serr();
    }
}