cmake_minimum_required(VERSION 3.16.3)
project(Project1)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

include_directories(.)

add_executable(Project1
        Automaton.h
        ColonAutomaton.cpp
        ColonAutomaton.h
        ColonDashAutomaton.cpp
        ColonDashAutomaton.h
        Lexer.cpp
        Lexer.h
        main.cpp
        Token.cpp
        Token.h CommaAutomaton.cpp CommaAutomaton.h PeriodAutomaton.cpp PeriodAutomaton.h Q_markAutomaton.cpp Q_markAutomaton.h L_ParenAutomaton.cpp L_ParenAutomaton.h R_Paren.cpp R_Paren.h MultiplyAutomaton.cpp MultiplyAutomaton.h AddAutomaton.cpp AddAutomaton.h FactsAutomaton.cpp FactsAutomaton.h SchemesAutomaton.cpp SchemesAutomaton.h RulesAutomaton.cpp RulesAutomaton.h QueriesAutomaton.cpp QueriesAutomaton.h StringAutomaton.cpp StringAutomaton.h SCommentAutomaton.cpp SCommentAutomaton.h MCommentAutomaton.cpp MCommentAutomaton.h IdAutomaton.cpp IdAutomaton.h UndefinedBlockComment.cpp UndefinedBlockComment.h Parser.cpp Parser.h Predicate.cpp Predicate.h Parameter.cpp Parameter.h Rule.cpp Rule.h Datalog.h Tuple.h Header.h Relations.h Database.h Interpreter.h Graph.h)

