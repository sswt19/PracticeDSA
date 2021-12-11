#include <vector>
#include <iostream>
#include <queue>
#include <stack>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <list>
#include <sstream>
using namespace std;
/*
1. Shortest Path
    1.1: Unweighted Graph
*/
class Graph
{
    unordered_map<int, vector<int>> adjList;

public:
    void insert(int u, int v, bool undirected = false)
    {
        adjList[u].push_back(v);
        if (undirected)
            adjList[v].push_back(u);
    }
};