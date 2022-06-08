//
// Created by Teagu on 10/25/2021.
//

#ifndef MAIN_CPP_TUPLE_H
#define MAIN_CPP_TUPLE_H
#include <iostream>
#include <vector>
#include <sstream>

class Tuple {
public:
    std::vector<std::string> values;

    Tuple() = default;

    Tuple(std::vector<std::string> values){
        this->values = values;
    }

    bool operator< (const Tuple &rhs) const {
        return values < rhs.values;
    }

    //get values function returns vector
    std::string getValue(int index){
        return values.at(index);
    }

    void addToTup(std::string value){
        values.push_back(value);
    }
    size_t getSize(){
        return values.size();
    }

    std::string toString(){
        std::stringstream oss;
        for(size_t i = 0; i < values.size(); i++){
            oss << values.at(i);
        }
        return oss.str();
    }
};


#endif //MAIN_CPP_TUPLE_H
