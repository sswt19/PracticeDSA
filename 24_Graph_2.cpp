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
1. Single source shortest Path
    1.1: Undirected Unweighted Graph : BFS

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
    // 1.1
    void SSSP_Undirected_Unweighted(int src)
    {
        queue<int> q;
        unordered_map<int, int> distance; // Will be used like visited array and store the distance
        unordered_map<int, int> parent;   // Will be used to print the actual path
        q.push(src);
        distance[src] = 0;
        parent[src] = -1;

        while (!q.empty())
        {
            int temp = q.front();
            q.pop();
            for (auto nbr : adjList[temp])
            {
                if (distance.find(nbr) == distance.end())
                {
                    q.push(nbr);
                    distance[nbr] = distance[temp] + 1;
                    parent[nbr] = temp;
                }
            }
        }
    }
};