#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/*
Pattern: 0/1 Knapsack
URL: https://www.interviewbit.com/problems/0-1-knapsack/
1. Brute force :    O(2^n)
2. Top Down DP :    O(n*W)
3. Bottom Up DP:    O(n*W)

Problems
1. 0/1 Knapsack
    https://www.interviewbit.com/problems/0-1-knapsack/
2. Subset Sum
    https://www.interviewbit.com/problems/subset-sum-problem/
3. Partition Equal Subset Sum
    https://leetcode.com/problems/partition-equal-subset-sum/
4.
*/

// 1
class Pattern01Knapsack
{

public:
    // Brute Force: we are trying all 2^n combinations
    int knapsackBF(vector<int> &values, vector<int> &weights, int i, int capacity)
    {
        if (i == values.size() || capacity <= 0)
            return 0;

        if (capacity < weights[i]) // we can't choose this item
            return knapsackBF(values, weights, i + 1, capacity);

        int pick_cur_item = values[i] + knapsackBF(values, weights, i + 1, capacity - weights[i]); // capacity decreased and we moved one index
        int ignore_cur_item = knapsackBF(values, weights, i + 1, capacity);                        // capacity same and we moved one index

        int ans = max(pick_cur_item, ignore_cur_item);

        return ans;
    }
    // Top Down
    int knapsackTD(vector<int> &values, vector<int> &weights, int capacity)
    {

        vector<vector<int>> dp(weights.size() + 1, vector<int>(capacity + 1, -1));
        return knapsackTD_helper(values, weights, 0, capacity, dp);
    }

    int knapsackTD_helper(vector<int> &values, vector<int> &weights, int i, int capacity, vector<vector<int>> &dp)
    {
        if (i == values.size() || capacity <= 0)
            return 0;
        // already computed so no need to compute again
        if (dp[i][capacity] != -1)
            return dp[i][capacity];

        if (capacity < weights[i]) // we can't choose this item
            return dp[i][capacity] = knapsackTD_helper(values, weights, i + 1, capacity, dp);

        int pick_cur_item = values[i] + knapsackTD_helper(values, weights, i + 1, capacity - weights[i], dp); // capacity decreased and we moved one index
        int ignore_cur_item = knapsackTD_helper(values, weights, i + 1, capacity, dp);                        // capacity same and we moved one index

        int ans = max(pick_cur_item, ignore_cur_item);

        return dp[i][capacity] = ans;
    }
    // Bottom Up
    int knapsackBU(vector<int> &values, vector<int> &weights, int capacity)
    {
        int N = values.size();
        vector<vector<int>> dp(N + 1, vector<int>(capacity + 1, 0)); // base case already initialized c=0 or items.size()=0 then value we can get is 0
        for (int i = 1; i <= N; i++)
        {
            for (int c = 1; c <= capacity; c++)
            {
                if (c - weights[i - 1] >= 0)                                                     // we will go to row c-weight[i-1], item (i-1)'s detail is dp[i] so access w[i-1] and v[i-1]
                    dp[i][c] = max(values[i - 1] + dp[i - 1][c - weights[i - 1]], dp[i - 1][c]); // if we can use current item
                else
                    dp[i][c] = dp[i - 1][c];
            }
        }
        return dp[N][capacity];
    }
};

// 2. Subset Sum
int subset_sum(vector<int> &arr, int sum)
{
    int N = arr.size();
    vector<vector<int>> dp(N + 1, vector<int>(sum + 1, 0));
    for (int i = 0; i <= N; i++)
        dp[i][0] = 1;

    for (int i = 1; i <= N; i++)
    {
        for (int s = 1; s <= sum; s++)
        {
            if (s - arr[i - 1] >= 0) // we will go to row s-arr[i-1]
                dp[i][s] = max(dp[i - 1][s], dp[i - 1][s - arr[i - 1]]);
            else
                dp[i][s] = dp[i - 1][s];
        }
    }
    return dp[N][sum];
}

// 3. Partition Equal Subset Sum

//
