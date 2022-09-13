#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/*
Pattern: 0/1 Knapsack Unbounded
1. Brute force :    O(2^(n+c)) (Why: reason is in comments of BF solution)
2. Top Down DP :    O(n*W)
3. Bottom Up DP:    O(n*W)

Problems
1. 0/1 Knapsack Unbounded
    https://practice.geeksforgeeks.org/problems/knapsack-with-duplicate-items4201/1/
2. Rod cutting
    https://practice.geeksforgeeks.org/problems/rod-cutting0840/1
3.
*/
class Pattern01unboundedKnapsack
{

public:
    int unboundedKnapsackBF(vector<int> &values, vector<int> &weights, int i, int c)
    {
        if (i == values.size() || c <= 0)
            return 0;

        if (c < weights[i]) // we can't choose this item
            return unboundedKnapsackBF(values, weights, i + 1, c);

        int p1 = unboundedKnapsackBF(values, weights, i + 1, c);
        int p2 = values[i] + unboundedKnapsackBF(values, weights, i, c - weights[i]); // i remains same but capacity decreases sice we can choose the item hence the call can go till n+c becomes 0
        return max(p1, p2);
    }
    int unboundedKnapsackTD(vector<int> &values, vector<int> &weights, int capacity)
    {

        vector<vector<int>> dp(weights.size() + 1, vector<int>(capacity + 1, -1));
        return unboundedKnapsackTD_helper(values, weights, 0, capacity, dp);
    }

    int unboundedKnapsackTD_helper(vector<int> &values, vector<int> &weights, int i, int c, vector<vector<int>> &dp)
    {
        if (i == values.size() || c <= 0)
            return 0;
        if (dp[i][c] != -1)
            return dp[i][c];

        if (c < weights[i]) // we can't choose this item
            return dp[i][c] = unboundedKnapsackTD_helper(values, weights, i + 1, c, dp);

        int p1 = unboundedKnapsackTD_helper(values, weights, i + 1, c, dp);
        int p2 = values[i] + unboundedKnapsackTD_helper(values, weights, i, c - weights[i], dp); // i remains same but capacity decreases sice we can choose the item

        return dp[i][c] = max(p1, p2);
    }

    int unboundedKnapsackBU(vector<int> &values, vector<int> &weights, int capacity)
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

// 2 rod Cutting
int rodCutting(const vector<int> &lengths, vector<int> &prices, int capacity)
{

    int N = lengths.size();

    vector<vector<int>> dp(N + 1, vector<int>(capacity + 1, 0));

    for (int i = 1; i <= N; i++)
    {
        for (int c = 1; c <= capacity; c++)
        {
            if (c - lengths[i - 1] >= 0)
                dp[i][c] = max(dp[i - 1][c], prices[i - 1] + dp[i][c - lengths[i - 1]]);
            else
                dp[i][c] = dp[i - 1][c];
        }
    }
    return dp[N][capacity];
}
