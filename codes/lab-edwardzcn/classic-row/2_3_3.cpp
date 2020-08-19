#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

#define rep(i, a, n) for (int i = a; i < n; ++i)
#define per(i, a, n) for (int i = n - 1; i >= a; --i)

// 只是作者自己的框架，需要自行填充细节

int main()
{

    string raw_in;
    getline(cin, raw_in);
    string temp;

    rep(r, 3, 13)
    {
        if (__gcd(r, 513) == r)
            continue;
        cout << "r=" << r << ": ";
        string temp_raw = raw_in;
        string ans = raw_in;
        int cnt = 0;
        rep(i, 0, r)
        {
            // Your code
        }
        // if (ans.find("the") != -1)
        cout << ans << endl;
    }
}