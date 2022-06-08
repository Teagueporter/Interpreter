//
// Created by Teagu on 9/29/2021.
//

#ifndef MAIN_CPP_PARAMETER_H
#define MAIN_CPP_PARAMETER_H

#include <sstream>
#include "Token.h"

class Parameter {
public:
    std::string value;
    bool isConstant;
    TokenType type;


    Parameter(std::string v) {
        value = v;
    }
    Parameter(std::string v, TokenType t) {
        value = v;
        type = t;
    }
    std::string toString(){return value;}
    const std::string &getValue() const {
        return value;
    }


};


#endif //MAIN_CPP_PARAMETER_H
