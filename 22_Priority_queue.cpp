#include <vector>
#include <iostream>
#include <queue>
#include <stack>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <list>
#include <sstream>
#include <set>
using namespace std;
typedef long long ll;

/*
1. Find Median from Data Stream
    url: https://leetcode.com/problems/find-median-from-data-stream/
2. Sliding Window Median
    url: https://leetcode.com/problems/sliding-window-median/
3. Maximize Capital
    url: https://leetcode.com/problems/ipo/
4. Next Interval
    url: https://leetcode.com/problems/find-right-interval/
5. Kth largest element in a stream
    url: https://leetcode.com/problems/kth-largest-element-in-a-stream/
6. K-th largest element in an unsorted array.
    url:https://leetcode.com/problems/kth-largest-element-in-an-array/
7. Minimum Cost to Connect Sticks
    You can connect any two sticks of lengths x and y into one stick by paying a cost of x + y.
    You must connect all the sticks until there is only one stick remaining.
    Return the minimum cost of connecting all the given sticks into one stick in this way.
    url:https://leetcode.com/problems/minimum-cost-to-connect-sticks/
8. Last Stone Weight
    url:https://leetcode.com/problems/last-stone-weight/description/

*/

// 1. Find Median from Data Stream
class MedianFinderPriorityQueue
{
    // 2 pqs needed, pqmax for first half and pqmin for second half, if odd number of elements pqmax will have one more element, every element in pq_min>= pq_max
    priority_queue<int> pq_max;
    priority_queue<int, vector<int>, greater<int>> pq_min;

public:
    MedianFinderPriorityQueue()
    {
    }

    void addNum(int num)
    {
        // These below 3 statements always make sure the elemnts of first half is always lower than the second half and the size of first half will increase by one
        pq_min.push(num);          // push to second half first
        pq_max.push(pq_min.top()); // //push the top element in pq_min to pq_max and remove from pq_min, this will handle in case the element was pushed should belong in first pq i.e pq_max
        pq_min.pop();

        // if the size difference becomes 2 remove one element and move to second half, since we are always increasing pq_max size this will happen
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

// 2. Sliding Window Medians
class MedianFinderMultiSet
{
    // we can not use set because there might be multiple elements like 1,2,2,3,4,4,5
    // every operation in logn here
    multiset<int> min_heap;
    multiset<int, greater<int>> max_heap;

public:
    MedianFinderMultiSet()
    {
    }
    void addNum(int num)
    {
        // this makes sure the size of maz_heap is increased by one
        min_heap.insert(num);
        int top = *min_heap.begin();
        max_heap.insert(top);
        // erase from min_heap
        auto itr = min_heap.find(top);
        if (itr != min_heap.end())
            min_heap.erase(itr);

        // if the diff is 2 rebalance the heaps
        if (max_heap.size() - min_heap.size() == 2)
        {
            int value = *max_heap.begin();
            min_heap.insert(value);
            auto itr = max_heap.find(value);
            if (itr != max_heap.end())
                max_heap.erase(itr);
        }
    }

    double findMedian()
    {
        double median;
        if (max_heap.size() == min_heap.size())
        {
            ll sum = *min_heap.begin();
            sum += *max_heap.begin();
            median = (double)(sum) / 2;
        }
        else
            median = *max_heap.begin();
        return median;
    }
    void erase(int value)
    {

        if (value > *max_heap.begin()) // remove in minheap
        {
            auto itr = min_heap.find(value);
            if (itr != min_heap.end())
                min_heap.erase(itr);
        }
        else // remove in max_heap and then insert one value from min_heap if the min heap is not empty
        {
            auto itr = max_heap.find(value);
            if (itr != max_heap.end())
                max_heap.erase(itr);
            // insert one element from min heap
            if (min_heap.size() > 0)
            {
                int top = *min_heap.begin();
                max_heap.insert(top);
                itr = min_heap.find(top);
                if (itr != min_heap.end())
                    min_heap.erase(itr);
            }
        }
        if (max_heap.size() - min_heap.size() == 2)
        {
            int value = *max_heap.begin();
            min_heap.insert(value);
            auto itr = max_heap.find(value);
            if (itr != max_heap.end())
                max_heap.erase(itr);
        }
    }
};
vector<double> medianSlidingWindow(vector<int> &nums, int k)
{
    vector<double> medians;
    MedianFinderMultiSet mf;
    int winS = 0, winE = 0;
    int n = nums.size();
    while (winE < n)
    {
        // add the new element to heaps and balance them
        mf.addNum(nums[winE]);
        if (winE - winS + 1 == k)
        {
            medians.push_back(mf.findMedian());
            // decrease window size from left
            mf.erase(nums[winS]);
            winS++;
        }
        winE++; // increase window size from left
    }
    return medians;
}

// 3. Maximize Capital
int findMaximizedCapital(int k, int w, vector<int> &profits, vector<int> &capital)
{
    int n = capital.size();
    vector<pair<int, int>> proj(n); // in cost,profit format
    for (int i = 0; i < n; i++)
        proj[i] = {capital[i], profits[i]};
    sort(proj.begin(), proj.end()); // sorted by cost

    int invested = 0;
    int cur_cap = w;
    int i = 0;                  // pointer for proj to keep pushing to heap, the projects whose capital is afordable now
    priority_queue<int> pq_max; // profits of projects currently possible
    while (invested < k)
    {
        while (i < n && proj[i].first <= cur_cap)
        {
            pq_max.push(proj[i].second);
            i++;
        }
        // we will invest in whatever is top of heap with max profit
        if (pq_max.empty()) // we can't invest
            break;
        invested++;
        cur_cap += pq_max.top();
        pq_max.pop();
    }
    return cur_cap;
}

// 4. Next Interval
vector<int> findRightInterval(vector<vector<int>> &intervals)
{
    /*
     we can just sort intervals by start time
     and do binary search for each endtime in start time vector to get the answer
    */
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq_min_start; // sorted by start time, pair<start,index>
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq_min_end;   // sorted by end time, pair<end,index>

    vector<int> ans(intervals.size(), -1);
    for (int i = 0; i < intervals.size(); i++)
    {
        pq_min_start.push({intervals[i][0], i});
        pq_min_end.push({intervals[i][1], i});
    }
    // now for all elements in pq_min_end we will find the right interval from pq_min_start
    while (!pq_min_end.empty())
    {
        auto p = pq_min_end.top();
        pq_min_end.pop();
        int index = p.second;
        int end = p.first;
        while (!pq_min_start.empty() && end > pq_min_start.top().first) // the current top element of pq_min_start can not be used by any pair remaining in pq_min_end so we can remove it
            pq_min_start.pop();
        if (pq_min_start.empty()) // for all remaining intervals in pq_min_end we can keep them -1
            break;
        ans[index] = pq_min_start.top().second;
    }
    return ans;
}

// 5 Kth largest element in a stream
// T:nlogk  S:k (size of the heap)
class KthLargest
{
    priority_queue<int, vector<int>, greater<int>> pq_min; // the Largest will be at last of pq, second largest will be second last and so on
    int k;

public:
    KthLargest(int k, vector<int> &nums)
    {
        this->k = k;
        for (auto v : nums)
            this->add(v); // use the add function implemented
    }

    int add(int val)
    {
        pq_min.push(val);
        if (pq_min.size() > k) // making sure size of pq_min always becomes of size k
            pq_min.pop();
        return pq_min.top();
    }
};

// 6 K-th largest element in an unsorted array.
// T:nlogk S:k
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

// 7 Minimum Cost to Connect Sticks
int connectSticks(vector<int> &sticks)
{
    // we need to minimize cost so adding two smallest ones that we will have minimum x+y
    int cost = 0;
    priority_queue<int, vector<int>, greater<int>> pq_min;
    for (auto x : sticks)
        pq_min.push(x);
    while (pq_min.size() > 1)
    {
        int x = pq_min.top();
        pq_min.pop();
        int y = pq_min.top();
        pq_min.pop();
        cost += x + y;
        pq_min.push(x + y);
    }
    return cost;
}

// 8. Last Stone Weight
// (T:nlogn, S:n)
class LastStoneWeight
{
public:
    int lastStoneWeight(vector<int> &stones)
    {
        priority_queue<int> pq_max;
        for (auto s : stones)
            pq_max.push(s);
        while (pq_max.size() > 1) // only if there are 2 or more stones
        {
            auto y = pq_max.top();
            pq_max.pop();
            auto x = pq_max.top();
            pq_max.pop();
            if (y != x)
                pq_max.push(y - x);
        }
        return pq_max.empty() ? 0 : pq_max.top();
    }
};
//
