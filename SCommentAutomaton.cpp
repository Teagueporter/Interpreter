//
// Created by Teagu on 9/16/2021.
//

#include "SCommentAutomaton.h"

void SCommentAutomaton::S0(const std::string& input) {
    if (input[index] == '#') {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void SCommentAutomaton::S1(const std::string& input) {
    //check to see in index >= input.size()
    if (input[index] == '\n' || input[index] == EOF) {
        return;
    }
    else{
        inputRead++;
        index++;
        S1(input);

    }
}

