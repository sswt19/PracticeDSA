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
6. Reverse Pairs
    https://leetcode.com/problems/reverse-pairs/

Binary Search
1. Order-agnostic Binary Search (Array might be ascending or descending)
2. Ceiling of a Number
    :https://www.codingninjas.com/codestudio/problems/ceiling-in-a-sorted-array_1825401
3. Number Range : The range of the ‘key’ will be the first and last position of the ‘key’ in the array.
    :https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/
4. Search in a Sorted Infinite Array
    :https://www.codingninjas.com/codestudio/problems/search-in-infinite-sorted-0-1-array_696193
5. Minimum Difference Element

An array is considered bitonic if it is monotonically increasing and then monotonically decreasing.
Monotonically increasing or decreasing means that for any index i in the array arr[i] != arr[i+1].
6. Bitonic Array Maximum:
    :https://leetcode.com/problems/peak-index-in-a-mountain-array/
7. Search Bitonic Array
    :https://www.interviewbit.com/problems/search-in-bitonic-array/
8a. Search in Rotated Sorted Unique Array
    :https://leetcode.com/problems/search-in-rotated-sorted-array/
8b.
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
    if (matrix.size() == 0) // Always have this check
        return {-1, -1};

    int rowSize = matrix.size();
    int colSize = matrix[0].size();
    pair<int, int> pos = {-1, -1}; // default target is not present

    // if matrix has only one row
    if (rowSize == 1)
    {
        pos = binarySearchRow(matrix, 0, 0, colSize - 1, target);
        return pos;
    }
    // Applying Binary Search on last coloumn to get the least value >= target and then apply binary search on that row
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
    if (matrix.size() == 0) // always check this condition
        return false;
    int rowSize = matrix.size();
    int colSize = matrix[0].size();

    int rowStart = 0;
    int colStart = colSize - 1; // starting from top right corder

    // Main Logic
    while (rowStart < rowSize && colStart >= 0)
    {
        int valuePresent = matrix[rowStart][colStart];
        if (valuePresent == target)
            return true;
        else if (valuePresent > target) // Everything in that coloumn is greater so not useful
            colStart--;
        else // Everything in that row is lower so not useful
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
    int i = s;                     // first sorted half start
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
// 4 QuickSort

class QuickSort
{
    /*
1.Shuffle the array (since randomized algorithm)
2.find pivot
3.sort two parts created by pivot
*/
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

// 5 KokoEatingBananas
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

// 6  Reverse Pairs
class ReversePairs
{
public:
    void merge(vector<int> &nums, int s, int e, int &count)
    {
        int mid = s + (e - s) / 2;
        int i = s, j = mid + 1;

        // The actual part of computing nums[i]>2*nums[j], we will not modify the array here but compute the Reverse pairs
        while (i <= mid && j <= e)
        {
            long long numsi = nums[i];
            long long numsj = nums[j];
            if (numsi > 2 * numsj)
            {
                count += mid - i + 1;
                j++;
            }
            else
                i++;
        }
        // Merge sort merge functionality
        i = s;                         // first sorted half start
        j = mid + 1;                   // second sorted half start
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
    void mergeSort(vector<int> &nums, int s, int e, int &count)
    {
        if (s >= e)
            return;
        int mid = s + (e - s) / 2;
        mergeSort(nums, s, mid, count);
        mergeSort(nums, mid + 1, e, count);
        merge(nums, s, e, count);
    }
    int reversePairs(vector<int> &nums)
    {
        int count = 0;
        mergeSort(nums, 0, nums.size() - 1, count);
        return count;
    }
};

/*
==================================================Binary Search============================================
*/

//  1 Order-agnostic Binary Search
int orderAgnosticBinarySearch(vector<int> nums, int key)
{
    int n = nums.size();
    if (n == 0)
        return -1;
    // check if ascending order or descending order
    bool isAscending = nums[n - 1] > nums[0]; // comapare first and last element if they are same all elements in array are same
    int s = 0, e = n - 1;
    while (s <= e)
    {
        int mid = s + (e - s) / 2;
        if (nums[mid] == key)
            return mid;
        // above 2 statements are common in both
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
    return -1; // not present
}
// 2 Ceiling of a Number
int ceilingInSortedArray(int x, vector<int> arr)
{
    // whenever we find arr[mid]>=x we will save it and still keep finding for smalller ones
    int s = 0, e = arr.size() - 1;
    int ceil = -1;
    while (s <= e)
    {
        int mid = s + (e - s) / 2;
        if (arr[mid] >= x)
        {
            ceil = arr[mid]; // the current value might be the ceil so we will set it for now and try to find even smaller ceil
            e = mid - 1;
        }
        else
            s = mid + 1;
    }
    return ceil;
}
// 3. Number Range : The range of the ‘key’ will be the first and last position of the ‘key’ in the array.
vector<int> findRange(vector<int> &nums, int target)
{
    // Apply BS twice to get first and last occurence each
    int n = nums.size();
    if (n == 0)
        return {-1, -1};
    int startIndex = -1, endIndex = -1;
    // get start index
    int s = 0, e = n - 1;
    while (s <= e)
    {
        int mid = s + (e - s) / 2;
        if (nums[mid] == target) // even if we found the occurence we will keep trying to find the occurence on the left side
        {
            startIndex = mid;
            e = mid - 1;
        }
        else if (nums[mid] > target)
            e = mid - 1;
        else
            s = mid + 1;
    }
    if (startIndex == -1) // not found
        return {-1, -1};
    // get end index
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
// 4. Search in a Sorted Infinite Array
int get(int index) // supposed to return INT_MAX if access out of index else value at index
{
    return index;
}
int searchInfiniteSortedArray(int key)
{
    // first get the endIndex to do binarySearch
    int endIndex = 0;
    while (true)
    {
        if (get(endIndex) >= key) // we found arr[endIndex]>=key, The key will be in b/w [0,endIndex]
            break;
        else
            endIndex = (endIndex * 2) + 1;
    }
    // simple binary search to find the first occurence
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
// 5. Minimum Difference Element
int searchMinDiffElement(const vector<int> &arr, int key)
{
    if (key > arr.back())
        return arr.back();
    else if (key < arr.front())
        return arr.front();
    // we will find ceil
    int ceil = -1;
    int s = 0, e = arr.size() - 1;
    while (s <= e)
    {
        int mid = s + (e - s) / 2;
        if (arr[mid] == key)
            return arr[mid];
        else if (arr[mid] > key)
        {
            ceil = mid;
            e = mid - 1;
        }
        else
            s = mid + 1;
    }
    // ceil can not be 0 as it is handled at the start
    // arr[ceil-1] will be < key and arr[ceil] is > key out of these two one will be the answer
    if (arr[ceil] - key > key - arr[ceil - 1])
        return arr[ceil - 1];
    return arr[ceil];
}
// 6. Bitonic Array Maximum
/*
An array is considered bitonic if it is monotonically increasing and then monotonically decreasing.
Monotonically increasing or decreasing means that for any index i in the array arr[i] != arr[i+1].
*/
int peakIndexInBiotonicArray(vector<int> &arr)
{
    int n = arr.size();
    if (n <= 1)
        return n - 1;
    int s = 0, e = n - 1;
    int mid = s + (e - s) / 2;

    while (mid != 0 && mid != n - 1) // we can't compare if mid is at the start or last index
    {
        if (arr[mid] > arr[mid - 1] && arr[mid] > arr[mid + 1]) // found the peak element's index
            return mid;
        else if (arr[mid] > arr[mid + 1]) // in monotonically decreasing
            e = mid - 1;
        else // in monotonically increasing
            s = mid + 1;
        mid = s + (e - s) / 2;
    }
    // when s=0 and e=1, mid will never become 1 and we might miss the case where mid=1 is the peak
    // peak element can never be at 0 or n-1, because it is given that the peak element exists such that arr[peak-1]<arr[peak]>arr[peak+1]
    return mid == 0 ? 1 : mid;
}
// 7. Search Bitonic Array
int searchInBiotonicArray(vector<int> &A, int B)
{
    int peakIndex = peakIndexInBiotonicArray(A); // divide and use binary serach in two parts [0,peakIndex] and [peakIndex+1,n-1]
    // search in part1:increaing sorted array
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
    // search in part2:decreasing sorted array
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
    return -1; // not found
}
// 8a. Search in Rotated Sorted Unique Array
int search(vector<int> &nums, int target)
{
    // Explanation in notebook
    int s = 0, e = nums.size() - 1;
    while (s <= e)
    {
        int mid = s + (e - s) / 2;
        if (nums[mid] == target)
            return mid;
        else if (nums[mid] >= nums[s]) // check if it is the first section
        {
            if (nums[mid] > target && nums[s] <= target)
                e = mid - 1;
            else
                s = mid + 1;
        }
        else // in the second section
        {
            if (nums[e] >= target && nums[mid] < target)
                s = mid + 1;
            else
                e = mid - 1;
        }
    }
    return -1; // not found
}
// 8b.
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
        else // in the second section
        {
            if (nums[e] >= target && nums[mid] < target)
                s = mid + 1;
            else
                e = mid - 1;
        }
    }
    return false; // not found
}
// 9
//  10.
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
    if (n == 3)                 // when size is 3 we do not go inside while loop and mid will be set to 2
        if (nums[0] != nums[1]) // checking only at 0 since if it is not 2 will be returned
            return nums[0];

    return nums[mid];
}
