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
3. Min Required Meeting Rooms/ Platforms at Railway station
    : https://leetcode.com/problems/meeting-rooms-ii/
    :https://practice.geeksforgeeks.org/problems/n-meetings-in-one-room-1587115620/1#
4. N meetings in 1 room or Activity Selection
    :https://practice.geeksforgeeks.org/problems/n-meetings-in-one-room-1587115620/1#
5. Interal Covering with min points
    :https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/
6 Merge Overlapping Subintervals
    :https://leetcode.com/problems/merge-intervals/

*/

// 1 coin change Greedy will not work always, DP will always works
void mincoinChange(int amount, vector<int> &coins)
{
    sort(coins.begin(), coins.end(), [](const int &a, const int &b) // Sort coins in decreasing order of value
         { return a > b; });
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

// 3 Railway platforms required with platform/ room no
int minMeetingRooms(vector<vector<int>> &intervals)
{
    // Sort by start time, give room to one which starts first
    sort(intervals.begin(), intervals.end(), [](vector<int> const &a, vector<int> const &b)
         { return a[0] < b[0]; });
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq_min;
    pq_min.push({intervals[0][1], 1}); // push end time and room number;

    for (int i = 1; i < intervals.size(); i++)
    {
        if (pq_min.top().first <= intervals[i][0]) // we can use this room since the meeting in this room is already over
        {
            auto lastMeeting = pq_min.top();
            pq_min.pop();
            pq_min.push({intervals[i][1], lastMeeting.second});
        }
        else // need new room
            pq_min.push({intervals[i][1], pq_min.size() + 1});
    }

    return pq_min.size();
}

// 4 N meetings in 1 room or Activity Selection
int activitSelection(vector<pair<int, int>> &activities)
{
    sort(activities.begin(), activities.end(), [](const pair<int, int> &a, const pair<int, int> &b)
         { return a.second < b.second; }); // sort by end time
    int count = 0;
    int last = -1;
    for (int i = 0; i < activities.size(); i++)
    {
        if (activities[i].first > last)
        {
            count++;
            last = activities[i].second;
        }
    }
    return count;
}

// 5 Interal Covering with min points
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

// 6 Merge Intervals
vector<vector<int>> mergeIntervals(vector<vector<int>> &intervals)
{
    sort(intervals.begin(), intervals.end(), [](vector<int> const &a, vector<int> const &b)
         { return a[0] < b[0]; }); // sort by start time
    vector<vector<int>> merged;

    auto last = intervals[0];
    for (int i = 1; i < intervals.size(); i++)
    {
        if (last[1] < intervals[i][0]) // no overlap, one independent interval found
        {
            merged.push_back(last);
            last = intervals[i];
        }
        else                                         // there is a overlap merge them
            last[1] = max(last[1], intervals[i][1]); // pick the max end time
    }
    merged.push_back(last); // push the last remaining interval
    return merged;
}

// 7 Job Scheduling
// url:https : //practice.geeksforgeeks.org/problems/job-sequencing-problem-1587115620/1#
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

// T(n)=O(nlogn + n*maxDeadline) if maxDeadline is n then O(n^2)
vector<int> JobScheduling(Job arr[], int n)
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
