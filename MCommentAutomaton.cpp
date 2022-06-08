//
// Created by Teagu on 9/16/2021.
//

#include "MCommentAutomaton.h"
void MCommentAutomaton::S0(const std::string& input) {
    if (input[index] == '#') {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void MCommentAutomaton::S1(const std::string& input) {
    //check to see in index >= input.size()

    if (input[index] == '|') {
        inputRead++;
        index++;
        S2(input);
    }
    else{
       Serr();
    }
}
void MCommentAutomaton::S2(const std::string& input) {

    for(size_t i = index; i < input.size(); i++){
        index++;
        if(input[i] != '|'){
            if(input[i] == '\n'){
                newLines++;
            }
            else{
                inputRead++;
            }
        }
        else{
            inputRead++;
            S3(input);
            break;
        }
        if(index >= (int)(input.size())){
            type = TokenType::UNDEFINED;
            return;
        }
    }

}
void MCommentAutomaton::S3(const std::string& input) {
    //check to see in index >= input.size()

    if(index >= (int)input.size()){
        type = TokenType::UNDEFINED;
        return;
    }
    if (input[index] == '#') {
        inputRead++;
        return;
    }
    else{
        Serr();
    }
}
