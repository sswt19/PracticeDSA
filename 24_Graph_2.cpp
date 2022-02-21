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
typedef long long ll;
/*
1.DSU Disjoint set union: Redundant Connection(leetcode)
2.MST
 2.1 Prims
 2.2 Kruskals
Single source shortest Path
: Undirected Unweighted Graph : BFS

*/

/*
//  DSU
Two Functions used 1. find(v): set of v, 2.union(u,v): merges sets of elements u and v
Optimizations:
Complexity before optimization for both functions: O(n)
1. Path Compression: O(log n)
2. Rank Optimization: O(1)
*/

class DSU
{
    int *parents;
    int *ranks;
    int size;
    int total_comps;

public:
    DSU(int n)
    {
        size = total_comps = n;

        parents = new int[n];
        ranks = new int[n];

        for (int i = 0; i < n; i++)
        {
            parents[i] = -1; // each node is parent of itself at start
            ranks[i] = 1;    // no of nodes in each set will be 1 at start
        }
    }

    int find(int x)
    {
        if (parents[x] == -1) // we arrived at the super parent
            return x;

        // path compression
        parents[x] = find(parents[x]); // for example parents of 5,4,3,2 be 4,3,2,2 after compression parents will be 2,2,2,2
        return parents[x];
    }

    void union_set(int x, int y)
    {
        int s1 = find(x);
        int s2 = find(y);

        if (s1 != s2) // if there super parents are different merge them
        {
            // union by rank reduces to O(1)
            if (ranks[s1] < ranks[s2]) // join subtree of s1 to s2
            {
                parents[s1] = s2;
                ranks[s2] += ranks[s1]; // add nodes of s1 set
                ranks[s1] = 0;          // for convinienece no need
            }
            else // join subtree of s2 to s1
            {
                parents[s2] = s1;
                ranks[s1] += ranks[s2];
                ranks[s2] = 0; // for convinienece no need
            }
            total_comps--;
        }
    }

    void print()
    {
        cout << "Number of elements:" << size << endl;
        cout << "Components:" << total_comps << endl;

        cout << "Parents" << endl;
        for (int i = 0; i < size; i++)
            cout << parents[i] << " ";
        cout << endl;

        cout << "Ranks" << endl;
        for (int i = 0; i < size; i++)
            cout << ranks[i] << " ";
        cout << endl;
    }
};
// 1  Redundant Connection
vector<int> findRedundantConnection(vector<vector<int>> &edges)
{
    auto g = DSU(edges.size() + 1);
    for (auto e : edges)
    {
        int s1 = g.find(e[0]);
        int s2 = g.find(e[1]);
        if (s1 == s2)
            return e;
        else
            g.union_set(e[0], e[1]);
    }
    return {};
}
// 2.1
/*
2.2 Kruskal
1. sort edges based on weight
2. pick edge and if it does not form cycle it will be in mst (check cycles using DSU)
*/
bool compare(vector<int> &a, vector<int> &b)
{
    return a[2] < b[2];
}
pair<ll, vector<vector<int>>> Kruskal(int vertices, vector<vector<int>> edges)
{
    sort(edges.begin(), edges.end(), compare);
    DSU g(vertices + 1);
    vector<vector<int>> mstEdges;
    ll mst = 0;
    for (auto e : edges)
    {
        int s1 = g.find(e[0]);
        int s2 = g.find(e[1]);
        if (s1 != s2) // they are not connected yet
        {
            mst += e[2]; // add weight to mst
            mstEdges.push_back(e);
            g.union_set(s1, s2);
        }
    }
    return {mst, mstEdges};
}

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
    //
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