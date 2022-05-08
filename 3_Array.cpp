
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
1. Search a 2D Matrix
    1A. https://leetcode.com/problems/search-a-2d-matrix/
        -Integers in each row are sorted from left to right.
        -The first integer of each row is greater than the last integer of the previous row.
    1B. https://leetcode.com/problems/search-a-2d-matrix-ii/
        -Integers in each row are sorted in ascending from left to right.
        -Integers in each column are sorted in ascending from top to bottom.
2.
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
