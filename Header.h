//
// Created by Teagu on 10/25/2021.
//

#ifndef MAIN_CPP_HEADER_H
#define MAIN_CPP_HEADER_H
#include <iostream>
#include <vector>

class Header {
public:

    std::vector<std::string> attributes;

    Header(std::vector<std::string> newAttributes){
        this->attributes = newAttributes;
    }
    Header() = default;

    const size_t getHeaderSize(){
        return attributes.size();
    }
    const std::string getAttribute(int index){
        return attributes.at(index);
    }
    void addAttribute(std::string attribute) {
        attributes.push_back(attribute);
    }
};
#endif //MAIN_CPP_HEADER_H
