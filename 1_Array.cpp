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
    We will use the same matrix to store our requied information.
    a) find out if 0th row and 0th col needs to be set to 0
    b) use 0th row and 0th column to store which row and column needs to be set to 0
    c) Set the row and col to 0 using b) mapping
    d) set 0th row and col to 0 using stored values in a)
 */
public:
    void setZeroes(vector<vector<int>> &matrix)
    {
        int m = matrix.size();
        int n = matrix[0].size();
        bool row0 = false, col0 = false;

        // a) to check if 0th row and 0th column needs to be set to zero, this will handle M[0][0] as well
        for (int i = 0; i < m; i++)
            if (matrix[i][0] == 0)
                col0 = true;
        for (int i = 0; i < n; i++)
            if (matrix[0][i] == 0)
                row0 = true;

        // b) using 0th row for column and 0th column for row to store info about zero
        for (int i = 1; i < m; i++)
        {
            for (int j = 1; j < n; j++)
                if (matrix[i][j] == 0)
                {
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
        }
        // c) using 0th row and 0th col to update whole matrix
        for (int i = 1; i < m; i++)
            for (int j = 1; j < n; j++)
                if (matrix[i][0] == 0 || matrix[0][j] == 0)
                    matrix[i][j] = 0;

        // d) now we need to hanlde the 0th row and 0th column
        //  Setting 0th row and 0th col to 0 if the booleans are true
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
{ /* We will use the previous row to compute the current row
        a) 1st level will have only 1
        b) n'th level will n items.
        c) each row's first and last element will be 1
        d) we will fill from 2nd to 2nd last element using the previous row
*/
public:
    vector<vector<int>> generate(int n)
    {
        vector<vector<int>> pascalT;
        // a)
        pascalT.push_back({1});

        for (int row = 2; row <= n; row++)
        {
            // b) and c)
            vector<int> level(row, 1);
            // d)
            for (int i = 1; i < row - 1; i++)
                level[i] = pascalT[row - 2][i - 1] + pascalT[row - 2][i]; // row - 2, because array is 0 indexed
            pascalT.push_back(level);
        }
        return pascalT;
    }
};

// 3
class NextPerm
{ /*
     a.find first i such that, a[i]<a[i+1], means from [i+1,n-1] all elements are in non increasing order
     b.we need to arrange the values from [i,n-1], the value at i will be swapped will be swapped with value just greater than at i
     c.reverse from [i+1,n-1], leads to sorted array
     d.traverse from i to end to find smallest value greater than a[i-1] and swap it
    */
public:
    void nextPermutation(vector<int> &nums)
    {
        int n = nums.size();
        int i = n - 2;
        // a
        while (i >= 0)
        {
            if (nums[i] < nums[i + 1])
                break;
            i--;
        }
        // c
        reverse(nums.begin() + i + 1, nums.end());
        // if i < 0 means the list was the greatest number possible and after revers, it is smallest number possible
        if (i >= 0)
        { // d
            for (int j = i + 1; j < n; j++)
                if (nums[i] < nums[j])
                {
                    swap(nums[i], nums[j]);
                    break;
                }
        }
    }
};

// 4
class Kadane
{
    /*
    Always ask if empty subarray is allowed
    Approach:
    1. We will find max subarray ending at current index, for all indexes
        1.1 the max subarray sum ending at current index i is = max(only the value at current index i,  max subarray sum ending at current index i-1 + arr[i])
            1.2 we are using max subarray ending at previous index to calculate for current index
    2. Out of this we will pick the one which is greatest (gs variable to handle this)
    */
public:
    long long maxSubArray(vector<int> &arr)
    {
        //*** long long gs = max(0, arr[0]); // if empty subarray allowed, i.e no elements are present in subarray
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