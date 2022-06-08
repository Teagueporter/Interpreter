//
// Created by Teagu on 9/17/2021.
//

#ifndef MAIN_CPP_UNDEFINEDBLOCKCOMMENT_H
#define MAIN_CPP_UNDEFINEDBLOCKCOMMENT_H


#include "Automaton.h"

class UndefinedBlockAutomaton : public Automaton
{
private:
    void S1(const std::string& input);
    void S2(const std::string& input);
    void S3(const std::string& input);

public:
    UndefinedBlockAutomaton() : Automaton(TokenType::COMMENT) {}  // Call the base constructor

    void S0(const std::string& input);
};


#endif //MAIN_CPP_UNDEFINEDBLOCKCOMMENT_H
