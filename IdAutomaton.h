//
// Created by Teagu on 9/16/2021.
//

#ifndef MAIN_CPP_IDAUTOMATON_H
#define MAIN_CPP_IDAUTOMATON_H


#include "Automaton.h"

class IdAutomaton : public Automaton
{
private:
    void S1(const std::string& input);

public:
    IdAutomaton() : Automaton(TokenType::ID) {}  // Call the base constructor

    void S0(const std::string& input);
};


#endif //MAIN_CPP_IDAUTOMATON_H
