#include <bits/stdc++.h>
#include <vector>
#include <iostream>
#include <queue>
#include <stack>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <list>
#include <sstream>
#include <limits.h>
using namespace std;
typedef long long ll;

class PatternMCM
{

public:
    int knapsackBF(vector<int> &values, vector<int> &weights, int i, int c)
    {
        if (i == values.size() || c <= 0)
            return 0;

        if (c < weights[i]) // we can't choose this item
            return knapsackBF(values, weights, i + 1, c);
        int ans = max(knapsackBF(values, weights, i + 1, c), values[i] + knapsackBF(values, weights, i + 1, c - weights[i]));
        return ans;
    }
    int knapsackTD(vector<int> &values, vector<int> &weights, int capacity)
    {

        vector<vector<int>> dp(weights.size() + 1, vector<int>(capacity + 1, -1));
        return knapsackTD_helper(values, weights, 0, capacity, dp);
    }

    int knapsackTD_helper(vector<int> &values, vector<int> &weights, int i, int c, vector<vector<int>> &dp)
    {
        if (i == values.size() || c <= 0)
            return 0;
        if (dp[i][c] != -1)
            return dp[i][c];

        if (c < weights[i]) // we can't choose this item
            return dp[i][c] = knapsackTD_helper(values, weights, i + 1, c, dp);
        int ans = max(knapsackTD_helper(values, weights, i + 1, c, dp), values[i] + knapsackTD_helper(values, weights, i + 1, c - weights[i], dp));
        return dp[i][c] = ans;
    }

    int knapsackBU(vector<int> &values, vector<int> &weights, int capacity)
    {

        vector<vector<int>> dp(weights.size() + 1, vector<int>(capacity + 1, 0)); // base case already initialized c=0 or items.size()=0
        for (int i = 1; i <= weights.size(); i++)
        {
            for (int c = 1; c <= capacity; c++)
            {
                if (c - weights[i - 1] >= 0)                                                     // item (i-1)'s detail is dp[i] so access w[i-1] and v[i-1]
                    dp[i][c] = max(dp[i - 1][c], values[i - 1] + dp[i - 1][c - weights[i - 1]]); // if we can use current item
                else
                    dp[i][c] = dp[i - 1][c];
            }
        }
        return dp[weights.size()][capacity];
    }
};