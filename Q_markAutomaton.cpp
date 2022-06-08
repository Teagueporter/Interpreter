//
// Created by Teagu on 9/15/2021.
//

#include "Q_markAutomaton.h"

void Q_markAutomaton::S0(const std::string& input) {
    if (input[index] == '?') {
        inputRead = 1;
    }
    else {
        Serr();
    }
}