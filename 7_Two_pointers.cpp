
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
1. Two Sum:
    url sorted input: https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/
    url unsorted input: https://leetcode.com/problems/two-sum/
2. Three Sum:
    url: https://leetcode.com/problems/3sum/
3. Four Sum:
    url:
4. Remove Duplicates from sorted Array:
    url: https://leetcode.com/problems/remove-duplicates-from-sorted-array/
5. Squaring a Sorted Array
    url: https://leetcode.com/problems/squares-of-a-sorted-array/

*/
// 1. Two Sum Sorted Array
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
// 2.
class UniqueThreeSum
{
public:
    vector<vector<int>> threeSum(vector<int> &nums)
    {

        int target = 0;
        vector<vector<int>> trip;
        sort(nums.begin(), nums.end()); // sort so that we can use pointers at start and end
        int n = nums.size();

        int i = 0;
        while (i < n)
        {
            auto v = twoSum(nums, target - nums[i], i + 1, n - 1);
            for (auto p : v)
                trip.push_back({nums[i], p.first, p.second});
            i++;
            // skip same element to avoid duplicate triplets
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
                s++;
                // skip same element to avoid duplicate pairs
                while (s < nums.size() && nums[s] == nums[s - 1]) // this line makes sure there are unique pairs
                    s++;
                e--;
            }
            else if (sum > target)
                e--;
            else
                s++;
        }
        return pairs;
    }
};
// 3.

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
    vector<int> ans(nums.size());
    int i = 0, j = nums.size() - 1;

    for (int k = nums.size() - 1; k >= 0; k--)
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