//
// Created by Teagu on 9/17/2021.
//

#include "UndefinedBlockComment.h"

void UndefinedBlockAutomaton::S0(const std::string &input) {
    if (input[index] == '#'){
        inputRead++;
        index++;
        S1(input);
    }
    else{
        Serr();
    }

}
void UndefinedBlockAutomaton::S1(const std::string &input) {
    if(input[index] == '|'){
        inputRead++;
        index++;
        S2(input);
    }
}
void UndefinedBlockAutomaton::S2(const std::string &input) {
    if(input[index] == '|'){
        inputRead++;
        index++;
        S3(input);
    }
    else if(index >= (int)input.size()){
        return;
    }
    else{
        if(input[index] == '\n')
            newLines++;
        inputRead++;
        index++;
        S2(input);
    }
}
void UndefinedBlockAutomaton::S3(const std::string &input) {
    if (input[index] == '#'){
        Serr();
    }
    else{
        if(input[index] == '\n')
            newLines++;
        inputRead++;
        index++;
        S2(input);
    }

}