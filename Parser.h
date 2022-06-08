//
// Created by Teagu on 9/21/2021.
//

#ifndef MAIN_CPP_PARSER_H
#define MAIN_CPP_PARSER_H
#include "Token.h"
#include "Rule.h"
#include "Datalog.h"
#include <vector>


class Parser {
private:
    std::vector<Token*> input;
    int tokenCount;
    Rule rules;
    Datalog myData;

public:
    Parser(std::vector<Token*> input){
        this->input = input;
        tokenCount = 0;
    }

    void datalogProgram();
    void schemeList();
    void ruleList();
    void factList();
    void queryList();
    void scheme();
    void fact();
    void rule();
    void query();
    void headPredicate();
    void predicate();
    void predicateList();
    void parameterList();
    void stringList();
    void idList();
    void parameter();
    //addPredicate function
    void match(TokenType type);
    Predicate createPredicate(int index);
    string toString();
    Rule createRule(int index);

    const Datalog &getMyData() const;
};


#endif //MAIN_CPP_PARSER_H
