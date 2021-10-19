#include <vector>
#include <iostream>
#include <queue>
#include <stack>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <time.h>
using namespace std;

/*
1.Search a 2D Matrix:Integers in each row are sorted and  matrix[row][0] >= matrix[row-1][cols-1]
2.Search a 2D Matrix II:Integers in each row and col are sorted in ascending.
3.Merge Sort 
4.Quick Sort 
*/

// 1 Search a 2D Matrix, T:logn+logm S:1
bool searchMatrix(vector<vector<int>> &matrix, int target)
{
    auto p = searchMatrixPos(matrix, target);
    cout << p.first << "," << p.second << endl;
    return p.first != -1;
}
pair<int, int> binarySearchRow(vector<vector<int>> &matrix, int row, int colS, int colE, int target)
{
    while (colS <= colE) // applying binary search in a row
    {
        int mid = colS + (colE - colS) / 2;
        if (matrix[row][mid] == target)
            return {row, mid};
        else if (matrix[row][mid] > target)
            colE = mid - 1;
        else
            colS = mid + 1;
    }
    return {-1, -1};
}
pair<int, int> searchMatrixPos(vector<vector<int>> &matrix, int target)
{
    if (matrix.size() == 0) //Always have this check
        return {-1, -1};

    int rowSize = matrix.size();
    int colSize = matrix[0].size();
    pair<int, int> pos = {-1, -1}; // default target is not present

    //if matrix has only one row
    if (rowSize == 1)
    {
        pos = binarySearchRow(matrix, 0, 0, colSize - 1, target);
        return pos;
    }
    //Applying Binary Search on last coloumn to get the least value >= target and then apply binary search on that row
    int rowS = 0, rowE = rowSize - 1;
    int rowToSearch = -1;
    while (rowS <= rowE)
    {
        int midRow = rowS + (rowE - rowS) / 2;
        int value = matrix[midRow][colSize - 1];
        if (value == target)
        {
            pos = {midRow, colSize - 1};
            return pos;
        }
        else if (value > target)
        {
            rowToSearch = midRow;
            rowE = midRow - 1;
        }
        else
            rowS = midRow + 1;
    }
    if (rowToSearch == -1)
        return {-1, -1};
    return binarySearchRow(matrix, rowToSearch, 0, colSize - 1, target);
}

// 2 Search a 2D Matrix II T:n+m; S:1
bool searchMatrix(vector<vector<int>> &matrix, int target)
{
    if (matrix.size() == 0) //always check this condition
        return false;
    int rowSize = matrix.size();
    int colSize = matrix[0].size();

    int rowStart = 0;
    int colStart = colSize - 1; // starting from top right corder

    //Main Logic
    while (rowStart < rowSize && colStart >= 0)
    {
        int valuePresent = matrix[rowStart][colStart];
        if (valuePresent == target)
            return true;
        else if (valuePresent > target) //Everything in that coloumn is greater so not useful
            colStart--;
        else //Everything in that row is lower so not useful
            rowStart++;
    }
    return false;
}

// 3 Merge Sort
/* Steps
1.break into two smaller arrays 
2.sort both of them 
3. Merge them
*/
void merge(vector<int> &nums, int s, int e)
{
    int mid = s + (e - s) / 2;
    int i = s;                     //first sorted half start
    int j = mid + 1;               // second sorted half start
    vector<int> sorted(e - s + 1); // merged values will be stored here since we can't use the nums array
    int k = 0;
    while (i <= mid && j <= e)
    {
        if (nums[i] < nums[j])
            sorted[k++] = nums[i++];
        else
            sorted[k++] = nums[j++];
    }
    while (i <= mid)
        sorted[k++] = nums[i++];
    while (j <= e)
        sorted[k++] = nums[j++];
    k = s;
    for (auto v : sorted) // copy the sorted array to original array from index s to e
        nums[k++] = v;
}
void mergeSort(vector<int> &nums, int s, int e)
{
    if (s >= e) // size is 0 or 1 already sorted
        return;

    int mid = s + (e - s) / 2;
    mergeSort(nums, s, mid);
    mergeSort(nums, mid + 1, e);
    merge(nums, s, e);
}
//4 QuickSort
/*
/* 
1.Shuffle the array (since randomized algorithm)
2.find pivot  
3.sort two parts created by pivot 
*/
class QuickSort
{
public:
    vector<int> sortArray(vector<int> &nums)
    {
        shuffle(nums);
        quickSort(nums, 0, nums.size() - 1);

        return nums;
    }
    void shuffle(vector<int> &nums)
    {
        srand(time(NULL));
        for (int j = nums.size() - 1; j >= 2; j--)
        {
            int swapWith = rand() % (j - 1);
            swap(nums[j], nums[swapWith]);
        }
    }
    int findPivot(vector<int> &nums, int s, int e)
    {
        int pivotValue = nums[s];
        int i = s, j = e, k = s;
        while (k <= j)
        {
            if (nums[k] == pivotValue)
                k++;
            else if (nums[k] > pivotValue)
                swap(nums[k], nums[j--]);
            else
                swap(nums[i++], nums[k++]);
        }
        return i;
    }
    void quickSort(vector<int> &nums, int s, int e)
    {
        if (s >= e)
            return;
        int pivot = findPivot(nums, s, e);
        quickSort(nums, s, pivot - 1);
        quickSort(nums, pivot + 1, e);
    }
};