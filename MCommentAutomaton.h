//
// Created by Teagu on 9/16/2021.
//

#ifndef MAIN_CPP_MCOMMENTAUTOMATON_H
#define MAIN_CPP_MCOMMENTAUTOMATON_H


#include "Automaton.h"

class MCommentAutomaton : public Automaton
{
private:
    void S1(const std::string& input);
    void S2(const std::string& input);
    void S3(const std::string& input);

public:
    MCommentAutomaton() : Automaton(TokenType::COMMENT) {}  // Call the base constructor

    void S0(const std::string& input);
};


#endif //MAIN_CPP_MCOMMENTAUTOMATON_H
