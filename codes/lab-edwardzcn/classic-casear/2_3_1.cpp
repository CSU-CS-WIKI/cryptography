#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

#define rep(i, a, n) for (int i = a; i < n; ++i)
#define per(i, a, n) for (int i = n - 1; i >= a; --i)

// 只是作者自己的框架，仅供思考，需要自行填充细节

int main()
{
    // ios::sync_with_stdio(false);

    string raw_in;
    getline(cin, raw_in);
    string temp;
    rep(i, 1, 26)
    {
        cout << "#" << endl;
        temp = raw_in;

        rep(j, 0, temp.length())
        {
            // cout << temp[j];
            if (temp[j] >= 'A' && temp[j] <= 'Z') {
                // Your code here

            } else if (temp[j] >= 'a' && temp[j] <= 'z') {
                // Your code here
            }
            // cout << temp[j] << endl;
        }
        cout << temp << endl;
    }
}