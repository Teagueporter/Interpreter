//
// Created by Teagu on 10/25/2021.
//

#ifndef MAIN_CPP_INTERPRETER_H
#define MAIN_CPP_INTERPRETER_H
#include "Datalog.h"
#include "Database.h"
#include "Graph.h"
#include <algorithm>

class Interpreter{
private:
    Datalog datalogProgram;
    Database database;
    bool didTupsChange = false;
    size_t totalTupCount = 0;
    vector<vector<Rule>> ruleTree;
public:
    Interpreter(Datalog myDatalog){
        this->datalogProgram = myDatalog;
    }

    void evaluateSchemes(){
        for(auto s : datalogProgram.schemesVector){
            database.addRelation(s.name, Header(s.getParamValues()));
        }
    }
    void evaluateFacts(){
        for(auto f : datalogProgram.factsVector){
            std::string key = f.name;
            database.getMyMap()[key]->insertTuples(f.getParamValues());
        }
    }

    void evaluateAllRules(){
        bool tupsChanged = true;
        size_t prevTups = 0;
        size_t numTups = 0;
        size_t numPass = 0;
        //creating orignial and reverse graphs
        Graph origGraph = Graph(datalogProgram.rulesVector);
        Graph revGraph = Graph(origGraph.adjacencyList);
        revGraph.fillMarkedList();
        origGraph.fillMarkedList();

        //creating postorder and SCC vectors
        vector<int> postOrder;
        vector<vector<int>> SCCvector;

        //calling DepthFirstSearchForest on reverse graph to get post order
        revGraph.DepthFirstSearchForest();
        revGraph.fillMarkedList();
        postOrder = revGraph.postorder;

        //calling DepthFirstSearchForestSCC to find the strongly connected components using the post order
        SCCvector = origGraph.DepthFirstSearchForestSCC(postOrder);

        for(auto tree : SCCvector){
            vector<Rule> rules;
            for(auto comp : tree){
                rules.push_back(datalogProgram.rulesVector.at(comp));
            }
            ruleTree.push_back(rules);
        }

        //printing out graph Evaluation
        cout << "Dependency Graph" << endl;
        cout << origGraph.adjacencytoString();
        cout << endl;

        cout << "Rule Evaluation" << endl;

        //tuples changed && (depends on self || size of SCC > 1)
        for(size_t i = 0; i < ruleTree.size(); i++){
            tupsChanged = true;

            if(ruleTree.at(i).size() == 1 && !origGraph.checkSelf(i)){
                cout << "SCC: ";
                string sccString;
                for (size_t k = 0; k < SCCvector.at(i).size(); ++k) {
                    sccString = "R" + to_string(SCCvector.at(i).at(k)) + ",";
                }
                sccString.pop_back();
                cout << sccString << endl;

                evalRule(ruleTree.at(i));
                numPass = 1;
                cout << numPass << " passes: " << sccString << endl;
            }
            else {
                numPass = 0;
                cout << "SCC: ";
                string sccString;
                for (size_t k = 0; k < SCCvector.at(i).size(); ++k) {
                    sccString += "R" + to_string(SCCvector.at(i).at(k)) + ",";
                }

                sccString.pop_back();
                cout << sccString << endl;

                while (tupsChanged) {

                    //cout << "SCC: R" << endl;

                    evalRule(ruleTree.at(i));

                    //checks if tups changed
                    for (auto mc : database.getMyMap()) {
                        numTups += mc.second->tuple.size();
                    }
                    if (prevTups == numTups) {
                        tupsChanged = false;
                    }
                    prevTups = numTups;
                    numTups = 0;
                    numPass++;
                }
                cout << numPass << " passes: " << sccString << endl;
            }
        }

    }

    void evalRule(vector<Rule> sccForest){
        for(auto r : sccForest){
            didTupsChange = false;
            std::vector<Relations*> vectorR;
            for(size_t i = 0; i < r.bodyPredicates.size(); i++){
                vectorR.push_back(evaluatePredicate(r.bodyPredicates.at(i)));
            }
            std::vector<int> vectorI;
            Relations* newR;
            if(vectorR.size() > 1){
                newR = vectorR.at(0);
                for(size_t k = 1; k < vectorR.size(); k++){
                    newR = newR->join(vectorR.at(k));
                }
            }
            else{
                newR = vectorR.at(0);
            }
            for(size_t hp = 0; hp < r.headPredicate.parameters.size(); hp++){
                for(size_t nrp = 0; nrp < newR->header.attributes.size(); nrp++){
                    if(r.headPredicate.parameters.at(hp).getValue() == newR->header.attributes.at(nrp)){
                        vectorI.push_back(nrp);
                    }
                }
            }

            newR = newR->project(vectorI);
            newR = newR->rename(database.getMyMap()[r.headPredicate.name]->header.attributes);

            cout << r.toString()  << "." << endl;

            string printout = r.toString();

            if(database.getMyMap()[r.headPredicate.name]->tuple.size() > 0){
                std::set<Tuple> newT = database.getMyMap()[r.headPredicate.name]->insertTuples(newR);
                if(newT.size() > 0){
                    cout << Relations(newR->header, newT).toString();
                }
            }
            else{
                database.addRelation(r.headPredicate.name, newR);
                cout << newR->toString();
            }

        }
    }

    void evaluateRulesSCC(Rule rule){
        didTupsChange = false;
        std::vector<Relations*> vectorR;
        for(size_t i = 0; i < rule.bodyPredicates.size(); i++){
            vectorR.push_back(evaluatePredicate(rule.bodyPredicates.at(i)));
        }
        std::vector<int> vectorI;
        Relations* newR;
        if(vectorR.size() > 1){
            newR = vectorR.at(0);
            for(size_t k = 1; k < vectorR.size(); k++){
                newR = newR->join(vectorR.at(k));
            }
        }
        else{
            newR = vectorR.at(0);
        }
        for(size_t hp = 0; hp < rule.headPredicate.parameters.size(); hp++){
            for(size_t nrp = 0; nrp < newR->header.attributes.size(); nrp++){
                if(rule.headPredicate.parameters.at(hp).getValue() == newR->header.attributes.at(nrp)){
                    vectorI.push_back(nrp);
                }
            }
        }

        newR = newR->project(vectorI);
        newR = newR->rename(database.getMyMap()[rule.headPredicate.name]->header.attributes);

        cout << rule.toString()  << "." << endl;

        string printout = rule.toString();

        if(database.getMyMap()[rule.headPredicate.name]->tuple.size() > 0){
            std::set<Tuple> newT = database.getMyMap()[rule.headPredicate.name]->insertTuples(newR);
            if(newT.size() > 0){
                cout << Relations(newR->header, newT).toString();
            }
        }
        else{
            database.addRelation(rule.headPredicate.name, newR);
            cout << newR->toString();
        }

    }

    void evaluateRules(){
        didTupsChange = false;
        for(size_t i = 0; i < datalogProgram.rulesVector.size(); i++){
            std::vector<Relations*> vectorR;
            for(size_t j = 0; j < datalogProgram.rulesVector.at(i).bodyPredicates.size(); j++){
                vectorR.push_back(evaluatePredicate(datalogProgram.rulesVector.at(i).bodyPredicates.at(j)));
            }
            std::vector<int> vectorI;
            Relations* newR;
            if(vectorR.size() > 1){
                newR = vectorR.at(0);
                for(size_t k = 1; k < vectorR.size(); k++){
                    newR = newR->join(vectorR.at(k));
                }
            }
            else{
                newR = vectorR.at(0);
            }
            for(size_t hp = 0; hp < datalogProgram.rulesVector.at(i).headPredicate.parameters.size(); hp++){
                for(size_t nrp = 0; nrp < newR->header.attributes.size(); nrp++){
                    if(datalogProgram.rulesVector.at(i).headPredicate.parameters.at(hp).getValue() == newR->header.attributes.at(nrp)){
                        vectorI.push_back(nrp);
                    }
                }
            }

            newR = newR->project(vectorI);
            newR = newR->rename(database.getMyMap()[datalogProgram.rulesVector.at(i).headPredicate.name]->header.attributes);

            cout << datalogProgram.rulesVector.at(i).toString()  << "." << endl;

            string printout = datalogProgram.rulesVector.at(i).toString();

            if(database.getMyMap()[datalogProgram.rulesVector.at(i).headPredicate.name]->tuple.size() > 0){
                std::set<Tuple> newT = database.getMyMap()[datalogProgram.rulesVector.at(i).headPredicate.name]->insertTuples(newR);
                if(newT.size() > 0){
                    cout << Relations(newR->header, newT).toString();
                }
            }
            else{
                database.addRelation(datalogProgram.rulesVector.at(i).headPredicate.name, newR);
                cout << newR->toString();
            }

        }

    }

    bool isDidTupsChange() const {
        return didTupsChange;
    }

    size_t getTotalTupCount(){
        totalTupCount = database.countTups();
        return totalTupCount;
    }

    void evaluateQueries(){
        Relations* r;
        for(size_t i = 0; i < datalogProgram.queriesVector.size(); i++){
            r = evaluatePredicate(datalogProgram.getQueriesVector().at(i));
            if(r->rsize() > 0){
                std::cout << datalogProgram.queriesVector.at(i).toString();
                std::cout << "? Yes(" << r->rsize() << ")";
                cout << "\n";
                std::cout << r->toString();
            }
            else{
                //todo im going to kill every a
                std::cout << datalogProgram.queriesVector.at(i).toString();
                std::cout << "? No";
                std::cout << r->toString() << endl;
            }
        }
    }

    Relations* evaluatePredicate(const Predicate& p){
        std::vector<int> indexs;
        std::vector<std::string> names;

        Relations* myRelation = (database.getMyMap()[p.getName()]);

        for(size_t i = 0; i < p.getParameters().size(); i++){
            //TODO check if it is a constand
            if(p.getParameters().at(i).type == TokenType::STRING){
                myRelation = myRelation->select(i, p.getParameters().at(i).value);
            }

            else{
                int found = -1;
                    for(size_t j = 0; j < names.size(); j++){
                        if(p.parameters.at(i).value == names.at(j)){
                            found = j;
                            break;
                        }
                    }
                    if(found >= 0 ){
                        myRelation = myRelation->select(i, found);
                    }
                    else{
                        names.push_back(p.parameters.at(i).value);
                        indexs.push_back(i);
                    }
            }
        }
        myRelation = myRelation->project(indexs);
        myRelation = myRelation->rename(names);

        return myRelation;

    }

    std::string toString(){
        return database.toString();
    }

};
#endif //MAIN_CPP_INTERPRETER_H
