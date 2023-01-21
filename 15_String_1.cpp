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
1.
2.
3.
*/

/*
String matching
    url: https://www.spoj.com/problems/NAJPF/
    url: https://leetcode.com/problems/implement-strstr/
0. BF
1. Rabin Karp
*/
// 0. BF(T:n*m)
vector<int> bf_string_matching(string t, string p)
{
    vector<int> indexes;
    int n = t.size();
    int m = p.size();
    for (int i = 0; i + m <= n; i++)
    {
        if (t.substr(i, m) == p)
            indexes.push_back(i);
    }
    return indexes;
}
// 1. RK(rolling hash)
class RobinKarp
{
    ll prime = 31;
    ll mod = 1e9 + 7;
    ll prime_inv;
    vector<ll> power_prime;
    string text;
    string pattern;
    ll poly_hash(string s)
    {
        ll hash = 0;
        for (int i = 0; i < s.size(); i++)
        {
            hash += (s[i] - 'a' + 1) * power_prime[i]; // a->1 not 0 because if a is 0. poly hash of aaaa,aaaaaa,a,aa all will be 0
            hash %= mod;
        }
        return hash;
    }
    ll fast_pow(ll a, ll b)
    {
        if (b == 0)
            return 1;

        ll ans = fast_pow(a, b / 2);
        ans = ans * ans;
        ans %= mod;
        if (b & 1)
            ans = (ans * a) % mod;
        return ans;
    }

public:
    RobinKarp(string t, string pat)
    {
        text = t;
        pattern = pat;
        // precompute so that we can use it during rolling hash calculation
        prime_inv = fast_pow(prime, mod - 2);
        vector<ll> prime_pow(pattern.size(), 0);

        ll p = 1;
        for (int i = 0; i < pattern.size(); i++)
        {
            prime_pow[i] = p;
            p = p * prime;
            p %= mod;
        }
        power_prime = prime_pow;
    }

    vector<int> matched_indexes()
    {
        int n = text.size();
        int m = pattern.size();
        if (m > n)
            return {};

        vector<int> indexes;
        ll pattern_hash = poly_hash(pattern);
        ll curr_hash = poly_hash(text.substr(0, m));
        if (curr_hash == pattern_hash)
            indexes.push_back(0);
        for (int i = 1; i + m <= n; i++)
        {
            curr_hash = (curr_hash - (text[i - 1] - 'a' + 1) + mod) % mod;
            curr_hash = (curr_hash * prime_inv) % mod;
            curr_hash = (curr_hash + ((text[i + m - 1] - 'a' + 1) * power_prime[m - 1]) % mod) % mod;

            if (curr_hash == pattern_hash)
                indexes.push_back(i);
        }
        return indexes;
    }
};
