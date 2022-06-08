//
// Created by Teagu on 9/16/2021.
//

#include "IdAutomaton.h"

void IdAutomaton::S0(const std::string& input) {
    if (isalpha(input[index]) && input.size() > 1) {
        inputRead++;
        index++;
        S1(input);
    }
    else if(isalpha(input[index])){
        inputRead++;
        index++;
    }
    else {
        Serr();
    }
}

void IdAutomaton::S1(const std::string& input) {
    if (isalnum(input[index])) {
        inputRead++;
        index++;
        S1(input);
    }
}