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
The general problem statement for this pattern is forgiven situation decide whether to use or not to use the current state. So, the problem requires you to make a decision at a current state.

Approach
If you decide to choose the current value use the previous result where the value was ignored;
vice - versa, if you decide to ignore the current value use previous result where value was used.
*/

/*
1. House Robber:
    url: https://leetcode.com/problems/house-robber/
2. Best Time to Buy and Sell Stock
    url:https://leetcode.com/problems/best-time-to-buy-and-sell-stock/

*/

// 1 House robber
/*
My extension: also tell the index of houses robbed
store i-1,i-2 for each index, for index i if i-2 is stored current index was used and then move to i-2 else goto i-1
for index 0 and 1 save -1 so that we will stop when we reach -1 and that was the first house robbed
*/
int rob(vector<int> &nums)
{
    int n = nums.size();
    vector<int> dp(nums);
    for (int i = 1; i < n; i++)
    {

        int include_cur_house = nums[i] + ((i - 1) == 0 ? 0 : dp[i - 2]); // we will use the result of till second last house
        int do_not_use_cur_house = dp[i - 1];                             // we will use result till last house
        dp[i] = max(do_not_use_cur_house, include_cur_house);
    }
    return dp.back();
}

// 2 Best Time to Buy and Sell Stock
int maxProfit(vector<int> &prices)
{

    int best_profit = 0;
    int min_price = INT_MAX;

    for (auto p : prices)
    {
        // decision part
        int cur_profit = p - min_price; // max profit we can make if we sell today
        min_price = min(min_price, p);
        best_profit = max(best_profit, cur_profit);
    }
    return best_profit;
}