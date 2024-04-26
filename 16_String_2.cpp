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
2. Valid Anagram
    https://leetcode.com/problems/valid-anagram/
3. Group Anagrams
    https://leetcode.com/problems/group-anagrams/
*/

// 2 Valid Anagram
class ValidAnagram
{
public:
    bool isAnagram(string s, string t)
    {
        unordered_map<int, int> count;
        // count first string characters
        for (auto c : s)
        {
            if (count.find(c) == count.end())
                count[c] = 0;
            count[c]++;
        }
        // remove second string characters from hash
        for (auto c : t)
        {
            if (count.find(c) == count.end())
                return false;
            count[c]--;
        }
        // if count is not zero for any of the characters they are not anagram
        for (auto p : count)
            if (p.second != 0)
                return false;
        return true;
    }
};

// 3. Group Anagrams
class GroupAnagrams
{
public:
    vector<vector<string>> groupAnagrams(vector<string> &strs)
    {
        // the string which are anagrams would be same after sorting, we will group anagram and use sorted string as key
        unordered_map<string, vector<string>> um;
        for (auto s : strs)
        {
            string orig = s;
            sort(s.begin(), s.end());
            // s will be the key
            if (um.find(s) == um.end())
                um[s] = {};
            um[s].push_back(orig);
        }

        vector<vector<string>> ans;
        for (auto p : um)
            ans.push_back(p.second);
        return ans;
    }
};

//