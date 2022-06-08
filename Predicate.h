//
// Created by Teagu on 9/28/2021.
//

#ifndef MAIN_CPP_PREDICATE_H
#define MAIN_CPP_PREDICATE_H

#include <vector>
#include "Parameter.h"
#include "Relations.h"

class Predicate {
public:
    std::string name;
    std::vector<Parameter> parameters;
    Predicate() = default;
    Predicate(std::string n) {name = n;}
    Predicate(std::string n, std::string p){name = n; parameters.push_back(p);}

    void addToParameterVector(std::string input, TokenType type){
        Parameter param(input, type);
        parameters.push_back(param);
    }

    const std::vector<Parameter> &getParameters() const {
        return parameters;
    }

    std::vector<std::string> getParamValues(){
        std::vector<std::string> newStrings;
        for(auto s : parameters){
            newStrings.push_back(s.value);
        }
        return newStrings;
    }

    const std::string getName() const {
        return name;
    }

    std::string toString(){
        std::stringstream oss;
        oss << name;
        oss << "(";
        for(size_t i = 0; i < parameters.size(); ++i){
            oss << parameters.at(i).toString();
            if(i != parameters.size() - 1){
                oss << ",";
            }
        }
        oss << ")";
        return oss.str();
    }
//    std::string setParam(){
//        for(size_t i = 0; i < parameters.size(); ++i){
//            domainParameters.at(i) = parameters.at(i);
//    }
};


#endif //MAIN_CPP_PREDICATE_H
