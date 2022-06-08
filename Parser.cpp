//
// Created by Teagu on 9/21/2021.
//
#include "iostream"
#include "Parser.h"

Predicate Parser::createPredicate(int index){
    //if problem add checker
    if( input.at(index)->getTokenType() == TokenType::FACTS) throw tokenCount;

    Predicate predicate(input.at(index)->getTokenValue());
    index++;
    while(input.at(index)->getTokenType() != TokenType::RIGHT_PAREN){
        if(input.at(index)->getTokenType() == TokenType::ID || input.at(index)->getTokenType() == TokenType::STRING){
            predicate.addToParameterVector(input.at(index)->getTokenValue(), input.at(index)->getTokenType());
        }
        index++;
    }
    return predicate;
}

void Parser::datalogProgram() {
    if(input.at(tokenCount)->getTokenType() == TokenType::SCHEMES){
        ++tokenCount;
    }
    else throw tokenCount;
    if(input.at(tokenCount)->getTokenType() == TokenType::COLON){
        ++tokenCount;
    }
    else throw tokenCount;
    scheme();
    schemeList();
    if(input.at(tokenCount)->getTokenType() == TokenType::FACTS){
        ++tokenCount;
    }
    else throw tokenCount;
    if(input.at(tokenCount)->getTokenType() == TokenType::COLON){
        ++tokenCount;
    }
    else throw tokenCount;
    factList();
    if(input.at(tokenCount)->getTokenType() == TokenType::RULES){
        ++tokenCount;
    }
    else throw tokenCount;
    if(input.at(tokenCount)->getTokenType() == TokenType::COLON){
        ++tokenCount;
    }
    else throw tokenCount;
    ruleList();
    if(input.at(tokenCount)->getTokenType() == TokenType::QUERIES){
        ++tokenCount;
    }
    else throw tokenCount;
    if(input.at(tokenCount)->getTokenType() == TokenType::COLON){
        ++tokenCount;
    }
    else throw tokenCount;
    query();
    queryList();

}
void Parser::schemeList(){
    if(input.at(tokenCount)->getTokenType() != TokenType::FACTS){
        scheme();
        schemeList();
    }
}
void Parser::ruleList(){
    if(input.at(tokenCount)->getTokenType() != TokenType::QUERIES){
        rule();
        ruleList();
    }
}
void Parser::factList(){
    if(input.at(tokenCount)->getTokenType() != TokenType::RULES){
        fact();
        factList();
    }
}
void Parser::queryList(){
    if(input.at(tokenCount)->getTokenType() != TokenType::_EOF){
        query();
        queryList();
    }
}

//ID LEFT_PAREN ID idList RIGHT_PAREN
void Parser::scheme(){
    myData.addToSchemesVector(createPredicate(tokenCount));
    if(input.at(tokenCount)->getTokenType() == TokenType::ID){
       tokenCount++;
    }
    else throw tokenCount;
    if(input.at(tokenCount)->getTokenType() == TokenType::LEFT_PAREN){
        tokenCount++;
    }
    else throw tokenCount;
    if(input.at(tokenCount)->getTokenType() == TokenType::ID){
        tokenCount++;
    }
    else throw tokenCount;
    idList();
    if(input.at(tokenCount)->getTokenType() == TokenType::RIGHT_PAREN){
        tokenCount++;
    }
    else throw tokenCount;
}
//ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD
void Parser::fact(){
    myData.addToFactsVector(createPredicate(tokenCount));
    if(input.at(tokenCount)->getTokenType() == TokenType::ID){
        tokenCount++;
    }
    else throw tokenCount;
    if(input.at(tokenCount)->getTokenType() == TokenType::LEFT_PAREN){
        tokenCount++;
    }
    else throw tokenCount;
    if(input.at(tokenCount)->getTokenType() == TokenType::STRING){
        tokenCount++;
    }
    else throw tokenCount;
    stringList();
    if(input.at(tokenCount)->getTokenType() == TokenType::RIGHT_PAREN){
        tokenCount++;
    }
    else throw tokenCount;
    if(input.at(tokenCount)->getTokenType() == TokenType::PERIOD){
        tokenCount++;
    }
    else throw tokenCount;
}
//headPredicate COLON_DASH predicate predicateList PERIOD
void Parser::rule(){
    //all of this head pred studd is what the Ta was trying to do but I don't think that it
    //works with the create predicate funciton.
    headPredicate();

    if(input.at(tokenCount)->getTokenType() == TokenType::COLON_DASH){
        tokenCount++;
    }
    else throw tokenCount;
    predicate();
    predicateList();

    if(input.at(tokenCount)->getTokenType() == TokenType::PERIOD){
        tokenCount++;
    }
    else throw tokenCount;

    myData.addToRulesVector(rules);
}
//predicate Q_MARK
void Parser::query(){
    myData.addToQueriesVector(createPredicate(tokenCount));
    predicate();
    if(input.at(tokenCount)->getTokenType() == TokenType::Q_MARK){
        tokenCount++;
    }
    else throw tokenCount;
}
//ID LEFT_PAREN ID idList RIGHT_PAREN
void Parser::headPredicate(){
    rules = Rule(createPredicate(tokenCount));
    if(input.at(tokenCount)->getTokenType() == TokenType::ID){
        tokenCount++;
    }
    else throw tokenCount;
    if(input.at(tokenCount)->getTokenType() == TokenType::LEFT_PAREN){
        tokenCount++;
    }
    else throw tokenCount;
    if(input.at(tokenCount)->getTokenType() == TokenType::ID){
        tokenCount++;
    }
    else throw tokenCount;
    idList();
    if(input.at(tokenCount)->getTokenType() == TokenType::RIGHT_PAREN){
        tokenCount++;
    }
    else throw tokenCount;
}
//ID LEFT_PAREN parameter parameterList RIGHT_PAREN
void Parser::predicate(){
    rules.addToBodyPredicateVector(createPredicate(tokenCount));
    if(input.at(tokenCount)->getTokenType() == TokenType::ID){
        tokenCount++;
    }
    else throw tokenCount;
    if(input.at(tokenCount)->getTokenType() == TokenType::LEFT_PAREN){
        tokenCount++;
    }
    else throw tokenCount;
    parameter();
    parameterList();
    if(input.at(tokenCount)->getTokenType() == TokenType::RIGHT_PAREN){
        tokenCount++;
    }
    else throw tokenCount;
}
//predicateList	->	COMMA predicate predicateList | lambda
void Parser::predicateList(){
    if(input.at(tokenCount)->getTokenType() != TokenType::PERIOD){
        if(input.at(tokenCount)->getTokenType() == TokenType::COMMA){
            tokenCount++;
        }
        else throw tokenCount;
        predicate();
//        rules.addToBodyPredicateVector(createPredicate(tokenCount));
        predicateList();
    }
}
//parameterList	-> 	COMMA parameter parameterList | lambda
void Parser::parameterList(){
    if(input.at(tokenCount)->getTokenType() != TokenType::RIGHT_PAREN){
        if(input.at(tokenCount)->getTokenType() == TokenType::COMMA){
            tokenCount++;
        }
        else throw tokenCount;
        parameter();
        parameterList();
    }
}
//stringList	-> 	COMMA STRING stringList | lambda
void Parser::stringList(){
    if(input.at(tokenCount)->getTokenType() != TokenType::RIGHT_PAREN){
        if(input.at(tokenCount)->getTokenType() == TokenType::COMMA){
            tokenCount++;
        }
        else throw tokenCount;
        if(input.at(tokenCount)->getTokenType() == TokenType::STRING){
            tokenCount++;
        }
        else throw tokenCount;
        string();
        stringList();
    }
}
//idList  	-> 	COMMA ID idList | lambda
void Parser::idList(){
    if(input.at(tokenCount)->getTokenType() != TokenType::RIGHT_PAREN){
        if(input.at(tokenCount)->getTokenType() == TokenType::COMMA){
            ++tokenCount;
        }
        else throw tokenCount;
        if(input.at(tokenCount)->getTokenType() == TokenType::ID){
            ++tokenCount;
        }
        else throw tokenCount;
        idList();
    }
}
//parameter	->	STRING | ID
void Parser::parameter(){
        if(input.at(tokenCount)->getTokenType() == TokenType::STRING || input.at(tokenCount)->getTokenType() == TokenType::ID){
            tokenCount++;
        }
        else throw tokenCount;
}

void Parser::match(TokenType type){
    if(input.at(tokenCount)->getTokenType() == type){
        ++tokenCount;
    }
    else throw tokenCount;
}

string Parser::toString() {
    stringstream oss;
    oss << myData.datalogtoString();
    return oss.str();
}

const Datalog &Parser::getMyData() const {
    return myData;
}
