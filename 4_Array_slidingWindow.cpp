
#include <vector>
#include <iostream>
#include <queue>
#include <stack>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <list>
#include <sstream>
#include <climits>
using namespace std;

/*


Sliding Window pattern:
1. Maximum Average Subarray I https://leetcode.com/problems/maximum-average-subarray-i/
2. Minimum Size Subarray Sum:https://leetcode.com/problems/minimum-size-subarray-sum/
3. Longest Substring with At Most K Distinct Characters: https://leetcode.com/problems/longest-substring-with-at-most-k-distinct-characters/
4. Fruit Into Baskets:https://leetcode.com/problems/fruit-into-baskets/
5. Longest Substring Without Repeating Characters: https://leetcode.com/problems/longest-substring-without-repeating-characters/
6.
*/

// 1
double findMaxAverage(vector<int> &nums, int k)
{
    double maxAvg = INT_MIN;
    int winStart = 0, winEnd = 0, winSum = 0;
    while (winEnd < nums.size())
    {
        winSum += nums[winEnd];         // use the new element who is part of window now
        if (winEnd - winStart + 1 == k) // found a window of required size
        {
            maxAvg = max(maxAvg, winSum / (double)k); // process the window
            // reduce the window size from left
            winSum -= nums[winStart]; // remove the start of window content
            winStart++;               // move the start of window ahead
        }
        winEnd++; // increase the window size from right
    }
    return maxAvg;
}

// 2. we will keep adding till the window sum>= target and then keep removing from left to find min window size possible
int minSubArrayLen(int target, vector<int> &nums)
{
    int minWin = INT_MAX;
    int winS = 0, winE = 0, winSum = 0;
    while (winE < nums.size())
    {
        winSum += nums[winE];    // use the new element who is part of window now
        while (winSum >= target) // we will keep reducing from left side till the condition is satisfied
        {
            minWin = min(minWin, winE - winS + 1);
            // decrease the window from left side
            winSum -= nums[winS];
            winS++;
        }
        // now the window sum is < target so we will increase the window from right side
        winE++;
    }
    return minWin == INT_MAX ? 0 : minWin; // if there was no window found return 0
}

// 3

int lengthOfLongestSubstringKDistinct(string str, int k)
{
    int maxL = 0;
    int winS = 0, winE = 0;
    unordered_map<int, int> um;

    while (winE < str.size())
    {
        // Add to unordered_map to know the map size
        if (um.find(str[winE]) == um.end())
            um[str[winE]] = 1;
        else
            um[str[winE]] += 1;

        while (um.size() > k) // we need to remove from left to make total types of characters = k
        {
            um[str[winS]] -= 1;
            if (um[str[winS]] == 0) // key does not exist delete it
                um.erase(str[winS]);
            winS++;
        }
        maxL = max(maxL, winE - winS + 1);

        winE++;
    }
    return maxL;
}

// 4
class Solution
{
public:
    int totalFruit(vector<int> &fruits)
    {
        int k = 2;
        int maxL = 0;
        int winS = 0, winE = 0;
        unordered_map<int, int> um;

        while (winE < fruits.size())
        {
            // Add to unordered_map to know the map size
            if (um.find(fruits[winE]) == um.end())
                um[fruits[winE]] = 1;
            else
                um[fruits[winE]] += 1;

            while (um.size() > k) // we need to remove from left to make total types of characters = k
            {
                um[fruits[winS]] -= 1;
                if (um[fruits[winS]] == 0) // key does not exist delete it
                    um.erase(fruits[winS]);
                winS++;
            }
            maxL = max(maxL, winE - winS + 1);

            winE++;
        }
        return maxL;
    }
};

// 5
class Solution
{
public:
    int lengthOfLongestSubstring(string str)
    {
        int maxL = 0;
        int winS = 0, winE = 0;
        unordered_map<int, int> um;

        while (winE < str.size())
        {
            // Add to unordered_map to know the map size
            if (um.find(str[winE]) == um.end())
                um[str[winE]] = 1;
            else
            {
                um[str[winE]] += 1;
                while (um[str[winE]] != 1) // we need to removing from left till count becomes 1
                {
                    um[str[winS]] -= 1;
                    if (um[str[winS]] == 0) // key does not exist delete it
                        um.erase(str[winS]);
                    winS++;
                }
            }
            maxL = max(maxL, winE - winS + 1); // now the window has only unique characters
            winE++;
        }
        return maxL;
    }
};