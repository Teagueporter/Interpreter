#include "Token.h"
#include <sstream>


using namespace std;

Token::Token(TokenType type, std::string description, int line) {
    // TODO: initialize all member variables

    // converts enums tokens to strings
    this->type = type;
    this->value = description;
    this->line = line;
}
string Token::tokenToString(TokenType type){
    switch(type){
        case TokenType::COLON: return "COLON"; break;
        case TokenType::COLON_DASH: return "COLON_DASH"; break;
        case TokenType::COMMA: return "COMMA"; break;
        case TokenType::PERIOD: return "PERIOD"; break;
        case TokenType::Q_MARK: return "Q_MARK"; break;
        case TokenType::LEFT_PAREN: return "LEFT_PAREN"; break;
        case TokenType::RIGHT_PAREN: return "RIGHT_PAREN"; break;
        case TokenType::MULTIPLY: return "MULTIPLY"; break;
        case TokenType::ADD: return "ADD"; break;
        case TokenType::SCHEMES: return "SCHEMES"; break;
        case TokenType::FACTS: return "FACTS"; break;
        case TokenType::RULES: return "RULES"; break;
        case TokenType::QUERIES: return "QUERIES"; break;
        case TokenType::ID: return "ID"; break;
        case TokenType::STRING: return "STRING"; break;
        case TokenType::COMMENT: return "COMMENT"; break;
        case TokenType::UNDEFINED: return "UNDEFINED"; break;
        case TokenType::_EOF: return "EOF"; break;
        default: return "UNDEFINED"; break;
    }

}
//get description funtion
string Token::getTokenValue(){
    return this->value;
}

TokenType Token::getTokenType(){
    return this->type;
}

string Token::toString() {
    stringstream oss;
    oss << "(" << tokenToString(type) << ",\"" << value << "\"," << line << ")";
    return oss.str();
}

