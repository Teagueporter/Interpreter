//
// Created by Teagu on 9/16/2021.
//

#include "StringAutomaton.h"

void StringAutomaton::S0(const std::string& input) {
    if (input[index] == '\'') {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void StringAutomaton::S1(const std::string& input) {
    if (index >= (int)input.size()) {
        type = TokenType::UNDEFINED;
        return;
    }
    if(input[index] == '\n'){
        newLines++;
        inputRead++;
        index++;
        S1(input);
    }
    else if (input[index] != '\''){
        inputRead++;
        index++;
        S1(input);
    }
    else{
        inputRead++;
        index++;
        S2(input);
    }
//
//    if (input[index] == '\'') {
//        inputRead++;
//        index++;
//        S2(input);
//    }
//    else {
//      //count newlines if it is a new line
//        if(input[index] == '\n'){
//            newLines++;
//        }
//        else {
//            inputRead++;
//            index++;
//            S1(input);
//        }
//
//    }
}
void StringAutomaton::S2(const std::string& input){
//    if (index >= (int)input.size()) {
//        return;
//    }
    if(input[index] == '\''){
        inputRead++;
        index++;
        S1(input);
    }
//    else{
//        return;
//    }
}