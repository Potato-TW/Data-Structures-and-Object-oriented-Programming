#ifndef PARTII_H
#include "SolverBase.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <list>
#include <utility>
#include <climits>
#include <fstream>

using namespace std;

class PartII : public SolverBase
{
private:
    int ver;
    int edge;
    int ans_di;
    int ans_be;
    std::vector<std::list<std::pair<int, int>>> di_graph;
    std::vector<std::list<std::pair<int, int>>> be_graph;
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>> > min_heap;   //first=dis second=node
    std::vector<int> distance;


public:
    void read(std::string);
    void solve();
    void write(std::string);

    void dis_init();
    void heap_init();
    void heap_update();
    void dijkstra();
    void bellman();
};


#define PARTII_H
#endif