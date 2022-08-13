
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
using ll = long long;

/*
1. Two Sum:
    url sorted input: https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/
    url unsorted input: https://leetcode.com/problems/two-sum/
2. Three Sum:
    2A. Three Sum Target
        url: https://leetcode.com/problems/3sum/
    2B. Triplet Sum Close to Target
        url: https://leetcode.com/problems/3sum-closest/
    2C. Triplets with Smaller Sum
        url: https://leetcode.com/problems/3sum-smaller/
        Ques:
            Given an array of n integers nums and an integer target,
            find the number of index triplets i, j, k with 0 <= i < j < k < n
            that satisfy the condition nums[i] + nums[j] + nums[k] < target.
3. Four Sum:
    url: https://leetcode.com/problems/4sum/
4. Remove Duplicates from sorted Array:
    url: https://leetcode.com/problems/remove-duplicates-from-sorted-array/
5. Squaring a Sorted Array
    url: https://leetcode.com/problems/squares-of-a-sorted-array/
6. Dutch national flag problem |Sort array of 0’s 1’s 2’s without extra space in linear time
    url: https://leetcode.com/problems/sort-colors/submissions/
7. Comparing Strings containing Backspaces
    url: https://leetcode.com/problems/backspace-string-compare/
8. Shortest Unsorted Continuous Subarray
    url: https://leetcode.com/problems/shortest-unsorted-continuous-subarray/

*/
// 1A. Two Sum Sorted Array
vector<int> twoSum_sorted_input(vector<int> &nums, int target)
{

    int i = 0, j = nums.size() - 1;

    while (i < j)
    {
        int sum = nums[i] + nums[j];
        if (sum == target)
            break;
        else if (sum > target)
            j--;
        else
            i++;
    }
    return {i, j};
}

// 1B. Two Sum Unsorted Array
vector<pair<int, int>> twoSum_unsorted(vector<int> &nums, int target)
{

    unordered_map<int, pair<int, vector<int>>> um; // each number with its count and indexd

    for (int i = 0; i < nums.size(); i++)
    {
        if (um.find(nums[i]) == um.end())
            um[nums[i]] = {1, {i}};
        else
        {
            um[nums[i]].first++;
            um[nums[i]].second.push_back(i);
        }
    }

    vector<pair<int, int>> targetSum;
    for (int v : nums)
    {
        if (um.find(target - v) != um.end() && um.find(v) != um.end())
        {
            if (v == target - v) // when b=a+a we need to know if number of a present is greater than or equal to 2
            {
                if (um[v].first < 2)
                    continue;
            }

            // reducing count and removing their index
            int p1 = um[v].second.back();
            um[v].first--;
            um[v].second.pop_back();
            // if v=target-v then p2 should be different index
            int p2 = um[target - v].second.back();
            um[target - v].first--;
            um[target - v].second.pop_back();
            targetSum.push_back({nums[p1], nums[p2]});

            if (um[v].first == 0)
                um.erase(v);
            if (um[target - v].first == 0)
                um.erase(target - v);
        }
    }
    return targetSum;
}

// 2A. Three Sum to target
class Unique3Sum
{
public:
    vector<vector<int>> threeSum(vector<int> &nums)
    {
        int target = 0;
        vector<vector<int>> trip;
        sort(nums.begin(), nums.end()); // sort so that we can use pointers at start and end also for removing duplicates
        int n = nums.size();

        int i = 0;
        while (i < n)
        {
            auto v = twoSum(nums, target - nums[i], i + 1, n - 1);
            for (auto p : v)
                trip.push_back({nums[i], p.first, p.second});
            // since the all triplets whose first element is nums[i] are already computed we will ignore all nums[i] as first element
            i++;
            while (i < n && nums[i] == nums[i - 1]) // this line makes sure there are unique triplets
                i++;
        }
        return trip;
    }
    // this method returns all unique two sum target pairs
    vector<pair<int, int>> twoSum(vector<int> &nums, int target, int s, int e)
    {

        vector<pair<int, int>> pairs;
        while (s < e)
        {
            int sum = nums[s] + nums[e];
            if (sum == target)
            {
                pairs.push_back({nums[s], nums[e]});
                // since the all pairs whose first element is nums[s] are already computed we will ignore all nums[s] as first element
                s++;
                while (s < nums.size() && nums[s] == nums[s - 1]) // this line makes sure there are unique pairs
                    s++;
            }
            else if (sum > target)
                e--;
            else
                s++;
        }
        return pairs;
    }
};

// 2B. Triplet Sum Close to Target
int threeSumClosest(vector<int> &nums, int sum_needed)
{
    sort(nums.begin(), nums.end());
    int k = 0, n = nums.size();
    int ans = 0;
    int diff = INT_MAX;

    while (k < n)
    {
        int target = sum_needed - nums[k]; // we will find closest pair sum to target b/w [k+1,n-1]
        int i = k + 1, j = n - 1;
        while (j > i)
        {
            int pair_sum = nums[i] + nums[j];
            if (pair_sum == target) // we found triplets nums[k]+nums[i]+nums[j]=target
                return sum_needed;
            else if (pair_sum > target)
            {
                if (pair_sum - target < diff)
                {
                    diff = pair_sum - target;
                    ans = sum_needed + diff; // current closest sum is higher from sum_needed by diff amount
                }
                j--; // we will reduce from right since the sum is greater
            }
            else
            {
                if (target - pair_sum <= diff)
                {
                    diff = target - pair_sum;
                    ans = sum_needed - diff; // current closest sum is lower from sum_needed by diff amount
                }
                i++; // we will increase from left since the sum is lower
            }
        }
        k++;
        while (k < n && nums[k] == nums[k - 1]) // for making unique triplets
            k++;
    }
    return ans;
}

// 2C. Triplets with Smaller Sum
class ThreeSumSmaller
{
public:
    int threeSumSmaller(vector<int> &nums, int target)
    {
        sort(nums.begin(), nums.end());
        int count = 0;
        int n = nums.size();
        for (int i = 0; i < n; i++)
            count += countTwoSumSmaller(nums, i + 1, n - 1, target - nums[i]);
        return count;
    }
    int countTwoSumSmaller(vector<int> &nums, int s, int e, int target)
    {
        if (s >= e) // not possible for less than 2 elements
            return 0;
        int count = 0;
        while (s < e)
        {
            int sum = nums[s] + nums[e];
            if (sum < target)
            {
                count += (e - s); // all nums from s+1 to e will satisfy the sum with nums[s] so total pairs= e-(s+1)+1=e-s
                s++;
            }
            else
                e--;
        }
        return count;
    }
};

// 3. Four Sum
// we will use three sum and two sum
class Unique4Sum
{
    vector<vector<int>> threeSum(vector<int> &nums, ll target, int s, int e)
    {

        vector<vector<int>> trip;
        int n = e + 1;

        int i = s;
        while (i < n)
        {
            auto v = twoSum(nums, target - nums[i], i + 1, n - 1);
            for (auto p : v)
                trip.push_back({nums[i], p.first, p.second});
            i++;
            while (i < n && nums[i] == nums[i - 1])
                i++;
        }
        return trip;
    }
    vector<pair<int, int>> twoSum(vector<int> &nums, ll target, int s, int e)
    {

        vector<pair<int, int>> pairs;
        while (s < e)
        {
            ll sum = nums[s] + nums[e];
            if (sum == target)
            {
                pairs.push_back({nums[s], nums[e--]});
                s++;
                while (s < nums.size() && nums[s] == nums[s - 1])
                    s++;
            }
            else if (sum > target)
                e--;
            else
                s++;
        }
        return pairs;
    }

public:
    vector<vector<int>> fourSum(vector<int> &nums, int target)
    {
        sort(nums.begin(), nums.end());
        vector<vector<int>> quads;
        int n = nums.size();

        int i = 0;
        while (i < n)
        {
            auto v = threeSum(nums, target - nums[i], i + 1, n - 1);
            for (auto p : v)
                quads.push_back({nums[i], p[0], p[1], p[2]});
            i++;
            while (i < n && nums[i] == nums[i - 1])
                i++;
        }
        return quads;
    }
};

// 4. Remove Duplicates from sorted Array
int removeDuplicates(vector<int> &nums)
{
    if (nums.size() <= 1)
        return nums.size();

    int i = 0, j = 1; // [0 to i] will have the unique elements
    while (j < nums.size())
    {
        if (nums[i] == nums[j])
            j++;
        else // found new
        {
            nums[i + 1] = nums[j];
            i++;
            j++;
        }
    }
    return i + 1; // till index i there are unique elements so size will be i+1
}

// 5. Squaring a Sorted Array
// i → 0, j → n-1, compare abs at j and i which is max put it's square at end of array. ⇒T:n; S:1
vector<int> sortedSquares(vector<int> &nums)
{
    vector<int> ans(nums.size()); // we will start filling ans from the end with the greatest value
    int i = 0, j = nums.size() - 1;

    for (int k = nums.size() - 1; k >= 0 && i <= j; k--)
    {
        if (abs(nums[i]) < abs(nums[j]))
        {
            ans[k] = (nums[j] * nums[j]);
            j--;
        }
        else
        {
            ans[k] = (nums[i] * nums[i]);
            i++;
        }
    }
    return ans;
}

// 6. Dutch national flag problem |Sort array of 0’s 1’s 2’s without extra space in linear time
void sortColors(vector<int> &arr)
{
    int n = arr.size();
    int i = -1, j = n, k = 0;
    // till i we have 0
    //  i+1 to k-1 we have 1
    //  from j we have 2
    int pivot = 1;
    while (k < j)
    {
        if (arr[k] < pivot)
            // swap(arr[++i],arr[k]); this was the mistake I did, i<k (must) but if we don't increment k and input is 001 i will get ahead of k
            swap(arr[++i], arr[k++]); // the value at i can be 0 or 1 so we can increase the k
        else if (arr[k] > pivot)      // the number we swapped may be 0, so we cannot increase k here
            swap(arr[--j], arr[k]);
        else // number is 1 so increase k
            k++;
    }
}

// 7. Comparing Strings containing Backspaces
bool backspaceCompare(string s, string t)
{

    int i = s.size() - 1, j = t.size() - 1;
    int count1 = 0, count2 = 0; // counts number of backspaces

    while (i >= 0 || j >= 0)
    {
        // find first occurence in string s
        while (i >= 0)
        {
            if (s[i] == '#') // count backspace
            {
                count1++;
                i--;
            }
            else if (s[i] != '#' && count1 > 0) // if count > 0 then the current char is deleted so ignore it
            {
                count1--;
                i--;
            }
            else
                break;
        }
        // find first occurence is string t
        while (j >= 0)
        {
            if (t[j] == '#')
            {
                count2++;
                j--;
            }
            else if (t[j] != '#' && count2 > 0)
            {
                count2--;
                j--;
            }
            else
                break;
        }
        if (j >= 0 && i >= 0 && s[i] != t[j]) // check if the characters are equal
            return false;
        if (i < 0 && j < 0) // reached the end of both the strings
            return true;
        if (i < 0 || j < 0) // reached the end of one of the strings and other string is still present
            return false;
        i--;
        j--;
    }
    return true;
}

// 8. Shortest Unsorted Continuous Subarray
int findUnsortedSubarray(vector<int> &nums)
{
    // Example: 1 3 4 5 2 6 7 8 6 10 12 14, i will point to 5 and j will point to 6
    int i = 0;
    int n = nums.size();
    while (i < n - 1)
    {
        if (nums[i] > nums[i + 1])
            break;
        i++;
    }
    // everything is sorted from 0 to i-1, so nothing to do
    if (i == n - 1)
        return 0;

    int j = n - 1;
    while (j > 0)
    {
        if (nums[j] < nums[j - 1])
            break;
        j--;
    }
    // find the smallest and largest elements b/w i and j
    int min_v = INT_MAX, max_v = INT_MIN;
    for (int k = i; k <= j; k++)
    {
        min_v = min(min_v, nums[k]);
        max_v = max(max_v, nums[k]);
    }
    // keep increasing the window size from left till the smallest in window is smaller
    while (i > 0 && min_v < nums[i - 1])
        i--;
    // keep increasing the window size from right till the largerst in window is larger
    while (j < n - 1 && max_v > nums[j + 1])
        j++;
    return j - i + 1; // window size
}
//