//
// Created by Teagu on 9/15/2021.
//

#ifndef PROJECT1_R_PAREN_H
#define PROJECT1_R_PAREN_H



#include "Automaton.h"

class R_ParenAutomaton : public Automaton
{
public:
    R_ParenAutomaton() : Automaton(TokenType::RIGHT_PAREN) {}  // Call the base constructor

    void S0(const std::string& input);
};


#endif //PROJECT1_R_PAREN_H
