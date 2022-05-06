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
3. Next Permutation: https://leetcode.com/problems/next-permutation/
4. Kadane's|  Maximum Subarray: https://leetcode.com/problems/maximum-subarray/
5. Dutch national flag problem |Sort array of 0’s 1’s 2’s without extra space in linear time: https://leetcode.com/problems/sort-colors/
6. Stock buy and Sell: https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
*/

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
class DutchNationalFlag
{
public:
    void sortColors(vector<int> &arr)
    {
        int n = arr.size();
        int i = 0, j = n - 1, k = 0; // zero: till i-1, one: i to k-1, unknown: k to j, Two: From j+1 to end
        int pivot = 1;
        while (k <= j)
        {
            if (arr[k] < pivot)
                // swap(arr[k],arr[i++]); // this was the mistake I did, i <=k (must) but if we don't increment k and input is 001 i will get ahead of k
                swap(arr[k++], arr[i++]);
            else if (arr[k] == pivot)
                k++;
            else
                swap(arr[k], arr[j--]);
        }
    }
};
// 6
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