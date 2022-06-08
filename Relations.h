//
// Created by Teagu on 10/25/2021.
//

#ifndef MAIN_CPP_RELATIONS_H
#define MAIN_CPP_RELATIONS_H
#include <iostream>
#include <vector>
#include <set>
#include <sstream>
#include "Tuple.h"
#include "Header.h"

using namespace std;

class Relations{
public:
    //Declaring variables
    std::string name;
    std::set<Tuple> tuple{};
    Header header;


    //Constructor for empty relation
    Relations(Header newHeader, std::string Rname){
        name = Rname;
        header = newHeader;
    }

    Relations(Header newHeader, set<Tuple> setTups){
        header = newHeader;
        tuple = setTups;
    }

    Relations(Header newHeader){
        header = newHeader;
    }

    Relations() = default;


    bool insertTuples(Tuple tup){
        return tuple.insert(tup).second;
    }

    set<Tuple> insertTuples(Relations* r){
        set<Tuple> newT;
        for(Tuple t : r->tuple){
            if(this->insertTuples(t)){
                newT.insert(t);
            }
        }
        return newT;
    }

    Relations* select(int index, std::string value){
        //create new relation
        Relations* newRelation = new Relations(this->header, this->name);//**********************
        for(auto i : tuple){
            if(i.getValue(index) == value){
                newRelation->insertTuples(i);
            }
        }
        return newRelation;
    }

    Relations* select(int index, int index1){
        Relations* newRelation = new Relations(this->header, this->name);
        for (auto i: tuple) {
            if (i.getValue(index) == i.getValue(index1)) {
                newRelation->insertTuples(i);
            }
        }
        return newRelation;
    }
    Relations* project(std::vector<int> indexs){
        std::vector<std::string> newHeaders;
        for(auto i : indexs){
            newHeaders.push_back(this->header.attributes.at(i));
        }
        Relations* newRelation = new Relations(Header(newHeaders), this->name);
        for(auto t : tuple){
            Tuple myTuple;
            for(auto i : indexs){
                myTuple.addToTup(t.getValue(i));
            }
            newRelation->insertTuples(myTuple);
        }
        return newRelation;

    }
    Relations* rename(std::vector<std::string> attributes){
        //iterate through everything and swap positions
        Header myHeader = Header(attributes);
        header = myHeader;
        return this;
    }

    Relations* join(Relations* r){
        vector<pair<unsigned int, unsigned int>> index;
        Header myHeader;
        myHeader = combineHeaders(this->header, r->header, index);

        Relations* myRelation = new Relations(myHeader);
        for(auto tuples1 : this->tuple){
            for(auto tuples2 : r->tuple){
                if(isJoin(tuples1, tuples2, index)){
                    Tuple newTup = Tuple(tuples1.values);
                    for(size_t j = 0; j < tuples2.getSize(); j++){
                        bool canAdd = true;
                        for(size_t k = 0; k < index.size(); k++){
                            if(j == index.at(k).second){
                                canAdd = false;
                                break;
                            }
                        }
                        if(canAdd){
                            newTup.addToTup((tuples2.getValue(j)));
                        }
                    }
                    myRelation->insertTuples(newTup);
                }

            }

        }
        return myRelation;
    }

    bool isJoin(Tuple& tuple1, Tuple& tuple2, vector<pair<unsigned int, unsigned int>>& index){

        for(size_t i = 0; i < index.size(); i++){
            if(tuple1.values.at(index.at(i).first) != tuple2.values.at(index.at(i).second)){
                return false;
            }
        }
        return true;
    }

    //maybe pass by reference in more info like vector that stores the second headers indexes
    Header combineHeaders(Header h1, Header h2, vector<pair<unsigned int, unsigned int>>& matches){
        Header newHeader = h1;
        for(size_t i = 0; i < h2.getHeaderSize(); i++){
            bool shouldAdd = true;
            for(size_t j = 0; j < h1.getHeaderSize(); j++){
                if(h2.getAttribute(i) == h1.getAttribute(j)){
                    shouldAdd = false;
                    matches.push_back({j,i});
                }
            }
            if(shouldAdd){
                newHeader.addAttribute(h2.getAttribute(i));
            }
        }
        return newHeader;
    }

    bool unite(Relations otherRelation){
        bool addedTuples = false;
        for(const auto& tups : otherRelation.tuple){
            if(tuple.insert(tups).second){
                addedTuples = true;
                cout << tupToString(tups);
            }
        }
        return addedTuples;
    }

    //make a new tuple to string
    string tupToString(Tuple tup){
        std::stringstream oss;
        bool isSizeZero = false;
                oss << std::endl;
                oss << "  ";
                for (size_t i = 0; i < header.getHeaderSize(); i++) {
                    oss << header.getAttribute(i) << "=" << tup.getValue(i);
                    if (i != header.getHeaderSize() - 1) {
                        oss << ", ";
                    }
                }
                if(tup.getSize() > 0){
                    isSizeZero = true;
                }
        if(isSizeZero == true){oss << std::endl;}

        return oss.str();
//        stringstream oss;
//        for(size_t i = 0; i < tup.getSize(); i++){
//            oss << " " << header.getAttribute(i) << "=" << tup.getValue(i);
//        }
//        return oss.str();
    }

    //possible getters and setters
    std::string getName(){
        return name;
    }
    void setName(std::string newName){
        name = newName;
    }

    int rsize(){
        return tuple.size();
    }




    //toString to print out the Tuples
    std::string toString(){
        std::stringstream oss;
        bool isSizeZero = false;
        size_t counter = 0;
        if(this->rsize() >= 0) {
            for (auto param : tuple) {
                if(tuple.size() > 0) {
                    oss << "  ";
                }
                for (size_t i = 0; i < header.getHeaderSize(); i++) {
                    oss << header.getAttribute(i) << "=" << param.getValue(i);
                    if (i != header.getHeaderSize() - 1) {
                        oss << ", ";
                    }
                    else if(counter != tuple.size() - 1){
                        oss << "\n";
                    }
                }
                if(param.getSize() > 0){
                    isSizeZero = true;
                }
                counter++;
            }
        }
        if(isSizeZero == true){oss << "\n";}

        return oss.str();
    }




};

#endif //MAIN_CPP_RELATIONS_H
