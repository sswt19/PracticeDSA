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
1. Set Matrix Zeroes:https://leetcode.com/problems/set-matrix-zeroes/
2. Pascal Triangle:https://leetcode.com/problems/pascals-triangle/
3. Next Permutation: https://leetcode.com/problems/next-permutation/
4. Kadane's|  Maximum Subarray: https://leetcode.com/problems/maximum-subarray/
5. Stock buy and Sell: https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
*/
// 1
class Solution
{
public:
    void setZeroes(vector<vector<int>> &matrix)
    {
        int m = matrix.size();
        int n = matrix[0].size();
        bool row0 = false, col0 = false;

        // to check if 0th row and 0th column needs to be set to zero
        for (int i = 0; i < m; i++)
            if (matrix[i][0] == 0)
                col0 = true;
        for (int i = 0; i < n; i++)
            if (matrix[0][i] == 0)
                row0 = true;
        // using 0th row for column and 0th column for row  to store info about zero
        for (int i = 1; i < m; i++)
        {
            for (int j = 1; j < n; j++)
                if (matrix[i][j] == 0)
                {
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
        }
        // using 0th row and 0th col to update whole matrix
        for (int i = 1; i < m; i++)
            for (int j = 1; j < n; j++)
                if (matrix[i][0] == 0 || matrix[0][j] == 0)
                    matrix[i][j] = 0;

        // Setting row 0 and col 0 to 0 if the booleans are true
        if (row0)
            for (int i = 0; i < n; i++)
                matrix[0][i] = 0;

        if (col0)
            for (int i = 0; i < m; i++)
                matrix[i][0] = 0;
    }
};
// 2
class PascalTriangle
{
public:
    vector<vector<int>> generate(int n)
    {
        vector<vector<int>> pascalT;
        pascalT.push_back({1});
        for (int i = 1; i < n; i++)
        {
            vector<int> level(i + 1, 1); // n'th level will n items so i+1th level will have i+1 items
            for (int j = 1; j < i; j++)
                level[j] = pascalT[i - 1][j - 1] + pascalT[i - 1][j]; // using the previous level for filling curent level
            pascalT.push_back(level);
        }
        return pascalT;
    }
};
// 3
class NextPerm
{
    /*
    1.find first a[i-1]<a[i]
    2.the value at i-1 will be swapped
    3.reverse from i to end, leads to sorted array because all a[i-1]>a[i] till we found the break point in step 1
    4.traverse from i to end to find smallest value greater than a[i-1] and swap it
    */
public:
    void nextPermutation(vector<int> &nums)
    {
        int n = nums.size();
        int i = n - 1;
        while (i > 0)
        {
            if (nums[i - 1] < nums[i]) // from i to n-1 all numbers are in decreasing order
                break;
            i--;
        }
        reverse(nums.begin() + i, nums.end()); // i to n-1 are now in increasing order
        if (i != 0)                            // if i==0 then whole array was in decreasing order
        {
            for (int j = i; j < n; j++)
                if (nums[j] > nums[i - 1])
                {
                    swap(nums[j], nums[i - 1]);
                    break;
                }
        }
    }
};

// 4
class Kadane
{
public:
    long long maxSubArray(vector<int> &arr)
    {
        // long long gs = max(0, arr[0]); // if empty subarray allowed
        long long gs = arr[0];
        long long ls = arr[0];
        for (int i = 1; i < arr.size(); i++)
        {
            ls = max(ls + arr[i], (long long)arr[i]); // ls will maintain maximum subarray sum ending at index i
            gs = max(ls, gs);                         // gs will pick the max of ls
        }
        return gs;
    }
};
// 5
class BuyAndSellStock
{
public:
    // We need to maximize prices[j]-prices[i] where j>i
    int maxProfit(vector<int> &prices)
    {
        int profit = 0; // in case not able to make profit don't buy and sell
        int minStock = prices[0];

        for (int i = 1; i < prices.size(); i++)
        {
            profit = max(profit, prices[i] - minStock);
            minStock = min(minStock, prices[i]);
        }
        return profit;
    }
};