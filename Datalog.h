//
// Created by Teagu on 9/29/2021.
//

#ifndef MAIN_CPP_DATALOG_H
#define MAIN_CPP_DATALOG_H

#include "Predicate.h"
#include "Parameter.h"
#include "Rule.h"
#include <iterator>
#include <set>
#include <sstream>
#include <iostream>

class Datalog {
public:

    Datalog() = default;

    std::vector<Predicate> schemesVector;
    std::vector<Predicate> factsVector;
    std::vector<Predicate> queriesVector;
    std::vector<Rule> rulesVector;
    std::vector<Parameter> factsParam = std::vector<Parameter>();


    //TODO add this to a set
    std::set<std::string> domain;
    std::set<std::string>::iterator itr;

    vector<Predicate> &getQueriesVector() {
        return queriesVector;
    }

    const vector<Rule> &getRulesVector() const {
        return rulesVector;
    }

    void addToSchemesVector(Predicate input){
        schemesVector.push_back(input);
    }
    void addToFactsVector(Predicate input){
        factsVector.push_back(input);
    }
    void addToQueriesVector(Predicate input){
        queriesVector.push_back(input);
    }
    void addToRulesVector(Rule input){
        rulesVector.push_back(input);
    }

    void getParam(){
        for(std::size_t i = 0; i < factsVector.size(); i++){
            string param;
//            param = parameters.at(i).toString();
        }
    }

    std::string datalogtoString(){
        //print out the output
        std::stringstream oss;

        oss << "Schemes(" << schemesVector.size() << "):";
        for(std::size_t i = 0; i < schemesVector.size(); i++){
            oss << endl << "  " << schemesVector.at(i).toString();
        }
        oss << std::endl;

        oss << "Facts(" << factsVector.size() << "):";

        for(std::size_t i = 0; i < factsVector.size(); i++){
            oss << endl << "  " << factsVector.at(i).toString() << ".";
            factsParam = factsVector.at(i).getParameters();
            for(std::size_t j = 0; j < factsParam.size(); j++){
                domain.insert(factsParam.at(j).getValue());
            }

        }

        oss << std::endl;
        oss << "Rules(" << rulesVector.size() << "):" << endl;
        for(std::size_t i = 0; i < rulesVector.size(); i++){
            oss << "  " << rulesVector.at(i).toString() << "." << endl;
        }

        oss << "Queries(" << queriesVector.size() << "):";
        for(std::size_t i = 0; i < queriesVector.size(); i++){
            oss << endl << "  " << queriesVector.at(i).toString() << "?";
        }

        oss << std::endl;
        oss << "Domain(" << domain.size() << "):";
        for(auto param : domain){
            oss << endl << "  " << param;
        }
        return oss.str();
    }


};


#endif //MAIN_CPP_DATALOG_H
