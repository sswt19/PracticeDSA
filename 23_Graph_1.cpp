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
1. Traversal a)BFS b)DFS
2. Connected Components for undirected graphs a)BFS b)DFS
3. Strongly connected components for directed graphs
4. Topological Sort a)BFS b)DFS
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
    //1 Traversal :BFS
    void BFS(int source)
    {
        unordered_map<int, bool> visited;
        queue<int> q;
        //mark and start with source node
        visited[source] = true;
        q.push(source);
        while (!q.empty())
        {
            auto temp = q.front();
            q.pop();
            cout << temp << ",";
            //find every nbr of temp node
            for (auto nbr : adjList[temp])
            {
                // node which is not visited mark it visted and push in queue
                if (!visited[nbr])
                {
                    visited[nbr] = true;
                    q.push(nbr);
                }
            }
        }
    }
    //1 Traversal :DFS
    void DFS(int source)
    {
        unordered_map<int, bool> visited;
        DFS_helper(source, visited);
    }
    void DFS_helper(int source, unordered_map<int, bool> &visited)
    {
        //mark source first
        visited[source] = true;
        cout << source << ",";
        //call DFS helper on every nbr which is not visited
        for (auto nbr : adjList[source])
            if (!visited[nbr])
                DFS_helper(nbr, visited);
    }

    //2 Connected Components:DFS
    int connected_components_DFS()
    {
        int count = 0;
        unordered_map<int, bool> visited; // we can store the visited or the component number in hashmap

        for (auto p : adjList) // call oe each key in adjList and all connected to key will be covered during dfs/bfs
        {
            if (visited.find(p.first) == visited.end())
            {
                count++;
                cout << "Component:" << count << "-->";
                DFS_helper(p.first, visited);
                cout << endl;
            }
        }
        return count;
    }
    //2 Connected Components:BFS
    int connected_components_BFS()
    {
        unordered_map<int, bool> visited; // we can store the visited or the component number in hashmap

        int count = 0;
        for (auto p : adjList)
        {
            if (visited.find(p.first) == visited.end())
            {
                count++;
                cout << "Component:" << count << "-->";

                queue<int> q;
                q.push(p.first);
                visited[p.first] = true;

                while (!q.empty())
                {
                    auto temp = q.front();
                    q.pop();
                    cout << temp << ", ";

                    for (auto vertex : adjList[temp])
                    {
                        if (visited.find(vertex) == visited.end())
                        {
                            visited[vertex] = true;
                            q.push(vertex);
                        }
                    }
                }
                cout << endl;
            }
        }
        return count;
    }

    //4 Topological Sort:BFS
    vector<int> topo_BFS()
    {
        vector<int> topOrder;
        unordered_map<int, int> indegree; // no need of visited hashmap this will work as both indegree count and visited
        for (auto p : adjList)
        {
            if (indegree.find(p.first) == indegree.end())
                indegree[p.first] = 0;
            for (auto nbr : p.second)
                indegree[nbr] = indegree.find(nbr) == indegree.end() ? 1 : indegree[nbr] + 1;
        }
        queue<int> q;
        for (auto p : indegree)
            if (p.second == 0) // start with nodes which donot required by other nodes
                q.push(p.first);
        while (!q.empty())
        {
            int temp = q.front();
            q.pop();
            topOrder.push_back(temp);
            for (auto nbr : adjList[temp])
            {
                indegree[nbr] -= 1; // requirements for each nbr of temp decreased by 1
                if (indegree[nbr] == 0)
                    q.push(nbr);
            }
        }
        if (indegree.size() != topOrder.size()) //there is a cycle, it is not DAG
            return {};
        return topOrder;
    }
    //4 Topological sort DFS
    vector<int> topo_DFS()
    { //check for cycle first if cycle not present then move ahead
        if (cycle())
            return {};
        unordered_map<int, bool> visited;
        vector<int> topOrder; //will contain in reverse order
        for (auto p : adjList)
        {
            if (visited.find(p.first) == visited.end())
                topo_DFSHelper(p.first, topOrder, visited);
        }
        reverse(topOrder.begin(), topOrder.end());
        return topOrder;
    }
    void topo_DFSHelper(int src, vector<int> &topOrder, unordered_map<int, bool> &visited)
    {
        visited[src] = true;
        for (auto nbr : adjList[src])
        {
            if (visited.find(nbr) == visited.end())
                topo_DFSHelper(nbr, topOrder, visited);
        }
        topOrder.push_back(src); // for src->node edge src should be done before node and all it's children
    }
    //5 Cycle
    bool cycle()
    {
        return true;
    }
};