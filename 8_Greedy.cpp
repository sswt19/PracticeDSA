#include <vector>
#include <iostream>
#include <queue>
#include <stack>
#include <unordered_map>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

/*

1. Greedy coin change
2. Fractional Knapsack
    :https://practice.geeksforgeeks.org/problems/fractional-knapsack-1587115620/1
3. Min Required Meeting Rooms or Min Platforms required at Railway station
    :https://leetcode.com/problems/meeting-rooms-ii/
    :https://practice.geeksforgeeks.org/problems/minimum-platforms-1587115620/1#
4. N meetings in 1 room or Activity Selection
    :https://practice.geeksforgeeks.org/problems/n-meetings-in-one-room-1587115620/1#
5. Merge Overlapping Subintervals
    :https://leetcode.com/problems/merge-intervals/
6. Job Scheduling
    :https://practice.geeksforgeeks.org/problems/job-sequencing-problem-1587115620/1#
7. Insert Interval
    :https://leetcode.com/problems/insert-interval/
8. Interal Covering with min points
    :https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/
*/

// 1 coin change Greedy will not work always, DP will always works
class CoinChangeGreedy
{
public:
    void mincoinChange(int amount, vector<int> &coins)
    {
        sort(coins.begin(), coins.end(), [](const int &a, const int &b)
             { return a > b; }); // Sort coins in decreasing order of value
        int i = 0;
        while (amount > 0)
        {
            if (coins[i] <= amount)
            {
                int coin = amount / coins[i];
                cout << coins[i] << ":" << coin << endl;
                amount -= (coin * coins[i]);
            }
            i++;
        }
    }
};

// 2 Fractional Knapsack, T(n)=O(n*logn)
struct Item
{
    int value;
    int weight;
};
bool compEff(const Item &a, const Item &b)
{
    double eff_a = (1.0 * a.value) / a.weight;
    double eff_b = (1.0 * b.value) / b.weight;

    return eff_a > eff_b;
}
class FractionalKnapsack
{
public:
    double fractionalKnapsack(int W, Item arr[], int n)
    {
        // Your code here
        sort(arr, arr + n, compEff); // sort by decreasing value/Weight
        double maxValue = 0.0;
        for (int i = 0; i < n && W > 0; i++)
        {
            if (arr[i].weight <= W) // pick whole item
            {
                maxValue += arr[i].value;
                W -= arr[i].weight;
            }
            else // fractional Item
            {
                maxValue += (arr[i].value * 1.0) * (W / (1.0 * arr[i].weight));
                W = 0;
            }
        }
        return maxValue;
    }
};

// 3 Railway platforms required with platform/ room no
class MinMeetingRooms
{
public:
    int findPlatform(int arr[], int dep[], int n)
    {
        // have it in same vector to sort
        vector<vector<int>> intervals(n);
        for (int i = 0; i < n; i++)
            intervals[i] = {arr[i], dep[i]};

        // Sort by start time, give room to one which starts first
        sort(intervals.begin(), intervals.end(), [](vector<int> const &a, vector<int> const &b)
             { return a[0] < b[0]; });

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq_min;

        for (int i = 0; i < intervals.size(); i++)
        {
            // <= or < depending what the criteria is for sharing same station with same departure and arrival time of two trains
            if (pq_min.size() != 0 && pq_min.top().first < intervals[i][0]) // we can use this room since the meeting in this room is already over
            {
                auto lastMeeting = pq_min.top();
                pq_min.pop();
                pq_min.push({intervals[i][1], lastMeeting.second}); // alocate the meeting room to new meeting
            }
            else // need new room, since we can't use all existing meeting rooms
                pq_min.push({intervals[i][1], pq_min.size() + 1});
        }
        return pq_min.size();
    }
};

// 4 N meetings in 1 room or Activity Selection
class ActivitSelection
{
    /*
        We will sort by end time and will pick ones who ends earliest
        1. Why? when we pick the first activity, it will be one which ends earliest and we will get more time to do other activities.
        2. If instead of this we picked something else it will end after then what we have now, so it will give us less time to try other activities
    */
public:
    int maxMeetings(int start[], int end[], int n)
    {
        vector<pair<int, int>> activities(n);
        for (int i = 0; i < n; i++)
            activities[i] = {start[i], end[i]};
        sort(activities.begin(), activities.end(), [](const pair<int, int> &a, const pair<int, int> &b)
             { return a.second < b.second; }); // sort by endtime

        int count = 0;
        int last = -1;
        for (auto activity : activities)
        {
            if (activity.first > last) // we can do this activity
            {
                last = activity.second;
                count++;
            }
        }
        return count;
    }
};

// 5 Merge Intervals
vector<vector<int>> mergeIntervals(vector<vector<int>> &intervals)
{ /*
     a. Sort by start time, the first interval's start time will be the same as sorted list's 1st interval's start time
     b. Keep merging all intervals whose start is less than or equal to current_intervals's end time
     c. if start of an interval is higher than current_interval's end, we found an interval, since all remaining intervals's start will be higher as well
 */
    // a
    sort(intervals.begin(), intervals.end(), [](vector<int> const &a, vector<int> const &b)
         { return a[0] < b[0]; }); // sort by start time
    vector<vector<int>> merged;

    auto last = intervals[0];
    for (int i = 1; i < intervals.size(); i++)
    {
        // c
        if (last[1] < intervals[i][0]) // no overlap, one independent interval found
        {
            merged.push_back(last);
            last = intervals[i];
        }
        // b
        else                                         // there is a overlap merge them
            last[1] = max(last[1], intervals[i][1]); // pick the max end time
    }
    merged.push_back(last); // push the last remaining interval
    return merged;
}

// 6  Job Scheduling
struct Job
{
    int id;     // Job Id
    int dead;   // Deadline of job
    int profit; // Profit if job is over before or on deadline
};

bool comp(const Job &a, const Job &b)
{
    return a.profit > b.profit;
}

class DSU
{
    int *parents;

public:
    DSU(int n)
    {
        parents = new int[n + 1];
        for (int i = 0; i <= n; i++)
            parents[i] = i;
    }

    int get_superParent(int x)
    {
        if (x == parents[x])
            return x;

        parents[x] = get_superParent(parents[x]);
        return parents[x];
    }

    void unite(int x, int y)
    {
        int super_x = get_superParent(x);
        int super_y = get_superParent(y);

        parents[super_y] = super_x;
    }
};
class JobScheduling
{
public:
    // T(n)=O(nlogn + n*maxDeadline) if maxDeadline is n then O(n^2)
    vector<int> JobSchedulingSlow(Job arr[], int n)
    {

        int maxDeadline = -1;
        for (int i = 0; i < n; i++)
            maxDeadline = max(maxDeadline, arr[i].dead);

        // to store which id is executed at what time
        vector<int> allocated(maxDeadline + 1, -1);
        sort(arr, arr + n, comp);

        int count = 0;
        int maxProfit = 0;
        for (int i = 0; i < n; i++)
        {
            int deadline = arr[i].dead;
            for (int j = deadline; j > 0; j--)
            {
                if (allocated[j] == -1)
                {
                    allocated[j] = arr[i].id;
                    count++;
                    maxProfit += arr[i].profit;
                    break;
                }
            }
        }
        // returns no of jobs and maxProfit
        return {count, maxProfit};
    }
    // T(n)=O(nlogn +nlogn(only path compression used not unoin by rank) )
    vector<int> JobSchedulingFast(Job arr[], int n)
    {

        int maxDeadline = -1;
        for (int i = 0; i < n; i++)
            maxDeadline = max(maxDeadline, arr[i].dead);

        DSU allocated(maxDeadline);
        sort(arr, arr + n, comp);

        int count = 0;
        int maxProfit = 0;
        for (int i = 0; i < n; i++)
        {
            int available = allocated.get_superParent(arr[i].dead);

            if (available > 0)
            {
                allocated.unite(available - 1, available);
                count++;
                maxProfit += arr[i].profit;
            }
        }
        // returns no of jobs and maxProfit
        return {count, maxProfit};
    }
};

// 7 Insert Interval
vector<vector<int>> insert(vector<vector<int>> &intervals, vector<int> &newInterval)
{
    vector<vector<int>> merged;

    int i = 0; // to keep track of which interval we are processing right now
    while (i < intervals.size() && intervals[i][1] < newInterval[0])
    {
        merged.push_back(intervals[i]); // push interval if  start of new interval> end of interval we are processing
        i++;
    }
    // we might have encountered an end time which is greater than start of new interval so new interval might have an overlap
    while (i < intervals.size() && intervals[i][0] <= newInterval[1]) // start of current interval <= end of new interval there is overlap
    {
        newInterval[0] = min(newInterval[0], intervals[i][0]);
        newInterval[1] = max(newInterval[1], intervals[i][1]);
        i++;
    }
    merged.push_back(newInterval);

    while (i < intervals.size())
    {
        merged.push_back(intervals[i]);
        i++;
    }
    return merged;
}

// 8 Interal Covering with min points
int findMinArrowShots(vector<vector<int>> &points)
{
    sort(points.begin(), points.end(), [](vector<int> const &a, vector<int> const &b)
         { return a[1] < b[1]; }); // sort by end time

    vector<int> ans;
    int last = points[0][1];
    ans.push_back(last);
    // We will use activity selection and see which intervals are colliding
    for (int i = 1; i < points.size(); i++)
    {
        if (points[i][0] > last) // new point needed since no collision for this interval
        {
            last = points[i][1]; // new point
            ans.push_back(last);
        }
    }
    return ans.size();
}
