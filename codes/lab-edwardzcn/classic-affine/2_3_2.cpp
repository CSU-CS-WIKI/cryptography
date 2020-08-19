#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

#define rep(i, a, n) for (int i = a; i < n; ++i)
#define per(i, a, n) for (int i = n - 1; i >= a; --i)
#define MOD 29

// 只有核心部分 需要你自行补充细节

void check_p(string input)
{
    pair<char, int> p[1000];
    rep(i, 0, 1000) p[i].second = 0, p[i].first = char(i);
    rep(i, 0, input.length())
    {
        if (islower(input[i]))
            p[input[i]].second++;
    }
    sort(p, p + 1000, cmp);
    rep(i, 0, 10) cout << "# " << p[i].first << "  # " << p[i].second << endl;
    cout << "a=" << 23 * qpod(4, MOD - 2, MOD) % MOD << endl;
}

char txt[] = "abcdefghijklmnopqrstuvwxyz .,";

int my_map(char c)
{
    if (islower(c))
        return c - 'a';
    else if (c == ' ')
        return 26;
    else if (c == '.')
        return 27;
    else if (c == ',')
        return 28;
}

static inline int inmap(char c)
{
    return islower(c) || c == '.' || c == ' ' || c == ',';
}

int main()
{
    // ios::sync_with_stdio(false);
    freopen("2_3_2_in.txt", "r", stdin);
    freopen("2_3_2_out.txt", "w", stdout);

    string raw_in;
    getline(cin, raw_in);
    check_p(raw_in);
    rep(A, 0, 29)
    {
        // cout << "A=" << A << endl;
        rep(B, 0, 29)
        {
            string ans = raw_in;
            rep(i, 0, ans.length())
            {
                if (inmap(ans[i]))
                    // Your code
            }
            if (ans.find("the") != -1)
                // Your code
        }
        // cout << endl;
    }

    // check_p(ans);
}