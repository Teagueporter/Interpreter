#ifndef TOKEN_H
#define TOKEN_H
#include <string>

using namespace std;

enum class TokenType {
    COLON,
    COLON_DASH,
    COMMA,
    PERIOD,
    Q_MARK,
    LEFT_PAREN,
    RIGHT_PAREN,
    MULTIPLY,
    ADD,
    SCHEMES,
    FACTS,
    RULES,
    QUERIES,
    ID,
    STRING,
    COMMENT,
    UNDEFINED,
    _EOF
};

class Token
{
private:
    // TODO: add member variables for information needed by Token
    TokenType type;
    string value;
    int line;

public:
    Token(TokenType type, std::string description, int line);
    TokenType getTokenType();
    string getTokenValue();

    string tokenToString(TokenType type);
    string toString();
    // TODO: add other needed methods
};

#endif // TOKEN_H

