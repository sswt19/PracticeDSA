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

5. Dutch national flag problem |Sort array of 0’s 1’s 2’s without extra space in linear time: https://leetcode.com/problems/sort-colors/
6. Stock buy and Sell: https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
*/
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