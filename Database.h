//
// Created by Teagu on 10/25/2021.
//

#ifndef MAIN_CPP_DATABASE_H
#define MAIN_CPP_DATABASE_H
#include <map>
#include <iterator>
#include "Relations.h"

class Database {
private:
    //function that add relation to map
    std::map<std::string, Relations*> myMap;
public:
    void addToDatabase(Relations* relation){
        myMap.insert({relation->getName(), relation});
    }

    std::map<std::string, Relations*> &getMyMap(){
        return myMap;
    }

    void addRelation(std::string name, Header header){
        Relations* newRelation = new Relations(header, name);
        myMap.insert({name, newRelation});
    }
    void addRelation(std::string n, Relations *r){
        myMap[n] = r;
    }
    size_t countTups(){
        int count = 0;
        for(auto mapCount : myMap){
           count += mapCount.second->tuple.size();
        }
        return count;
    }

    void addTupleToRelation(std::string name, Tuple myTup){
        myMap.at(name)->insertTuples(myTup);
    }
    std::string toString(){
        std::stringstream oss;
        for(auto m : myMap){
            oss << m.second->toString();
        }
        return oss.str();
    }
    //parseQuery takes queary and parses with relation
};

#endif //MAIN_CPP_DATABASE_H
