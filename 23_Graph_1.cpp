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
1. Traversal
    i)BFS ii)DFS

2. Connected Components for undirected graphs
    i)BFS ii)DFS

3. Detect Cycle
    a) Undirected   i) BFS ii) DFS
    b) directed     i) BFS ii) DFS

4. Topological Sort(DAG)
    i)BFS ii)DFS

5. Bipartite Graph(Two sets of vertics and only edeges b/w both sets are present)

6. Clone a Graph

7. Strongly connected components for directed graphs(At the end of this file)

when to use, how to use, directed or undirected graphs
MST and DSU only for directed graphs
cycle in directed and undirected using BFS and DFS
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
    // 1 Traversal
    // BFS
    void BFS(int source)
    {
        unordered_map<int, bool> visited;
        BFS_helper(source, visited);
    }
    void BFS_helper(int source, unordered_map<int, bool> &visited)
    {
        queue<int> q;
        // mark and start with source node
        visited[source] = true;
        q.push(source);
        while (!q.empty())
        {
            auto temp = q.front();
            q.pop();
            // find every nbr of temp node
            for (auto nbr : adjList[temp]) // node which is not visited mark it visted and push in queue
                if (!visited[nbr])
                {
                    visited[nbr] = true;
                    q.push(nbr);
                }
        }
    }
    // DFS
    void DFS(int source)
    {
        unordered_map<int, bool> visited;
        DFS_helper(source, visited);
    }
    void DFS_helper(int source, unordered_map<int, bool> &visited)
    {
        // mark source first
        visited[source] = true;

        // call DFS helper on every nbr which is not visited
        for (auto nbr : adjList[source])
            if (!visited[nbr])
                DFS_helper(nbr, visited);
    }

    // 2 Connected Components
    // DFS
    int connected_components_DFS()
    {
        int count = 0;
        unordered_map<int, bool> visited; // we can store the visited or the component number in hashmap

        for (auto p : adjList) // call on each key in adjList and all connected to key will be covered during dfs/bfs
            if (visited.find(p.first) == visited.end())
            {
                count++;
                DFS_helper(p.first, visited);
            }

        return count;
    }
    // BFS
    int connected_components_BFS()
    {
        unordered_map<int, bool> visited; // we can store the visited or the component number in hashmap

        int count = 0;
        for (auto p : adjList) // call on each key in adjList and all connected to key will be covered during dfs/bfs
            if (visited.find(p.first) == visited.end())
            {
                count++;
                BFS_helper(p.first, visited);
            }

        return count;
    }

    // 3A) Detect Cycle: Undireced Graph
    // BFS
    bool cycle_check_BFS()
    {
        unordered_map<int, int> parent; // a->b, if b is found using a then parent of b is a
        // parent is stored because:For Ex: G:2-3 2 is marked then we go to 3 and 3's nbr 2 is already visited we will call cycle which will be wrong
        for (auto p : adjList)
        {
            // check cycle in each component
            auto node = p.first;
            if (parent.find(node) == parent.end())
            {
                queue<int> q;
                // mark the parent, will be used same as visited
                parent[node] = node;
                q.push(node);
                while (!q.empty())
                {
                    auto top = q.front();
                    q.pop();
                    for (auto nbr : adjList[top])
                    {
                        if (parent.find(nbr) == parent.end())
                        {
                            parent[nbr] = top;
                            q.push(nbr);
                        }
                        else if (parent[top] != nbr) // if the nbr is not the parent of current node then there is a cycle
                            return true;
                    }
                }
            }
        }
        return false;
    }
    // DFS
    bool dfs_isCycle(vector<int> adj[])
    {
        unordered_map<int, bool> visited;
        for (auto p : adjList) // check in all components
            if (visited.find(p.first) == visited.end() && isCycle_dfs_helper(p.first, p.first, visited))
                return true;

        return false;
    }
    bool isCycle_dfs_helper(int node, int parent, unordered_map<int, bool> &visited)
    {
        // mark it visited
        visited[node] = true;
        for (auto nbr : adjList[node])
        {
            if (visited.find(nbr) == visited.end())
            {
                if (isCycle_dfs_helper(nbr, node, visited))
                    return true; // this return true very important
            }
            else if (nbr != parent) // if nbr is visited already and is not the parent then there is cycle
                return true;
        }
        return false;
    }

    // 3B) Detect Cycle:  Directed Graph
    // BFS
    bool topo_BFS_Directed_Checkcycle()
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
                indegree[nbr] -= 1;     // requirements for each nbr of temp decreased by 1
                if (indegree[nbr] == 0) // it's parents are completed now we can process it
                    q.push(nbr);
            }
        }
        if (indegree.size() != topOrder.size()) // there is a cycle, it is not DAG
            return true;
        return false;
    }
    // DFS
    bool DFS_Directed_Checkcycle_helper(int src, unordered_map<int, bool> &visited, unordered_map<int, bool> &path)
    {
        // mark it and add current node is in path
        visited[src] = true;
        path[src] = true;

        for (auto nbr : adjList[src])
        {
            if (visited.find(nbr) == visited.end())
            {
                bool cyclePresent = DFS_Directed_Checkcycle_helper(nbr, visited, path);
                if (cyclePresent)
                    return cyclePresent;
            }
            else if (path.find(nbr) != path.end()) // this means nbr is already visited and there is back edge from src to nbr causing the cycle because nbr is present in path map
                return true;
        }
        // every path from current node is done hence remove it
        path.erase(src); // don't forget

        return false;
    }
    bool DFS_Directed_Checkcycle()
    {
        unordered_map<int, bool> visited;
        unordered_map<int, bool> path; // this is stored to check if there is back edge to node which is already in path
        for (auto p : adjList)         // Check Every component
            if (visited.find(p.first) == visited.end() && DFS_Directed_Checkcycle_helper(p.first, visited, path))
                return true;

        return false;
    }

    // 4 Topological Sort:BFS
    vector<int> topo_BFS()
    {
        vector<int> topOrder;
        unordered_map<int, int> indegree; // no need of visited hashmap this will work as both indegree count and visited
        for (auto p : adjList)
        {
            if (indegree.find(p.first) == indegree.end())
                indegree[p.first] = 0;
            for (auto nbr : p.second)
                indegree[nbr] = indegree.find(nbr) == indegree.end() ? 1 : indegree[nbr] + 1; // 1 default because there is edge from p.first->nbr
        }
        queue<int> q;
        for (auto p : indegree)
            if (p.second == 0) // start with nodes which are not required by other nodes i.e idegree 0
                q.push(p.first);

        while (!q.empty())
        {
            int temp = q.front();
            q.pop();
            topOrder.push_back(temp); // push current node with 0 indegree to topOrder
            for (auto nbr : adjList[temp])
            {
                indegree[nbr] -= 1; // requirements for each nbr of temp decreased by 1
                if (indegree[nbr] == 0)
                    q.push(nbr);
            }
        }
        if (indegree.size() != topOrder.size()) // there is a cycle, it is not DAG
            return {};
        return topOrder;
    }
    // 4 Topological sort DFS
    vector<int> topo_DFS()
    { // check for cycle first if cycle not present then move ahead
        if (DFS_Directed_Checkcycle())
            return {};
        unordered_map<int, bool> visited;
        vector<int> topOrder; // will contain in reverse order

        for (auto p : adjList) // on all components
            if (visited.find(p.first) == visited.end())
                topo_DFSHelper(p.first, topOrder, visited);

        reverse(topOrder.begin(), topOrder.end());
        return topOrder;
    }
    void topo_DFSHelper(int src, vector<int> &topOrder, unordered_map<int, bool> &visited)
    {
        visited[src] = true;
        for (auto nbr : adjList[src])
            if (visited.find(nbr) == visited.end())
                topo_DFSHelper(nbr, topOrder, visited);

        // push the current node only after it's subtree is completed
        topOrder.push_back(src); // for src->node edge src should be done before node and all it's children
    }

    // 6 Bipartitie
    bool isBipartite_BFS()
    {
        unordered_map<int, int> colored; // instead of visited we will store the color
        for (auto p : adjList)           // check in all components
        {
            if (colored.find(p.first) == colored.end())
            {
                queue<int> q;
                q.push(p.first);
                colored[p.first] = 0;
                while (!q.empty())
                {
                    auto parent = q.front();
                    q.pop();
                    for (auto nbr : adjList[parent])
                    {
                        if (colored.find(nbr) == colored.end()) // if not visited then color it opposite to parent
                        {
                            q.push(nbr);
                            colored[nbr] = 1 - colored[parent];
                        }
                        else if (colored[nbr] == colored[parent]) // if visited check if color is same as parent
                            return false;
                    }
                }
            }
        }
        return true;
    }
};

// 7 Clone the graph: here each node is represented by Node object
/*
unordered_map<int,vector<int>> can be copied easily through traversing the adjList and inserting the same way ori was created
*/
class Node
{
public:
    int val;
    vector<Node *> neighbors;

    Node()
    {
        val = 0;
        neighbors = vector<Node *>();
    }

    Node(int _val)
    {
        val = _val;
        neighbors = vector<Node *>();
    }

    Node(int _val, vector<Node *> _neighbors)
    {
        val = _val;
        neighbors = _neighbors;
    }
};

class Solution
{
public:
    Node *cloneGraph(Node *node)
    {
        if (!node)
            return NULL;

        unordered_map<Node *, Node *> clone; // this will be used for mapping from ori to copy
        clone[node] = new Node(node->val);
        // BFS traversal
        queue<Node *> Q;
        Q.push(node);

        while (!Q.empty())
        {
            Node *parent = Q.front();
            Q.pop();

            for (auto nbr : parent->neighbors)
            {
                if (clone.find(nbr) == clone.end())
                {
                    clone[nbr] = new Node(nbr->val); // vertices are mapped here
                    Q.push(nbr);
                }
                clone[parent]->neighbors.push_back(clone[nbr]); // every edge is mapped here
            }
        }

        return clone[node];
    }
};

// 3 SCC
// Create reverse graph
// do topological sort on ori graph
// do dfs on reverse graph using the order of topological sort
// nodes covered in each dfs iteration will be one SCC
class SCC
{
    unordered_map<int, vector<int>> adjList;
    unordered_map<int, vector<int>> revAdjList;

public:
    void insert(int u, int v)
    {
        adjList[u].push_back(v);
        revAdjList[v].push_back(u);
    }

    void dfs_topoOrder(int src, stack<int> &topo, unordered_map<int, bool> &visited)
    {
        visited[src] = true;
        for (auto nbr : adjList[src])
            if (visited.find(nbr) == visited.end())
                dfs_topoOrder(nbr, topo, visited);
        topo.push(src);
    }
    void dfs_on_reverseGraph(int src, unordered_map<int, int> &visitedRev, int scc)
    {
        visitedRev[src] = scc;
        for (auto nbr : revAdjList[src])
            if (visitedRev.find(nbr) == visitedRev.end())
                dfs_on_reverseGraph(nbr, visitedRev, scc);
    }
    int SCCs_count()
    {
        unordered_map<int, bool> visited;
        unordered_map<int, int> visitedRev;

        // create topoOrder
        stack<int> topo;
        for (auto p : adjList) // all components
            if (visited.find(p.first) == visited.end())
                dfs_topoOrder(p.first, topo, visited);

        // call DFS on reverse Graph from topo Order of stack
        int scc = 0;
        while (!topo.empty())
        {
            int sink = topo.top();
            topo.pop();
            if (visitedRev.find(sink) == visitedRev.end())
            {
                scc++;
                dfs_on_reverseGraph(sink, visitedRev, scc);
            }
        }
        return scc;
    }
};
