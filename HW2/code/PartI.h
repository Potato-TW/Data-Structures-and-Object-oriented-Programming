#ifndef PARTI_H
#include "SolverBase.h"
#include <vector>
#include <map>
#include <fstream>
#include <utility>
#include <list>
#include <stack>
#include <iostream>
#include <unordered_map>
#include <queue>
#include <map>

using namespace std;

class PartI : public SolverBase
{
private:
    int ver;
    int edge;
    vector<list<pair<int, int>>> graph;
    
    //output
    vector<unordered_map<int, int>> finish;
    vector<map<int, int>> take;
    
    //Topo
    vector<list<pair<int, int>>> to_graph;
    stack<int> topo_order;

    //kosoraju
    vector<list<pair<int, int>>> rev_graph;
    vector<int> path;
    vector<int> visit;
    vector<vector<int>> scc;

    bool iscylic;

public:
    void read(std::string);
    void solve();
    void write(std::string);
    void find(vector<pair<int, int>>& , int , int );

    bool isThereACycle();
    void rec(int, bool*);
    void topologicalSort();
    void showTopo();


    void kosoraju();
    void first_dfs(int);
    void second_dfs(int, int);
    void showKoso();
};

#define PARTI_H
#endif