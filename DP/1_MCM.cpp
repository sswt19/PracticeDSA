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

/*
Pattern: Matrix chain multiplication
URL: https://practice.geeksforgeeks.org/problems/matrix-chain-multiplication0303/1
1. Brute force :    O(2^n)
2. Top Down DP :    O(n^3)
3. Bottom Up DP:    O(n^3)

Problems
1.
*/

class PatternMCM
{
public:
    int mcmBF(int arr[], int i, int j)
    {
        if (i >= j) // single matrix or no matrix
            return 0;

        int ans = INT_MAX;
        for (int k = i; k < j; k++)
        {
            int tempAns = mcmBF(arr, i, k) + mcmBF(arr, k + 1, j) + arr[i] * arr[k + 1] * arr[j + 1];
            ans = min(tempAns, ans);
        }
        return ans;
    }
    int mcmTD(int N, int arr[])
    {
        vector<vector<int>> dp(N, vector<int>(N, -1));
        return mcmTD_hepler(arr, 0, N - 2, dp);
    }
    int mcmTD_hepler(int arr[], int i, int j, vector<vector<int>> &dp)
    {
        if (i >= j) // single matrix or no matrix
            return 0;
        if (dp[i][j] != -1)
            return dp[i][j];

        int ans = INT_MAX;
        for (int k = i; k < j; k++)
        {
            int tempAns = mcmTD_hepler(arr, i, k, dp) + mcmTD_hepler(arr, k + 1, j, dp) + arr[i] * arr[k + 1] * arr[j + 1];
            ans = min(tempAns, ans);
        }
        return dp[i][j] = ans;
    }
    int mcmBU(int N, int arr[])
    {
        int matrixes = N - 1;                                        // No of matrixes
        vector<vector<int>> dp(matrixes, vector<int>(matrixes, -1)); // dp cache

        for (int t = 0; t < matrixes; t++)
        {
            for (int i = 0; i < matrixes - t; i++)
            {
                int j = i + t;
                // found i and j same top down logic now using the i and j
                if (i == j)
                    dp[i][j] = 0;
                else
                {
                    int ans = INT_MAX;
                    for (int k = i; k < j; k++)
                        ans = min(ans, dp[i][k] + dp[k + 1][j] + arr[i] * arr[k + 1] * arr[j + 1]);
                    dp[i][j] = ans;
                }
            }
        }
        return dp[0][matrixes - 1];
    }
};