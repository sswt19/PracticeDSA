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
1. Rotate Matrix: https://leetcode.com/problems/rotate-image/
2. Merge Overlapping Subintervals: https://leetcode.com/problems/merge-intervals/
3. Merge two sorted Arrays without extra space: https://leetcode.com/problems/merge-sorted-array/
4.
5.
6. Inversion of Array
*/

// 1
class RotateImage
{
public:
    void rotate(vector<vector<int>> &matrix)
    {
        transpose(matrix);
        for (int i = 0; i < matrix.size(); i++)
            reverse(matrix[i].begin(), matrix[i].end());
    }
    void transpose(vector<vector<int>> &matrix)
    {
        int n = matrix.size();
        for (int t = 0; t < n; t++)
            for (int i = 0; i < n - t; i++)
            {
                int j = i + t;
                swap(matrix[i][j], matrix[j][i]);
            }
    }
};
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
    void merge(vector<int> &nums1, int m, vector<int> &nums2, int n)
    {
        int k = m + n - 1; // fill from the end
        int i = m - 1;
        int j = n - 1;

        while (i >= 0 && j >= 0)
        {
            if (nums2[j] > nums1[i])
                nums1[k--] = nums2[j--];
            else
                nums1[k--] = nums1[i--];
        }
        while (i >= 0)
            nums1[k--] = nums1[i--];
        while (j >= 0)
            nums1[k--] = nums2[j--];
    }
};

// 6
class InversionCount
{
public:
    long long getInversions(long long *arr, int n)
    {
        long long inv = 0;
        mergeSort(arr, 0, n - 1, inv);
        return inv;
    }
    void mergeSort(long long *arr, int s, int e, long long &inv)
    {
        if (s >= e) // never forget to write the base case
            return;
        int m = s + (e - s) / 2;
        mergeSort(arr, s, m, inv);
        mergeSort(arr, m + 1, e, inv);
        merge(arr, s, e, inv);
    }
    void merge(long long *arr, int s, int e, long long &inv)
    {
        int m = s + (e - s) / 2;
        int *arrCopy = new int[e - s + 1];
        int i = s, j = m + 1;
        int k = 0;
        while (i <= m && j <= e)
        {
            if (arr[i] <= arr[j])
                arrCopy[k++] = arr[i++];
            else
            {
                inv += m - i + 1; // this extra step is used for inversion count
                arrCopy[k++] = arr[j++];
            }
        }
        while (i <= m)
            arrCopy[k++] = arr[i++];
        while (j <= e)
            arrCopy[k++] = arr[j++];
        for (int k = 0; k <= e - s; k++)
            arr[s + k] = arrCopy[k];
    }
};