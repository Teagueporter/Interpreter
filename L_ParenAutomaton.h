//
// Created by Teagu on 9/15/2021.
//

#ifndef PROJECT1_L_PARENAUTOMATON_H
#define PROJECT1_L_PARENAUTOMATON_H



#include "Automaton.h"

class L_ParenAutomaton : public Automaton
{
public:
    L_ParenAutomaton() : Automaton(TokenType::LEFT_PAREN) {}  // Call the base constructor

    void S0(const std::string& input);
};


#endif //PROJECT1_L_PARENAUTOMATON_H
