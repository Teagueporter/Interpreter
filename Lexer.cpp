#include "Lexer.h"
#include "Token.h"
#include "CommaAutomaton.h"
#include "ColonAutomaton.h"
#include "ColonDashAutomaton.h"
#include "QueriesAutomaton.h"
#include "Q_markAutomaton.h"
#include "L_ParenAutomaton.h"
#include "R_Paren.h"
#include "AddAutomaton.h"
#include "MultiplyAutomaton.h"
#include "SchemesAutomaton.h"
#include "PeriodAutomaton.h"
#include "FactsAutomaton.h"
#include "RulesAutomaton.h"
#include "StringAutomaton.h"
#include "IdAutomaton.h"
#include "SCommentAutomaton.h"
#include "MCommentAutomaton.h"
#include "UndefinedBlockComment.h"
#include <cctype>
#include <sstream>

using namespace std;

Lexer::Lexer() {
    CreateAutomata();
}

Lexer::~Lexer() {
    // TODO: need to clean up the memory in `automata` and `tokens`

}

void Lexer::CreateAutomata() {
   automata.push_back(new ColonAutomaton());
   automata.push_back(new ColonDashAutomaton());
   automata.push_back(new CommaAutomaton());
   automata.push_back(new PeriodAutomaton());
   automata.push_back(new Q_markAutomaton());
   automata.push_back(new L_ParenAutomaton());
   automata.push_back(new R_ParenAutomaton());
   automata.push_back(new MultiplyAutomaton());
   automata.push_back(new AddAutomaton());
   automata.push_back(new RulesAutomaton());
   automata.push_back(new SchemesAutomaton());
   automata.push_back(new FactsAutomaton());
   automata.push_back(new QueriesAutomaton());
   automata.push_back(new IdAutomaton());
   automata.push_back(new StringAutomaton());
   automata.push_back(new UndefinedBlockAutomaton());
   automata.push_back(new SCommentAutomaton());
   automata.push_back(new MCommentAutomaton());

}

void Lexer::Run(std::string& input) {

    lineNumber = 1;
    int maxRead;
    int inputRead = 0;

    while(input.size() > 0){

        maxRead = 0;

        Automaton* maxAutomaton;
        maxAutomaton = automata.front();

        while(isspace(input[0])){
            if(input[0] == '\n') {
                lineNumber++;
            }
            input.erase(0,1);
        }
        for(size_t i = 0; i < automata.size(); ++i) {

            inputRead = automata.at(i)->Start(input);
            //inputRead += automata.at(i)->NewLinesRead();
            if(inputRead > maxRead) {
                maxRead = inputRead;
                maxAutomaton = automata.at(i);
            }
        }

        if (maxRead > 0){
            //determine if it is a comment and don't add it
            if(maxAutomaton->CreateToken(input.substr(0, maxRead), lineNumber)->getTokenType() != TokenType::COMMENT){
                tokens.push_back(maxAutomaton->CreateToken(input.substr(0, maxRead), lineNumber));
                lineNumber += maxAutomaton->NewLinesRead();
            }
        }

        else {
            if (input.size() > 0){
                maxRead = 1;
                tokens.push_back(new Token(TokenType::UNDEFINED, input.substr(0, maxRead), lineNumber));
            }
        }

        input.erase(0, maxRead);

    }

    //TODO: add eof token to the token list
    tokens.push_back(new Token(TokenType::_EOF, "", lineNumber));

}
string Lexer::toStringLexar(){
    stringstream oss;
    for(size_t i = 0; i < tokens.size(); ++i){
        oss << tokens.at(i)->toString() << endl;
    }
    oss << "Total Tokens = " << tokens.size();
    return oss.str();
}


