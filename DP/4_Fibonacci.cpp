#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/*
Pattern: Fibonacci
URL: https://www.interviewbit.com/problems/0-1-knapsack/
1. Brute force :    O(2^n)
2. Top Down DP :    O(n)
3. Bottom Up DP:    O(n)

Problems
1.
*/
class PatternFib
{
public:
    // BF
    int fibBF(int n)
    {
        if (n <= 1)
            return n;
        else
            return fibBF(n - 1) + fibBF(n - 2);
    }
    // TD
    int fibTD(int n)
    {
        vector<int> dp(n + 1, -1);
        return fibTDHelper(n, dp);
    }
    int fibTDHelper(int n, vector<int> &dp)
    {
        if (n <= 1)
            return n;
        if (dp[n] != -1)
            return dp[n];
        else
            return dp[n] = fibTDHelper(n - 1, dp) + fibTDHelper(n - 2, dp);
    }
    // BU
    int fibBU(int n)
    {
        if (n <= 1)
            return n;
        int last = 0, curr = 1;
        for (int i = 2; i <= n; i++)
        {
            int temp = last + curr;
            last = curr;
            curr = temp;
        }
        return curr;
    }
};