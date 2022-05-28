
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
1. Search a 2D Matrix
    1A. https://leetcode.com/problems/search-a-2d-matrix/
        -Integers in each row are sorted from left to right.
        -The first integer of each row is greater than the last integer of the previous row.
    1B. https://leetcode.com/problems/search-a-2d-matrix-ii/
        -Integers in each row are sorted in ascending from left to right.
        -Integers in each column are sorted in ascending from top to bottom.
2. Pow(x, n) n can be negative:https://leetcode.com/problems/powx-n/
3. Majority Element:https://leetcode.com/problems/majority-element/
4. Majority Element 2: https://leetcode.com/problems/majority-element-ii/
*/
// 1
class SearchMatrix
{
public:
    // 1A
    bool searchMatrix(vector<vector<int>> &matrix, int target)
    {

        int m = matrix.size();
        int n = matrix[0].size();

        int s = 0, e = m - 1;
        while (s < e)
        {
            int mid = s + (e - s) / 2;
            if (matrix[mid][n - 1] < target)
                s = mid + 1;
            else
                e = mid; // not mid-1 because the data might be at mid
        }
        return binary_search(matrix[e].begin(), matrix[e].end(), target);
    }
    // 1B
    bool searchMatrix2(vector<vector<int>> &matrix, int target)
    {
        if (matrix.size() == 0)
            return false;
        int rows = matrix.size();
        int cols = matrix[0].size();

        int rowStart = 0; // starting at top right corner
        int colStart = cols - 1;

        while (rowStart < rows && colStart >= 0)
        {
            int valuePresent = matrix[rowStart][colStart];
            if (valuePresent == target)
                return true;
            else if (valuePresent > target)
                colStart--;
            else
                rowStart++;
        }
        return false;
    }
};

// 2
class PowNegative
{
public:
    double myPow(double x, int n)
    {
        if (n == 0)
            return 1;

        bool negativePow = n < 0;
        bool oddPower = n % 2 != 0;

        int n_half = abs((long long)n / 2); // To avoid overflow, if n= -2147483648,then abs(n) also = -2147483648 due to overflow
        double value = myPow(x, n_half);
        value = value * value;

        value = oddPower ? value * x : value;

        return negativePow ? 1 / value : value;
    }
};
// 3
class MajorityElement
{
    // Boyer-Moore Majority Voting Algorithm

public:
    int majorityElement(vector<int> &nums)
    {
        int count = 1;
        int majElement = nums[0];
        for (int i = 1; i < nums.size(); i++)
        {
            if (count == 0) // till (i-1)th index no majority element whenever count is 0 we mark a new majority element
                majElement = nums[i];
            if (majElement == nums[i]) // if matches increase count
                count++;
            else // decrease count and if it becomes then the next index will become majority element
                count--;
        }

        // This second pass is neded when it is not guranteed that majority element exists. For example [5,5,7,7,1]: our code will return 1 as majority element
        /*
            int countMajElement = 0;
            for (auto v : nums)
               if (majElement == v)
                   countMajElement++;
            return countMajElement > (nums.size() / 2) ? majElement : INT_MIN;
        */
        return majElement; // if given in the ques majority element always exist
    }
};
// 4
class MajorityElement2
{
public:
    vector<int> majorityElement(vector<int> &nums)
    {
        // there can be only two elements which are >n/3
        // majority element will be left after forming triplets  example 1,2,3,1,2,3,1,3
        vector<int> majE;
        int cand1 = -1, cand2 = -1;
        int count1 = 0, count2 = 0;

        for (auto v : nums)
        {
            if (v == cand1)
                count1++;
            else if (v == cand2)
                count2++;
            else if (count1 == 0)
            {
                cand1 = v;
                count1 = 1;
            }
            else if (count2 == 0)
            {
                cand2 = v;
                count2 = 1;
            }
            else
            {
                count1--;
                count2--;
            }
        }
        // second pass to check if element is majority
        count1 = count2 = 0;
        for (auto v : nums)
        {
            if (v == cand1)
                count1++;
            else if (v == cand2)
                count2++;
        }
        if (count1 > nums.size() / 3)
            majE.push_back(cand1);
        if (count2 > nums.size() / 3)
            majE.push_back(cand2);

        return majE;
    }
};