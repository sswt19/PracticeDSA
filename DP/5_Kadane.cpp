#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/*
Pattern: Kadane : O(n)
URL: https://leetcode.com/problems/maximum-subarray/

Problems
1.
*/
class PatternKadane
{
public:
    // we can use index to store the subarray
    // whenever ls changes make li=le=i,else le++
    // whenever gs changes make gi=li and ge=le
    int maxSubArray(vector<int> &nums)
    {

        int ls, gs;
        ls = gs = nums[0];

        /*
        DP : because we are using value of i-1 stored in ls

        CRUX: max subarray sum ending at index i is arr[i] or arr[i]+ls,
        ls is max subarray sum till index i-1,
        we will find if subarray will grow and add index i or reduce to size 1 containing only index i
        we use gs to know which was max subarray ending at i for all i
        */
        for (int i = 1; i < nums.size(); i++)
        {
            ls = max(ls + nums[i], nums[i]);
            gs = max(ls, gs);
        }
        return gs;
    }
};
