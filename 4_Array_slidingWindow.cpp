
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
#define ll long long
/*

Hashing
1. Longest Consecutive Sequence
    https://leetcode.com/problems/longest-consecutive-sequence/description/
2. Largest subarray with 0 sum
    https://practice.geeksforgeeks.org/problems/largest-subarray-with-0-sum/1
3. Count number of subarrays with given Xor K/ Count Subarray Sum Equals K
    https://leetcode.com/problems/subarray-sum-equals-k/
    https://www.codingninjas.com/codestudio/problems/1115652
4. Count Subarray Sums Divisible by K
    https://leetcode.com/problems/subarray-sums-divisible-by-k/

Sliding Window pattern:
1. Maximum Average Subarray I https://leetcode.com/problems/maximum-average-subarray-i/
2. Minimum Size Subarray Sum:https://leetcode.com/problems/minimum-size-subarray-sum/
3. Longest Substring with At Most K Distinct Characters: https://leetcode.com/problems/longest-substring-with-at-most-k-distinct-characters/
4. Fruit Into Baskets:https://leetcode.com/problems/fruit-into-baskets/
5. Longest Substring Without Repeating Characters: https://leetcode.com/problems/longest-substring-without-repeating-characters/
6. Subarrays with Product Less than a Target: https://leetcode.com/problems/subarray-product-less-than-k/
7. Max consecutive ones: https://leetcode.com/problems/max-consecutive-ones/description/

*/

/*
****
Hashing
****
*/
// 1. Longest Consecutive Sequence
class LongestConsSeq
{ /*
     LC solution similar but better implementation
     def longestConsecutive(self, nums):
         nums = set(nums)
         best = 0
         for x in nums:
             if x - 1 not in nums:
                 y = x + 1
                 while y in nums:
                     y += 1
                 best = max(best, y - x)
         return best
 */
public:
    int longestConsecutive(vector<int> &nums)
    {

        unordered_map<int, bool> marked; // to find which number is present in constant time
        int streak = 0;

        for (auto x : nums)
            marked[x] = false; // false means this numbr has not been used in any sequence

        for (auto x : nums)
        {
            if (marked[x] == false)
            {
                int cur = x;
                while (marked.find(x) != marked.end()) // this loop finds start of sequence
                    marked[x--] = true;
                x++; // start of the sequence, we have 1 behind the sequence so add 1, x+1 is start of sequence

                while (marked.find(cur) != marked.end()) // this loop finds end of sequnece
                    marked[cur++] = true;
                cur--; // end of the sequence, cur does not exist so we go 1 behind which was in hashmap

                streak = max(streak, cur - x + 1);
            }
        }
        return streak;
    }
};

// 2 Largest subarray with 0 sum
class MaxLenWithSum0
{
public:
    int maxLen(vector<int> &arr, int n)
    {
        // Your code here
        int csum = 0;
        int maxL = 0;
        unordered_map<int, int> um;
        um[0] = -1; // for the case when subarray starts at index 0 not after 0

        for (int i = 0; i < n; i++)
        {
            csum += arr[i];
            if (um.find(csum) != um.end())
                maxL = max(maxL, i - um[csum]);
            else
                um[csum] = i;
        }
        return maxL;
    }
};

// 3 Count number of subarrays with given Xor K/ Count Subarray Sum Equals K
class CountSubArrayXorORSumEqualToK
{
public:
    int subarraySum(vector<int> &nums, int k)
    {
        int csum = 0;
        int count = 0;
        unordered_map<int, int> um;
        um[0] = 1; // used for count when subarray starts with index 0

        for (int i = 0; i < nums.size(); i++)
        {
            csum += nums[i];
            if (um.find(csum - k) != um.end())
                count += um[csum - k];
            // adding current csum for future use
            if (um.find(csum) == um.end())
                um[csum] = 1;
            else
                um[csum] += 1;
        }
        return count;
    }
    int subarraysXor(vector<int> &nums, int k)
    {
        int cxor = 0;
        int count = 0;
        unordered_map<int, int> um;
        um[0] = 1; // used for count when subarray starts with index 0

        for (int i = 0; i < nums.size(); i++)
        {
            cxor ^= nums[i];
            if (um.find(cxor ^ k) != um.end())
                count += um[cxor ^ k];
            // adding current cxor for future use
            if (um.find(cxor) == um.end())
                um[cxor] = 1;
            else
                um[cxor] += 1;
        }
        return count;
    }
};

// 4 Count Subarray Sums Divisible by K
class CountSubArraySumDivByK
{
public:
    /*
subarray sum b/w i+1 to j is csum[j]-csum[i]
we need to know csum[j]-csum[i] is divisible by k
i.e (csum[j]-cusm[i])%k==0
    (csum[j]%k -csum[i]%k +k)%k==0
remainder left by both are same then factor of k
*/
    int subarraysDivByK(vector<int> &nums, int k)
    {
        int csum = 0;
        int count = 0;
        unordered_map<int, int> um;
        um[0] = 1;

        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] >= 0) // no problem with positive
                csum = (csum + nums[i]) % k;
            else // when adding negative to csum
            {
                int sub = abs(nums[i]) % k;
                csum = (csum - sub + k) % k;
            }
            if (um.find(csum) != um.end()) // used to count of csum[i]s which gave same remainder as csum[j] for %k
                count += um[csum];
            if (um.find(csum) == um.end())
                um[csum] = 1;
            else
                um[csum] += 1;
        }
        return count;
    }
};

/****
 *
 Sliding Window
 *
*****/

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
            // decrease the window size from left
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
            minWin = min(minWin, winE - winS + 1); // current window might be the answer
            // decrease the window from left side
            winSum -= nums[winS];
            winS++;
        }
        // now the window sum is < target so we will increase the window from right side
        winE++;
    }
    return minWin == INT_MAX ? 0 : minWin; // if there was no window found return 0
}

// 3. Same Logic as 2nd, we will keep adding till the window's um.size() <= k  and then keep removing from left to find max window size possible until um.size()>k
int lengthOfLongestSubstringKDistinct(string str, int k)
{
    int maxL = 0;
    int winS = 0, winE = 0;
    unordered_map<int, int> um;

    while (winE < str.size())
    {
        // Add to unordered_map to know the map size
        // use the new element who is part of window now
        if (um.find(str[winE]) == um.end()) // new character
            um[str[winE]] = 1;
        else // already exists
            um[str[winE]] += 1;

        while (um.size() > k) // we need to remove from left to make total types of characters = k
        {
            um[str[winS]] -= 1;     // reduce count
            if (um[str[winS]] == 0) // char does not exist in the window anymore delete it
                um.erase(str[winS]);
            winS++;
        }
        // now the different types of character in string are <=k and window is useful
        maxL = max(maxL, winE - winS + 1);
        winE++; // increase the window
    }
    return maxL;
}

// 4. Same as 3rd Longest Substring with K Distinct Characters where K=2.
// Need to undertand how same question can be framed differently
int totalFruit(vector<int> &fruits)
{
    int k = 2;
    int maxL = 0;
    int winS = 0, winE = 0;
    unordered_map<int, int> um;

    while (winE < fruits.size())
    {
        if (um.find(fruits[winE]) == um.end())
            um[fruits[winE]] = 1;
        else
            um[fruits[winE]] += 1;

        while (um.size() > k)
        {
            um[fruits[winS]] -= 1;
            if (um[fruits[winS]] == 0)
                um.erase(fruits[winS]);
            winS++;
        }
        maxL = max(maxL, winE - winS + 1);
        winE++;
    }
    return maxL;
}

// 5. Same logic as 2nd and 3rd. increase the window for new character, if character already exists shrink from left till it's count becomes 1
int lengthOfLongestSubstring(string str)
{
    int maxL = 0;
    int winS = 0, winE = 0;
    unordered_map<int, int> um;

    while (winE < str.size())
    {
        // Add to unordered_map to know the map size
        if (um.find(str[winE]) == um.end()) // new character
            um[str[winE]] = 1;
        else // already exists shrink from left
        {
            um[str[winE]] += 1;
            while (um[str[winE]] != 1) // we need to removing from left till the character's count becomes 1
            {
                um[str[winS]] -= 1;
                if (um[str[winS]] == 0) // key does not exist delete it
                    um.erase(str[winS]);
                winS++;
            }
        }
        // now the window has only unique characters
        maxL = max(maxL, winE - winS + 1);
        winE++;
    }
    return maxL;
}

// 6. Subarrays with Product Less than a Target
int numSubarrayProductLessThanK(vector<int> &nums, int k)
{
    int winS = 0, winE = 0;
    int n = nums.size();
    ll product = 1;
    int count = 0;
    while (winE < n)
    {
        product *= nums[winE];
        while (winS <= winE && product >= k) // shrink from left
        {
            product = product / nums[winS];
            winS++;
        }
        // count all subarrays b/w [winS,winE] ending at winE, using this method we will always count unqiue subarrays
        int sub_arrays = winE - winS + 1;
        count += sub_arrays;
        winE++;
    }

    return count;
}

// 7.Max consecutive ones

class findMaxConsecutiveOne
{
public:
    // using sliding window
    int findMaxConsecutiveOnes(vector<int> &nums)
    {
        int winS = 0, winE = 0;
        int maxLength = 0;
        while (winE < nums.size())
        {

            if (nums[winE] == 1) // found start of one window
            {
                winS = winE;
                while (winE < nums.size() && nums[winE] == 1)
                    winE++;
                // we might have reached end of array or encountered a 0, winE will point to 0 or is out of array now
                maxLength = max(maxLength, winE - winS);
            }
            else
                winE++;
        }
        return maxLength;
    }
    // other apporach just keep counting one and whenever we see 0 set count to 0
    int findMaxConsecutiveOnes(vector<int> &nums)
    {

        int gl = 0, lc = 0;
        for (auto x : nums)
        {
            if (x == 1)
                gl = max(++lc, gl);
            else
                lc = 0;
        }
        return gl;
    }
};

//
