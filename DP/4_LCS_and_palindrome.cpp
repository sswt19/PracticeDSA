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
Pattern: Longest Common Subsequence
1. Brute force :    O(2^(n+m)) (Why: reason is in comments of BF solution)
2. Top Down DP :    O(s2*s1)
3. Bottom Up DP:    O(s2*s1) S: O(2*s1)

Problems
1. Longest Common Subsequence
    https://leetcode.com/problems/longest-common-subsequence/
2. Longset Common Substring
    https://practice.geeksforgeeks.org/problems/longest-common-substring1452/1
3. Shortest Common Supersequence
    https://leetcode.com/problems/shortest-common-supersequence/
4. Minimum Deletions & Insertions to Transform a String into another

*/
// 1 Longest Common Subsequence
class PatternLongestCommonSubsequence
{

public:
    // Brute Force: we are trying all 2^n combinations
    int lcs_bf(string s1, string s2, int s1_size, int s2_size)
    {
        if (s1_size == 0 || s2_size == 0)
            return 0;
        // if character matches use it
        if (s1[s1_size - 1] == s2[s2_size - 1])
            return 1 + lcs_bf(s1, s2, s1_size - 1, s2_size - 1);
        else
            return max(lcs_bf(s1, s2, s1_size - 1, s2_size), lcs_bf(s1, s2, s1_size, s2_size - 1));
    }
    // Top Down
    int lcsTD(string s1, string s2)
    {
        int s1_size = s1.size();
        int s2_size = s2.size();
        vector<vector<int>> dp(s1_size + 1, vector<int>(s2_size + 1, -1));
        return lcsTD_helper(s1, s2, s1_size, s2_size, dp);
    }

    int lcsTD_helper(string &s1, string &s2, int s1_size, int s2_size, vector<vector<int>> &dp)
    {
        if (s1_size == 0 || s2_size == 0)
            return 0;
        // already computed
        if (dp[s1_size][s2_size] != -1)
            return dp[s1_size][s2_size];

        // if character matches use it
        if (s1[s1_size - 1] == s2[s2_size - 1])
            return dp[s1_size][s2_size] = 1 + lcsTD_helper(s1, s2, s1_size - 1, s2_size - 1, dp);
        else
            return dp[s1_size][s2_size] = max(lcsTD_helper(s1, s2, s1_size - 1, s2_size, dp), lcsTD_helper(s1, s2, s1_size, s2_size - 1, dp));
    }
    // Bottom Up
    int lcsBU(string s1, string s2)
    {
        bool spaceOptimize = false;
        int s1_size = s1.size();
        int s2_size = s2.size();

        if (spaceOptimize == false)
        {
            //*********** S: O(s1*s2)*******************//
            // we cam use same dp to construct the lcs
            vector<vector<int>> dp(s1_size + 1, vector<int>(s2_size + 1, 0));
            // base case when length of any of the string is 0 the lcs is 0, so we will start at 1,1
            for (int i = 1; i <= s1_size; i++)
            {
                for (int j = 1; j <= s2_size; j++)
                {
                    if (s1[i - 1] == s2[j - 1])
                        dp[i][j] = 1 + dp[i - 1][j - 1];
                    else
                        dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
            return dp.back().back();
        }
        else // space optimization
        {    //*********** S: O(2*s2)*******************//
             // we can not construct the lcs
            vector<int> prev(s2_size + 1, 0), cur(s2_size + 1, 0);
            // base case when length of any of the string is 0 the lcs is 0, so we will start at 1,1
            for (int i = 1; i <= s1_size; i++)
            {
                for (int j = 1; j <= s2_size; j++)
                {
                    if (s1[i - 1] == s2[j - 1])
                        cur[j] = 1 + prev[j - 1];
                    else
                        cur[j] = max(prev[j], cur[j - 1]);
                }
                prev = cur;
            }
            return prev.back();
        }
    }

    string get_lcs(string s1, string s2)
    {

        int s1_size = s1.size();
        int s2_size = s2.size();

        //*********** S: O(s1*s2)*******************//
        // we cam use same dp to construct the lcs
        vector<vector<int>> dp(s1_size + 1, vector<int>(s2_size + 1, 0));
        // base case when length of any of the string is 0 the lcs is 0, so we will start at 1,1
        for (int i = 1; i <= s1_size; i++)
        {
            for (int j = 1; j <= s2_size; j++)
            {
                if (s1[i - 1] == s2[j - 1])
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }

        // to get the LCS string
        string lcs = "";
        int x = s1_size, y = s2_size;
        while (dp[x][y] != 0)
        {
            if (s1[x - 1] == s2[y - 1])
            {
                lcs += s1[x - 1];
                x = x - 1;
                y = y - 1;
            }
            else if (dp[x][y] == dp[x][y - 1])
                y = y - 1;
            else
                x = x - 1;
        }
        reverse(lcs.begin(), lcs.end());
        return lcs;
    }
};

// 2 LCSubstring
int longestCommonSubstr(string s1, string s2, int n, int m)
{
    bool spaceOptimize = false;

    int maxlcs = 0;
    int endIndex = -1; // stores lcs endindex for string s1
    int s1_size = s1.size();
    int s2_size = s2.size();

    if (spaceOptimize == false)
    { // stores the longest substring ending at i,j
        vector<vector<int>> dp(s1_size + 1, vector<int>(s2_size + 1, 0));
        for (int i = 1; i <= s1_size; i++)
        {
            for (int j = 1; j <= s2_size; j++)
            {
                if (s1[i - 1] == s2[j - 1])
                {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                    if (dp[i][j] > maxlcs)
                    {
                        maxlcs = dp[i][j];
                        endIndex = i - 1;
                    }
                }
                else
                    dp[i][j] = 0;
            }
        }
    }
    else
    {
        vector<int> prev(s2_size + 1, 0), cur(s2_size + 1, 0);
        for (int i = 1; i <= s1_size; i++)
        {
            for (int j = 1; j <= s2_size; j++)
            {
                if (s1[i - 1] == s2[j - 1])
                {
                    cur[j] = 1 + prev[j - 1];
                    if (cur[j] > maxlcs)
                    {
                        maxlcs = cur[j];
                        endIndex = i - 1;
                    }
                }
                else
                    cur[j] = 0;
            }
            prev = cur;
        }
    }
    // the string will be of size maxlcs backward from endIndex [endIndex-maxlcs+1,endIndex]
    return maxlcs;
}

// 3 Shortest Common Supersequence
string shortestCommonSupersequence(string str1, string str2)
{
    PatternLongestCommonSubsequence p;
    string lcs = p.get_lcs(str1, str2);
    string scs = "";
    int i = 0;
    int j = 0;
    int r = 0;
    while (r < lcs.size())
    {
        while (i < str1.size() && str1[i] != lcs[r])
        {
            scs += str1[i];
            i++;
        }
        while (j < str2.size() && str2[j] != lcs[r])
        {
            scs += str2[j];
            j++;
        }
        scs += lcs[r];
        r++;
        i++;
        j++;
    }
    // need to add any remaining part of both strings which is not in lcs
    return scs + str1.substr(i) + str2.substr(j);
}

// 4 Minimum Deletions & Insertions to Transform a String into another

//