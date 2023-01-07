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
4. Kadane's|  Maximum Subarray sum: https://leetcode.com/problems/maximum-subarray/
5. Stock buy and Sell: https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
*/

// 1

class SetMatrixZeroes
{ /*
 1. We will use the same matrix to store our requied information.
     How is in comments of code
 */
public:
    void setZeroes(vector<vector<int>> &matrix)
    {
        int m = matrix.size();
        int n = matrix[0].size();
        bool row0 = false, col0 = false;

        // to check if 0th row and 0th column needs to be set to zero, this will handle M[0][0] as well
        for (int i = 0; i < m; i++)
            if (matrix[i][0] == 0)
                col0 = true;
        for (int i = 0; i < n; i++)
            if (matrix[0][i] == 0)
                row0 = true;
        // using 0th row for column and 0th column for row to store info about zero
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

        // Setting 0th row and 0th col to 0 if the booleans are true
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
            vector<int> level(i + 1, 1);                              // n'th level will n items so i+1th level will have i+1 items, we are setting the first and last element to 1 for each row
            for (int j = 1; j < i; j++)                               // for current row set other values other than first and last
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
    1.find first a[i-1]<a[i], means from [i,n-1] all elements are in non increasing order
    2.the value at i-1 will be swapped will be swapped with correct element
    3.reverse from [i,n-1], leads to sorted array
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
    /*
    Approach:
    1. We will find max subarray ending at current index, for all indexes
        1.1 the max subarray sum ending at current index i is = max(only the value at current index i,  max subarray sum ending at current index i-1 + arr[i])
            1.2 we are using max subarray ending at previous index to calculate for current index
    2. Out of this we will pick the one which is greatest (gs variable to handle this)
    */
public:
    long long maxSubArray(vector<int> &arr)
    {
        // long long gs = max(0, arr[0]); // if empty subarray allowed, i.e no elements are present in subarray
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
    /*
        1. We need to maximize the value of (prices[j]-prices[i]) where j>i
            1.1 So for each j we will use the min value b/w [0,j-1] and find arr[j]-minV
                and the ans will be the max arr[j]-minV computed
    */
public:
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