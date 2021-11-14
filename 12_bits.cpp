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
1.Every number appears twice except one number
2.Two numbers appears once others twice
3.Every number appears thrice except one number
*/
int singleNumberOthersTwice(vector<int> &nums)
{
    int xorv = 0;
    for (auto x : nums)
        xorv ^= x;
    return xorv;
}
vector<int> twoNumberOnceOthersTwice(vector<int> &nums)
{
    int xorv = 0;
    int firstNum = 0;
    int secondNum = 0;

    for (auto x : nums)
        xorv ^= x;

    int rightMostOne = 1;
    while ((rightMostOne & xorv) == 0)
        rightMostOne = rightMostOne << 1;

    for (auto x : nums)
        if (x & rightMostOne)
            firstNum ^= x;

    secondNum = xorv ^ firstNum;
    return {firstNum, secondNum};
}
int singleOnceOtherThrice(vector<int> &nums)
{
    vector<int> bitCount(32, 0);
    int uniqueNum = 0;
    for (int i = 0; i < 32; i++)
    {
        int mask = 1 << i;
        for (int v : nums)
            if (mask & v)
                bitCount[i]++;
        bitCount[i] %= 3;
        if (bitCount[i])
            uniqueNum = uniqueNum | mask;
    }
    return uniqueNum;
}