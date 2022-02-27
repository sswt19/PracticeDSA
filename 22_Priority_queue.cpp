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
typedef long long ll;

/*
1. Find Median from Data Stream
2. Kth largest element in a stream
3. K-th largest element in an unsorted array.
*/

// 1. Find Median from Data Stream
class MedianFinder
{
    // 2 pqs needed, pqmax for first half and pqmin for second half, if odd number of elements pqmax will have one more element, every element in pq_min>= pq_max
    priority_queue<int> pq_max;
    priority_queue<int, vector<int>, greater<int>> pq_min;

public:
    MedianFinder()
    {
    }

    void addNum(int num)
    {
        // These below 3 statements always make sure the elemnts of first half is always lower than the second half and the size of first half will increae by one
        pq_min.push(num);          // push to second half first
        pq_max.push(pq_min.top()); // //push the top element in pq_min to pq_max and remove from pq_min, this will handle in case the element was pushed should belong in first pq i.e pq_max
        pq_min.pop();

        // if the size difference becomes 2 remove one element and move to second half
        if (pq_max.size() - pq_min.size() == 2)
        {
            pq_min.push(pq_max.top());
            pq_max.pop();
        }
    }

    double findMedian()
    {
        // FindMedian: if both sizes are equal take from both top and retun avg else return from pqmax
        if (pq_max.size() == pq_min.size())
            return (double)(pq_min.top() + pq_max.top()) / 2;
        return pq_max.top();
    }
};

// 2 Kth largest element in a stream
class KthLargest
{
    priority_queue<int, vector<int>, greater<int>> pq_min; // the Largest will be at last of pq, second largest will be second last and so on
    int k;

public:
    KthLargest(int K, vector<int> &nums)
    {
        this->k = K;
        for (auto v : nums)
        {
            pq_min.push(v);
            if (pq_min.size() > k) // making sure size of pq_min always becomes of size k
                pq_min.pop();
        }
    }

    int add(int val)
    {
        pq_min.push(val);
        if (pq_min.size() > k)
            pq_min.pop();
        return pq_min.top();
    }
};
// 3 K-th largest element in an unsorted array.

// nlogk time complexity
int findKthLargest(vector<int> &nums, int k)
{
    priority_queue<int, vector<int>, greater<int>> pq_min;
    for (auto v : nums)
    {
        pq_min.push(v);
        if (pq_min.size() > k)
            pq_min.pop();
    }
    return pq_min.top();
}