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

4. Kadane's|  Maximum Subarray: https://leetcode.com/problems/maximum-subarray/
5. Dutch national flag problem |Sort array of 0’s 1’s 2’s without extra space in linear time: https://leetcode.com/problems/sort-colors/
6. Stock buy and Sell: https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
*/

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