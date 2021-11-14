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
5.Koko Eating Bananas similar to Aggressive Cows
6.Order-agnostic Binary Search (Array might be ascending or descending)
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

//5 KokoEatingBananas
class KokoEatingBananas
{
public:
    int minEatingSpeed(vector<int> &piles, int h)
    {
        int minSpeed = 1;
        int maxSpeed = piles[0];
        for (auto v : piles)
            maxSpeed = max(maxSpeed, v);
        int ans = -1;
        while (minSpeed <= maxSpeed)
        {
            int mid = minSpeed + (maxSpeed - minSpeed) / 2;
            if (possible(piles, h, mid))
            {
                ans = mid;
                maxSpeed = mid - 1;
            }
            else
                minSpeed = mid + 1;
        }
        return ans;
    }
    bool possible(vector<int> &piles, int h, int speed)
    {
        for (auto v : piles)
        {
            h = h - ((v / speed) + (v % speed ? 1 : 0));
            if (h < 0)
                return false;
        }
        return true;
    }
};

//6 Binary Search
int binarySearch(vector<int> nums, int key)
{
    int n = nums.size();
    if (n == 0)
        return -1;
    bool isAscending = nums[n - 1] > nums[0];
    int s = 0, e = n - 1;
    while (s <= e)
    {
        int mid = s + (e - s) / 2;
        if (nums[mid] == key)
            return mid;
        //above 2 statements are common in both
        if (isAscending)
        {
            if (nums[mid] > key)
                e = mid - 1;
            else
                s = mid + 1;
        }
        else // for descending order
        {
            if (nums[mid] > key)
                s = mid + 1;
            else
                e = mid - 1;
        }
    }
    return -1;
}

int singleNonDuplicateinSortedArray(vector<int> &nums)
{
    int n = nums.size();
    int s = 0, e = n - 1;
    int mid = s + (e - s) / 2;
    if (mid & 1)
        mid++;
    while (mid != 0 && mid != n - 1)
    {
        if (nums[mid] != nums[mid + 1] && nums[mid] != nums[mid - 1])
            return nums[mid];
        else if (nums[mid] == nums[mid + 1])
            s = mid + 1;
        else
            e = mid - 1;
        mid = s + (e - s) / 2;
        if (mid & 1)
            mid++;
    }
    if (n == 3)                 //when size is 3 we do not go inside while loop and mid will be set to 2
        if (nums[0] != nums[1]) //checking only at 0 since if it is not 2 will be returned
            return nums[0];

    return nums[mid];
}

vector<int> searchRange(vector<int> &nums, int target)
{
    int n = nums.size();
    if (n == 0)
        return {-1, -1};
    int s = 0, e = n - 1;
    int startIndex = -1, endIndex = -1;
    while (s <= e)
    {
        int mid = s + (e - s) / 2;
        if (nums[mid] == target)
        {
            startIndex = mid;
            e = mid - 1;
        }
        else if (nums[mid] > target)
            e = mid - 1;
        else
            s = mid + 1;
    }
    if (startIndex == -1) //not found
        return {-1, -1};
    s = 0, e = n - 1;
    while (s <= e)
    {
        int mid = s + (e - s) / 2;
        if (nums[mid] == target)
        {
            endIndex = mid;
            s = mid + 1;
        }
        else if (nums[mid] > target)
            e = mid - 1;
        else
            s = mid + 1;
    }
    return {startIndex, endIndex};
}

int get(int index) //supposed to return INT_MAX if access out of index else value at index
{
    return index;
}
int searchInfSortedArray(int key)
{
    // TODO: Write your code here
    //first get the endIndex to do binarySearch
    int endIndex = 0;
    while (true)
    {
        if (get(endIndex) >= key)
            break;
        else
            endIndex = (endIndex * 2) + 1;
    }
    int s = 0, e = endIndex;
    int firstOccurence = -1;
    while (s <= e)
    {
        int mid = s + (e - s) / 2;
        if (get(mid) == key)
        {
            firstOccurence = mid;
            e = mid - 1;
        }
        else if (get(mid) > key)
            e = mid - 1;
        else
            s = mid + 1;
    }
    return firstOccurence;
}

int peakIndexInBiotonicArray(vector<int> &arr)
{
    int n = arr.size();
    if (n <= 1)
        return n - 1;
    int s = 0, e = n - 1;
    int mid = s + (e - s) / 2;

    while (mid != 0 && mid != n - 1)
    {
        if (arr[mid] > arr[mid - 1] && arr[mid] > arr[mid + 1])
            return mid;
        else if (arr[mid] > arr[mid + 1])
            e = mid - 1;
        else
            s = mid + 1;
        mid = s + (e - s) / 2;
    }
    if (mid == 0)
        if (arr[0] < arr[1])
            mid = 1;
    return mid;
}

int searchInBiotonicArray(vector<int> &A, int B)
{
    int peakIndex = peakIndexInBiotonicArray(A); //divide and use binary serach in two parts [0,peakIndex] and [peakIndex+1,n-1]
    //search in part1:increaing sorted array
    int s = 0, e = peakIndex;
    while (s <= e)
    {
        int mid = s + (e - s) / 2;
        if (A[mid] == B)
            return mid;
        else if (A[mid] > B)
            e = mid - 1;
        else
            s = mid + 1;
    }
    //search in part2:decreasing sorted array
    s = peakIndex + 1, e = A.size() - 1;
    while (s <= e)
    {
        int mid = s + (e - s) / 2;
        if (A[mid] == B)
            return mid;
        else if (A[mid] > B)
            s = mid + 1;
        else
            e = mid - 1;
    }
    return -1; //not found
}

bool searchRotatedSortedArrayWithDuplicates(vector<int> &nums, int target)
{
    int s = 0, e = nums.size() - 1;

    while (s <= e)
    {
        int mid = s + (e - s) / 2;
        if (nums[mid] == target)
            return true;
        if ((nums[s] == nums[mid]) && (nums[e] == nums[mid]))
        {
            s++;
            e--;
        }
        else if (nums[mid] >= nums[s]) // check if it is the first section and a case where s==mid hence greater than equal to
        {
            if (nums[mid] > target && nums[s] <= target)
                e = mid - 1;
            else
                s = mid + 1;
        }
        else //in the second section
        {
            if (nums[e] >= target && nums[mid] < target)
                s = mid + 1;
            else
                e = mid - 1;
        }
    }

    return false; // not found
}