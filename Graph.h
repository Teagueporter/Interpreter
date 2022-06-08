//
// Created by Teagu on 12/6/2021.
//

#ifndef MAIN_CPP_GRAPH_H
#define MAIN_CPP_GRAPH_H

#include <map>
#include <vector>
#include <set>
#include <iterator>
#include <algorithm>
#include "Rule.h"

using namespace std;

class Graph{
public:
    std::map<int, set<int>> adjacencyList;
    vector<bool> marked;
    set<int> visited;
    vector<int> postorder;
    vector<int> scc;
    set<int> dependentRule;
    vector<int> dpRule;
    vector<vector<int>> SSCforest;

    Graph(vector<Rule> ruleVector){
        //makes the original adjacency list
        makeAdjacencylist((ruleVector));
    }
    Graph(std::map<int, set<int>> dependencyList){
        //makes reverse adjacency list
        makeReverseList(dependencyList);
    }
    bool checkSelf(int index){
        bool depend = false;
        int checkLoop = SSCforest.at(index).at(0);
        for(auto r : adjacencyList[checkLoop]){
            if(r == checkLoop){
                depend = true;
                break;
            }
        }
        return depend;
    }
    void makeAdjacencylist(vector<Rule> ruleVector){
        for(size_t i = 0; i < ruleVector.size(); i++){
            set<int> adjacents;
            for(size_t j = 0; j < ruleVector.at(i).bodyPredicates.size(); j++){
                for(size_t k = 0; k < ruleVector.size(); k++){
                    if(ruleVector.at(i).bodyPredicates.at(j).name == ruleVector.at(k).headPredicate.name){
                        adjacents.insert(k);
                        dependentRule.insert(k);
                        dpRule.push_back(k);
                    }
                }
            }
            adjacencyList[i] = adjacents;
            fillMarkedList();
        }
//        for(unsigned int i = 0; i < ruleVector.size(); i++){
//            for(unsigned int j = 0; i < ruleVector.at(i).bodyPredicates.size(); j++){
//                if(ruleVector.at(i).headPredicate.name == ruleVector.at(i).bodyPredicates.at(j).name){
//                    dependentRule.insert(i);
//                }
//            }
//        }

    }
    void makeReverseList(map<int, set<int>> reverseList){
        for(auto r : reverseList){
            adjacencyList[r.first];
        }
        for(auto r : reverseList){
            for(auto item : r.second){
                adjacencyList[item].insert(r.first);
            }
        }
        fillMarkedList();
    }
    void fillMarkedList(){
        //check to see if it works otherwise make an iterator
        marked.clear();
        for(auto m : adjacencyList){
            marked.push_back(false);
        }
    }
    void depthFS(size_t v){
        marked.at(v) = true;
        set<int>:: iterator itr = adjacencyList[v].begin();
        while(itr != adjacencyList[v].end()){
            if(marked.at(*itr) == false){
                depthFS(*itr);
            }
            itr++;
        }
    }
    void DFSSCC(size_t vertex){

        set<int>::iterator iter = adjacencyList[vertex].begin();
        while(iter != adjacencyList[vertex].end()){
            if(visited.insert(*iter).second){
                DFSSCC(*iter);
            }
            iter++;
        }
        scc.push_back(vertex);
    }
    void DepthFirstSearch(size_t vertex){

//        std::map<int, set<int>>:: iterator itr = adjacencyList.find(vertex);
//        set<int>adjacents = itr->second;

        set<int>::iterator iter = adjacencyList[vertex].begin();
        while(iter != adjacencyList[vertex].end()){
            if(visited.insert(*iter).second){
                DepthFirstSearch(*iter);
            }
            iter++;
        }

        postorder.push_back(vertex);

    }
    vector<int> DepthFirstSearchForest(){
        for(auto m : adjacencyList){
            if(visited.insert(m.first).second){
                DepthFirstSearch(m.first);
            }
        }
        reverse(postorder.begin(), postorder.end());
        return postorder;
    }
    vector<vector<int>> DepthFirstSearchForestSCC(vector<int> postorderVector){
        visited.clear();
        for(size_t i = 0; i < postorderVector.size(); i++){
            if(visited.insert(postorderVector.at(i)).second){

                DFSSCC(postorderVector.at(i));

                SSCforest.push_back(scc);
                scc.clear();
            }
        }
        //return SSCforest vector
        return SSCforest;
    }
    string adjacencytoString(){
        stringstream oss;
        stringstream reset;
        for(auto r : adjacencyList){
            reset << "R" << r.first << ":";
            for(auto s : r.second){
                reset << "R" << s << ",";
            }
            string temp = reset.str();
            reset.str("");
            temp = temp.substr(0, temp.rfind(','));
            oss << temp << endl;
        }
            return oss.str();
    }

};



#endif //MAIN_CPP_GRAPH_H
