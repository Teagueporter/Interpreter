#include "Lexer.h"
#include "Parser.h"
#include "Interpreter.h"
#include "Database.h"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
    string inputStream = argv[1];
    ifstream ifs (inputStream, ifstream::in);
    //int index = 1;
    //int tupleCount = 1;

    char c;
    string file;

    while(ifs.peek() != EOF){
        c = ifs.get();
        file += c;
    }

    Lexer* lexer = new Lexer();

    lexer->Run(file);

    Parser parse(lexer->getTokenVector());
    try{
        parse.datalogProgram();
        //cout << "Success!" << endl;
        //cout << parse.toString();
    }
    catch(int index){
        //cout << "Failure! \n" << lexer->getTokenVector().at(index)->toString() << endl;
    }

    Datalog datalog = parse.getMyData();
    Interpreter interpreter(datalog);
    interpreter.evaluateSchemes();
    interpreter.evaluateFacts();
    interpreter.evaluateAllRules();
    cout << endl << "Query Evaluation" << endl;
    interpreter.evaluateQueries();
    //cout << interpreter.toString();

    delete lexer;

    return 0;
}