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
using ll = long long;

/*
1. Rotate Matrix
    :https://leetcode.com/problems/rotate-image/
2. Merge Overlapping Subintervals
    :https://leetcode.com/problems/merge-intervals/
3. Merge two sorted Arrays without extra space
    :https://leetcode.com/problems/merge-sorted-array/
4. Inversion of Array

Cyclic Sort:
****************************************************************************************************************
-> Always try to see if we can solve it using XOR even if it is solvable by cyclic sort
-> Most Questions will be like there are n/n+1 numbers in the range from 0/1 to n-1/n/n+1 and need to use constant space
****************************************************************************************************************
5. CyclicSort
6. Missing Number
    :https://leetcode.com/problems/missing-number/
7. Find all Missing Numbers
    :https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/
8. Find the Duplicate Number
    :https://leetcode.com/problems/find-the-duplicate-number/
        Leetcode duplicate was repeated only ones
        Correct Ques Below:
            We are given an unsorted array containing ‘n+1’ numbers taken from the range 1 to ‘n’.
            The array has only one duplicate but it can be repeated multiple times.
            We are given an unsorted array containing ‘n+1’ numbers taken from the range 1 to ‘n’.
            The array has ỏ̉nly one duplicate but it can be repeated multiple times.
9. Find All Duplicates in an Array
    :https://leetcode.com/problems/find-all-duplicates-in-an-array/
10. Repeat and Missing Number Array
    :https://www.interviewbit.com/problems/repeat-and-missing-number-array/
11. First Missing Positive
    :https://leetcode.com/problems/first-missing-positive/
12. Find the First K Missing Positive Numbers
    :https://leetcode.com/problems/kth-missing-positive-number/

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

// 4
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

// Cyclic Sort Pattern
class CyclicSortTemplate
{
public:
    static int findNumber(vector<int> &arr)
    {

        int index = 0, n = arr.size();
        while (index < n)
        {
            // Check element is already at correct place if yes move ahead
            //  if (arr[index] == index) when mapping is like 2->2, n->n
            if (arr[index] == index + 1) // 0->1,1->2, ith index will have i+1 value
                index++;
            else // the current element is not at it's correct place
            {
                // int indexOfCurrentElement = arr[index] // for 2->2, n->n
                int indexOfCurrentElement = arr[index] - 1;   // find what is the correct place for current element
                if (arr[index] == arr[indexOfCurrentElement]) // cases where we might have to skip swapping
                    index++;
                else // swap to correct place
                    swap(arr[index], arr[indexOfCurrentElement]);
            }
        }
        // some further processing if needed
        return arr[n - 1];
    }
};

// 5
class CyclicSort
{
public:
    static void sort(vector<int> &arr)
    {
        // Numbers are from 1 to n
        // Index apping 0->1,1->2 i.e at index 0 1 should be present
        int index = 0, n = arr.size();
        while (index < n)
        {
            if (arr[index] == index + 1) // at index i the value should be i+1, if it is there we will move ahead
                index++;
            else
            {
                int indexOfCurrentElement = arr[index] - 1; // move the element to it's correct index, 3 will be moved to 3-1
                swap(arr[index], arr[indexOfCurrentElement]);
            }
        }
    }
};
// 6
class MissingNumber
{
public:
    static int findMissingNumber(vector<int> &arr)
    {
        // Index mapping 0->0,1->1
        int index = 0, n = arr.size();
        while (index < n)
        {
            if (arr[index] == index || arr[index] == n)
                index++;
            else
            {
                int indexOfCurrentElement = arr[index];
                if (arr[index] >= n)
                    index++;
                swap(arr[index], arr[indexOfCurrentElement]);
            }
        }
        for (int i = 0; i < n; i++)
            if (arr[i] != i)
                return i; // the element is not present at it's index
        return n;         // all element from 0 to n-1 are present
    }
    // XOR method
    int missingNumberXOR_solution(vector<int> &nums)
    {

        int xorV = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            xorV ^= nums[i];
            xorV ^= (i + 1);
        }
        return xorV;
    }
};
// 7
class AllMissingNumbers
{
public:
    static vector<int> findNumbers(vector<int> &arr)
    {
        // Index mapping 0->1,1->2
        vector<int> missingNumbers;
        int index = 0, n = arr.size();
        while (index < n)
        {
            if (arr[index] == index + 1)
                index++;
            else
            {
                int indexOfCurrentElement = arr[index] - 1;
                if (arr[index] == arr[indexOfCurrentElement]) // no need to swap since the number at the position to be swaped is same
                    index++;
                else
                    swap(arr[index], arr[indexOfCurrentElement]);
            }
        }
        for (int i = 0; i < n; i++)
            if (arr[i] != i + 1)
                missingNumbers.push_back(i + 1);
        return missingNumbers;
    }
};
// 8
class FindDuplicate
{
public:
    static int findNumber(vector<int> &arr)
    {
        // 0->1,1->2
        int index = 0, n = arr.size();
        while (index < n)
        {
            if (arr[index] == index + 1)
                index++;
            else
            {
                int indexOfCurrentElement = arr[index] - 1;
                if (arr[index] == arr[indexOfCurrentElement])
                    index++;
                else
                    swap(arr[index], arr[indexOfCurrentElement]);
            }
        }
        // since the numbers are b/w [1,n] and no of elements is n+1, 0->1,1->2,n-1->n, then nth index(since there are n+1 elements) will be mapped to repeating element̉̉
        return arr[n - 1];
    }
};
// 9
class FindAllDuplicate
{
public:
    static vector<int> findNumbers(vector<int> &arr)
    {
        // Index mapping 0->1,1->2
        vector<int> duplicateNumbers;
        int index = 0, n = arr.size();
        while (index < n)
        {
            if (arr[index] == index + 1)
                index++;
            else
            {
                int indexOfCurrentElement = arr[index] - 1;
                if (arr[index] == arr[indexOfCurrentElement]) // when both elements are same no need to swap
                    index++;
                else
                    swap(arr[index], arr[indexOfCurrentElement]);
            }
        }
        for (int i = 0; i < n; i++)
            if (arr[i] != i + 1)
                duplicateNumbers.push_back(arr[i]);

        return duplicateNumbers;
    }
};

// 10
class FindCorruptNums_OR_RepeatAndMissing
{
public:
    static vector<int> findNumbers(vector<int> &arr)
    {
        // Index mapping 0->1,1->2
        int index = 0, n = arr.size();
        while (index < n)
        {
            if (arr[index] == index + 1)
                index++;
            else
            {
                int indexOfCurrentElement = arr[index] - 1;
                if (arr[index] == arr[indexOfCurrentElement]) // when both elements are same no need to swap
                    index++;
                else
                    swap(arr[index], arr[indexOfCurrentElement]);
            }
        }
        for (int i = 0; i < n; i++)
            if (arr[i] != i + 1)
                return vector<int>{arr[i], i + 1}; // arr[i] is repeated and i+1 is missing
        return vector<int>{-1, -1};
    }
};

// 11
class FirstSmallestMissingPositive
{
public:
    static int findNumber(vector<int> &arr)
    {
        // The Smallest Missing Positive will be in [1,n+1] n+1 when the array contains 1 to n numbers.
        // We will try to place the numbers on their correct indices and ignore all numbers that are out of the range of the array (i.e.,0, all negative numbers  and all numbers greater than the length of the array).
        // Index mapping 0->1,1->2
        ll index = 0, n = arr.size();
        while (index < n)
        {
            if (arr[index] == index + 1)
                index++;
            else
            {
                ll indexOfCurrentElement = (ll)arr[index] - 1;
                if (arr[index] <= 0 || arr[index] > n || arr[indexOfCurrentElement] == arr[index]) // we will skip if num is <=0 or >n or equal to the number which we will be swapping with
                    index++;
                else
                    swap(arr[index], arr[indexOfCurrentElement]);
            }
        }
        for (int i = 0; i < n; i++) // find first smalles missing number from 1 to n
            if (arr[i] != i + 1)
                return i + 1;
        return n + 1; // if 1 to n are present the n+1 is the missing one
    }
};
// 12
class FirstKMissingPositive
{
public:
    int findKthPositive(vector<int> &arr, int k)
    {
        vector<int> missingNumbers;
        ll index = 0, n = arr.size();
        unordered_map<int, bool> mark;
        while (index < n)
        {
            if (arr[index] == index + 1)
                index++;
            else
            {
                ll indexOfCurrentElement = (ll)arr[index] - 1;
                if (arr[index] <= 0 || arr[index] > n || arr[indexOfCurrentElement] == arr[index])
                    index++;
                else
                    swap(arr[index], arr[indexOfCurrentElement]);
            }
        }

        for (int i = 0; i < n; i++)
        {
            if (arr[i] != i + 1 && missingNumbers.size() < k)
                missingNumbers.push_back(i + 1);
            if (arr[i] > n) // mark numbers so that they are not added to missing numbers list later Ex:[1,6] so 6 will be marked and not added to the missingNUmbers list
                mark[arr[i]] = true;
        }
        // add the remaining missing numbers
        for (int i = 1; missingNumbers.size() < k; i++)
        {
            int candidateNumber = i + arr.size(); // because missing numbers from [1,nums.size()] have already been added
            // ignore if the array contains the candidate number
            if (mark.find(candidateNumber) == mark.end())
                missingNumbers.push_back(candidateNumber);
        }
        return missingNumbers[k - 1];
    }
};