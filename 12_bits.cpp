#include <vector>
#include <iostream>
#include <queue>
#include <stack>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <time.h>
#include <math.h>
using namespace std;
/*
1. Complement of Base 10 Integer
    :https://leetcode.com/problems/complement-of-base-10-integer/
2. Every number appears twice except one number
    :https://leetcode.com/problems/single-number/
3. Two numbers appears once others twice
    :https://leetcode.com/problems/single-number-iii/
4. Every number appears thrice except one number
    :https://leetcode.com/problems/single-number-ii/
5. Flipping an Image
    :https://leetcode.com/problems/flipping-an-image/
*/

// 1
int bitwiseComplement(int num)
{
    if (num == 0)
        return 1;

    int bitCounts = 0;
    int temp = num;
    while (temp)
    {
        bitCounts++;
        temp = temp >> 1;
    }
    int all_ones = pow(2, bitCounts) - 1;
    return num ^ all_ones;
}
// 2
int singleNumberOthersTwice(vector<int> &nums)
{
    int xorv = 0;
    for (auto x : nums)
        xorv ^= x;
    return xorv;
}
// 3
vector<int> twoNumberOnceOthersTwice(vector<int> &nums)
{
    int xorv = 0;
    int firstNum = 0;
    int secondNum = 0;

    for (auto x : nums) // xorv will contain num1^num2
        xorv ^= x;

    int rightMostOne = 1;
    while ((rightMostOne & xorv) == 0) // find the first rightmost bit of xorv, this bit is different b/w num1 and num2
        rightMostOne = rightMostOne << 1;

    for (auto x : nums) // xor all numbers with that right bit set so we will get num1
        if (x & rightMostOne)
            firstNum ^= x;

    secondNum = xorv ^ firstNum; // use the firstnum and xorv to get second one
    return {firstNum, secondNum};
}

// 4
int singleOnceOtherThrice(vector<int> &nums)
{
    vector<int> bitCount(32, 0); // count the number of set bits for each bit out of 32 bit
    int uniqueNum = 0;
    for (int i = 0; i < 32; i++)
    {
        int mask = 1 << i; // mask for each bit
        for (int v : nums)
            if (mask & v) // if bit is set for a number increase the bit count
                bitCount[i]++;
        bitCount[i] %= 3; // there will be remainder 1 for the bit of number which is present once

        if (bitCount[i]) // if it is there set the bit ith bit for single number
            uniqueNum = uniqueNum | mask;
    }
    return uniqueNum;
}
// 5
vector<vector<int>> flipAndInvertImage(vector<vector<int>> &A)
{

    int n = A.size();
    int m = A[0].size();

    for (int i = 0; i < n; i++) // traverse each row
    {
        for (int j = 0; j < m / 2; j++) // for reversing each row and flipping the values
        {
            swap(A[i][j], A[i][m - j - 1]);
            A[i][j] ^= 1;
            A[i][m - j - 1] ^= 1;
        }
        if (m & 1) // for odd size row don't forget to flip bits
            A[i][m / 2] ^= 1;
    }
    return A;
}
