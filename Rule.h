//
// Created by Teagu on 9/29/2021.
//

#ifndef MAIN_CPP_RULE_H
#define MAIN_CPP_RULE_H

#include "Predicate.h"

class Rule {
public:
    Predicate headPredicate;
    std::vector<Predicate> bodyPredicates;

    Rule() = default;
    Rule(Predicate n) {headPredicate = n;}
    Rule(Predicate n, Predicate p){headPredicate = n; bodyPredicates.push_back(p);}

    void addToBodyPredicateVector(Predicate predicateInput){
        bodyPredicates.push_back(predicateInput);
    }
//    void setHeadPredicate(Predicate predicate){
//        headPredicate = predicate;
//    }
//    void clear(){
//        bodyPredicates.clear();
//    }

    std::string toString(){
        std::stringstream oss;
        //call tostring on headPredicate
        oss << headPredicate.toString();
        oss << " :- ";
        for(size_t i = 0; i < bodyPredicates.size(); ++i){
            oss << bodyPredicates.at(i).toString();
            if(i != bodyPredicates.size() - 1){
                oss << ",";
            }
        }
        return oss.str();
    }

};


#endif //MAIN_CPP_RULE_H
