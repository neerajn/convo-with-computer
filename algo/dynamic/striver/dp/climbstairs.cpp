//
// Created by Neeraj Nandakumar on 17/01/2024.
//

#include <iostream>
#include <algorithm>
#include <vector>

typedef const unsigned long long c_ullong;
typedef unsigned long long ullong;

using namespace std;

// bottom up
int dp_opt_climbStairs(c_ullong n)
{
    int prev1 = 1;
    int prev2 = 1;

    for (int i = 2; i <= n; ++i) {
        int curri = prev1 + prev2;
        prev2 = prev1;
        prev1 = curri;
    }

    return prev1;
}

// top down - memoization
int dp_climbStairs(c_ullong n, vector<ullong>& cache)
{
    if (n <= 1) {
        cache[n] = 1;
    }
    if (cache[n] != -1) {
        return cache[n];
    }
    cache[n] = dp_climbStairs(n - 1, cache) + dp_climbStairs(n - 2, cache);
    return cache[n];
}

int recursive_climbStairs(c_ullong n)
{
    if (n <= 1) {
        return 1;
    }
    return recursive_climbStairs(n - 1) + recursive_climbStairs(n - 2);
}

int main(int argc, char** argv)
{
    cout << "Steps count: 3 ; recursive_climbStairs says "
        << recursive_climbStairs(3)
        << " ways." << endl;

    cout << "Steps count: 4 ; recursive_climbStairs says "
         << recursive_climbStairs(4)
         << " ways." << endl;

    vector<ullong> cache1(3 + 1, -1);
    cout << "Steps count: 3 ; dp_climbStairs says "
         << dp_climbStairs(3, cache1)
         << " ways." << endl;

    vector<ullong> cache2(4 + 1, -1);
    cout << "Steps count: 4 ; dp_climbStairs says "
         << dp_climbStairs(4, cache2)
         << " ways." << endl;

    cout << "Steps count: 3 ; dp_opt_climbStairs says "
         << dp_opt_climbStairs(3)
         << " ways." << endl;

    cout << "Steps count: 4 ; dp_opt_climbStairs says "
         << dp_opt_climbStairs(4)
         << " ways." << endl;


    return 0;
}