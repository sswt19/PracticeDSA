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
1.
2. Merge Overlapping Subintervals: https://leetcode.com/problems/merge-intervals/
3. Merge two sorted Arrays without extra space
4.
5.
6.
*/

// 2
class MergeOvrInt
{
public:
    vector<vector<int>> merge(vector<vector<int>> &intervals)
    {
        sort(intervals.begin(), intervals.end(), [](vector<int> const &a, vector<int> const &b)
             { return a[0] < b[0]; });
        vector<vector<int>> merged;

        auto last = intervals[0];
        for (int i = 1; i < intervals.size(); i++)
        {
            if (last[1] < intervals[i][0])
            {
                merged.push_back(last);
                last = intervals[i];
            }
            else
                last[1] = max(last[1], intervals[i][1]);
        }
        merged.push_back(last);
        return merged;
    }
};
// 3
class MergeTwoSortedArray
{
public:
    void mergeNoExtraSpaceInAnyVector(vector<int> &nums1, int m, vector<int> &nums2, int n)
    {
        if (n == 0 || m == 0) // no need to merge
            return;
        while (nums1[m - 1] > nums2[0]) // last element of first array is greater than first element of second array
        {
            swap(nums1[m - 1], nums2[0]);
            for (int j = m - 1; j > 0; j--) // bring the new element in first array to correct place using bubble up
            {
                if (nums1[j - 1] > nums1[j])
                    swap(nums1[j - 1], nums1[j]);
                else
                    break;
            }
            for (int j = 0; j < n - 1; j++) // bring the new element in second array to correct place using bubble down
            {
                if (nums2[j] > nums2[j + 1])
                    swap(nums2[j], nums2[j + 1]);
                else
                    break;
            }
        }
    }
};