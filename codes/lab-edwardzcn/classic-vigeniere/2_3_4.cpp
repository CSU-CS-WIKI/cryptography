//破解维吉尼亚密码  找到密钥

// 只是作者自己的框架 需要自行填充细节

// 看不懂框架建议自己写噢
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

#define rep(i, a, n) for (int i = a; i < n; ++i)
#define per(i, a, n) for (int i = n - 1; i >= a; --i)
#define all(x) x.begin(), x.end()
#define ANS_LEN key_len

double icattack(string a)
{

    int tempcnt[100];
    double tempsum = 0;
    int allsum = 0;
    memset(tempcnt, 0, sizeof(tempcnt));
    // Your code

    return tempsum;
}

int main()
{
    // ios::sync_with_stdio(false);
    freopen("2_3_4_in.txt", "r", stdin);
    freopen("2_3_4_out.txt", "w", stdout);

    string raw_in;
    getline(cin, raw_in);
    string temp;

    stringstream ss(raw_in);

    map<string, int> my_map;

    int key_len = 0;
    double max_ic = -1;

    cout << raw_in << endl;

    rep(i, 1, 12)
    {
        string cipher_divide[100];
        int temp_key_len = i;
        rep(j, 0, raw_in.length())
        {
            if (!isalpha(raw_in[j]))
                continue;
            if (isupper(raw_in[j])) {
                // Your code
            } else {
                // Your code
            }
        }
        double temp_sum = 0;
        rep(j, 0, i)
        {
            // Your code.
        }
        temp_sum /= i;
        cout << temp_sum << endl;
        // Your code
        //对一个密文分组进行重合指数攻击
    }
    // key_len = 7;
    cout << "key_len = " << key_len << endl;

    int freque[100][100];
    int de_ans[100];

    rep(i, 0, raw_in.length())
    {
        if (!isalpha(raw_in[i]))
            continue;
        if (isupper(raw_in[i])) {
            // Your code
        } else {
            // Your code
        }
    }

    rep(i, 0, key_len)
    {
        int maxnum = -1;
        rep(j, 0, 26)
        {
            if (freque[i][j] > maxnum) {
                maxnum = freque[i][j];
                de_ans[i] = 'e' - 'a' - j;
            }
        }
    }
    //手动修改
    // Your code

    rep(i, 0, raw_in.length())
    {
        if (!isalpha(raw_in[i])) {
            cout << raw_in[i];
        } else if (isupper(raw_in[i])) {
            cout << char('A' + (raw_in[i] - 'A' + de_ans[i % key_len] + 26) % 26);
        } else
            cout << char('a' + (raw_in[i] - 'a' + de_ans[i % key_len] + 26) % 26);
    }
    cout << endl;

    rep(i, 0, key_len)
    {
        cout << char('a' + (26 - de_ans[i]) % 26);
    }
}