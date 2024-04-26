
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
2. Pow(x, n) n can be negative
    :https://leetcode.com/problems/powx-n/
3. Majority Element
    :https://leetcode.com/problems/majority-element/
4. Majority Element 2
    :https://leetcode.com/problems/majority-element-ii/
5. Unique Paths
    :https://leetcode.com/problems/unique-paths/description/

*/
// 1  Search a 2D Matrix
class SearchMatrix
{
public:
    // 1A
    bool searchMatrix(vector<vector<int>> &matrix, int target)
    {

        int m = matrix.size();    // rows
        int n = matrix[0].size(); // columns

        int s = 0, e = m - 1;
        int mid = s + (e - s) / 2;
        while (s < e)
        {
            if (matrix[mid][n - 1] == target)
                return true;
            else if (matrix[mid][n - 1] < target)
                s = mid + 1;
            else
                e = mid; // might be in same row of mid
            mid = s + (e - s) / 2;
        }
        return binary_search(matrix[mid].begin(), matrix[mid].end(), target);
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

// 2 Pow(x, n)
class PowNegative
{
public:
    // simple solution but because of overflow test case in test case of leetcode myPow2 is to handle overflow
    double myPow1(double x, int n)
    {
        if (n == 0)
            return 1;
        if (n < 0)
            return 1 / myPow1(x, abs(n)); // overflow will happen here, for n= -2147483648,then abs(n) also = -2147483648 due

        double x_pow_half_n = myPow1(x, n / 2);
        double ans = x_pow_half_n * x_pow_half_n;
        if (n & 1)
            ans = ans * x;
        return ans;
    }
    double myPow2(double x, int n)
    {
        if (n == 0)
            return 1;

        bool negativePow = n < 0;
        bool oddPower = n % 2 != 0;

        int n_half = abs((long long)n / 2); // To avoid overflow, if n= -2147483648,then abs(n) also = -2147483648 due to overflow
        double value = myPow2(x, n_half);
        value = value * value;

        value = oddPower ? value * x : value;

        return negativePow ? 1 / value : value;
    }
};

// 3 Majority Element
class MajorityElement
{
    /*
        Boyer - Moore Majority Voting Algorithm
        we will form pairs with majority element and remaining elements will be majority
    */

public:
    int
    majorityElement(vector<int> &nums)
    {
        int count = 0;
        int majElement = -1; // initialize with anything will be set with first if condition
        for (auto v : nums)
        {
            if (count == 0) // till now no majority element whenever count is 0 we mark a new majority element
            {
                majElement = v;
                count = 1;
            }
            else if (majElement == v) // if matches increase count
                count++;
            else
                //  pair of {current majE,v}, decrease count and if it becomes 0 then the next element will become majority element
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

// 4 Majority Element 2
class MajorityElement2
{
    /*
        majority element will be left after forming triplets  example (1,2,3) ,(1,2,3) ,(1,3)
        We will form triplets with possible candidates
    */
public:
    vector<int> majorityElement(vector<int> &nums)
    {
        // there can be only two elements which are >n/3
        vector<int> majE;
        int cand1, cand2, count1, count2;
        cand1 = cand2 = INT_MIN; // initialize to values which will not be present in nums array
        count1 = count2 = 0;

        for (auto v : nums)
        {
            /*
                we will need to match for cand1 and cand2 at start.
                we cannot assign v to cand1 or cand2 if the count is zero as we did in majority element 1,
                cand1 and cand2 might become same values
                Ex: test case where it will fail
                    2,1,1,3,1,4,5,6
                    both cand1 and cand2 will be set to 1 when we reach 5th element
            */
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
            else // formed one triplet with {cand1,cand2,v}
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
        // found majority Elements
        if (count1 > nums.size() / 3)
            majE.push_back(cand1);
        if (count2 > nums.size() / 3)
            majE.push_back(cand2);

        return majE;
    }
};

// 5 Unique Paths
class UniquePaths
{
    /*
        Permutation with repetition = n!/r1!*r2!..rk!
        we have to go right m-1 times and down n-1 times
        total ways= (m+n-2)!/(m-1)!*(n-1)!
    */
public:
    long long uniquePaths(int m, int n)
    {
        return ncr(m + n - 2, m - 1);
    }
    long long ncr(int n, int r)
    {
        if (r > n - r)
            return ncr(n, n - r);
        long long ans = 1;
        for (int i = 1; i <= r; i++)
            ans = (ans * (n - r + i)) / i;

        return ans;
    }
};

//