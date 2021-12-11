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

bool knows(int a, int b)
{
    return 0;
}
// when api is given
int findCelebrity(int n)
{
    int i = 0, j = n - 1;
    while (i < j)
    {
        if (knows(i, j))
            i++;
        else
            j--;
    }
    int mayBeCel = i;
    for (int i = 0; i < n; i++)
        if (i != mayBeCel && (!knows(i, mayBeCel) || knows(mayBeCel, i))) //cel should not know anyone and everyone should know him
            return -1;
    return mayBeCel;
}
// when edges are given : use in and outdegree indegree of celeb =n-1 and out =0
int findJudge(int n, vector<vector<int>> &trust)
{
    if (trust.size() == 0 && n == 1)
        return 1;

    unordered_map<int, int> out; //how many people i trusts
    unordered_map<int, int> in;  // how many people trust i

    for (auto edge : trust)
    {
        if (out.find(edge[0]) == out.end())
            out[edge[0]] = 1;
        else
            out[edge[0]] += 1;
        if (in.find(edge[1]) == in.end())
            in[edge[1]] = 1;
        else
            in[edge[1]] += 1;
    }
    for (int i = 1; i <= n; i++)
        if (in[i] == n - 1 && out[i] == 0) // if everyone trust i and i trust no one he/she is judge
            return i;

    return -1;
}