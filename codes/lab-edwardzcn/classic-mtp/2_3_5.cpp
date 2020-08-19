// MTP 是本人修改过的题面
// 这里的文件都是草稿 如若不能理解请从题面出发自行解决

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

#define rep(i, a, n) for (int i = a; i < n; ++i)
#define per(i, a, n) for (int i = n - 1; i >= a; --i)
#define N 10

vector<int> change_raw_to_int(string raw_in)
{
    vector<int> temp_ans;
    for (int i = 0; i < raw_in.length(); i += 2) {
        int ah = isalpha(raw_in[i]) ? raw_in[i] - 'a' + 10 : raw_in[i] - '0';
        int al = isalpha(raw_in[i + 1]) ? raw_in[i + 1] - 'a' + 10 : raw_in[i + 1] - '0';
        temp_ans.push_back((ah << 4) + al);
    }
    // rep(i, 0, temp_ans.size()) cout << " " << temp_ans[i];
    // cout << endl;
    return temp_ans;
}

int main()
{
    // ios::sync_with_stdio(false);
    freopen("2_3_5_in2.txt", "r", stdin);
    freopen("2_3_5_out.txt", "w", stdout);

    vector<string> raw_in;

    vector<int> ciphertext[N];
    vector<int> plaintext_xor[N][N];
    vector<int> conflict_index;
    int key[10000];
    memset(key, 0, sizeof(key));

    rep(i, 0, N)
    {
        string temp;
        getline(cin, temp);
        raw_in.push_back(temp);
        ciphertext[i] = change_raw_to_int(raw_in[i]);
        //cipher 里存的是转化以后的每个字符的值
    }

    rep(i, 0, N)
    {
        int cnt_value[1000];
        memset(cnt_value, 0, sizeof(cnt_value));

        rep(j, 0, N)
        {
            if (j == i)
                continue;

            rep(kk, 0, ciphertext[1].size())
            {
                plaintext_xor[i][j].push_back(ciphertext[i][kk] ^ ciphertext[j][kk]);
                if (isalpha(ciphertext[i][kk] ^ ciphertext[j][kk])) {
                    cnt_value[kk]++;
                }
            }
        }

        rep(j, 0, ciphertext[1].size())
        {
            if (cnt_value[j] >= 7 && isprint(32 ^ ciphertext[i][j])) {
                if (key[j] != 0) {
                    if (key[j] != (32 ^ ciphertext[i][j])) {
                        conflict_index.push_back(j);
                        key[j] = (32 ^ ciphertext[i][j]);
                    }
                } else
                    key[j] = (32 ^ ciphertext[i][j]);
            }
        }
    }

    //人工校对补充
    // key[1] = 'xxxx' ^ xxx;
    key[1] = 'e' ^ (5 * 16 + 11);
    key[3] = 'r' ^ 81;
    key[10] = 't' ^ 24;
    key[15] = 'i' ^ (2 * 16 + 13);
    key[16] = 'e' ^ 2;
    key[20] = 'o' ^ (3 * 16 + 4);
    key[21] = 'n' ^ (5 * 16 + 7);
    key[22] = 'u' ^ (3 * 16 + 13);
    key[24] = 'd' ^ (4 * 16 + 9);
    key[27] = ' ' ^ (7 * 16 + 9);
    // key[28] = '(';
    // key[29] = 'X';
    key[30] = 'w' ^ 21;
    // key[31] = 'W';
    // key[32] = '<';
    key[33] = '%';
    key[35] = 32 ^ 2;
    key[40] = 'o' ^ (3 * 16 + 4);
    key[42] = 'd' ^ (2 * 16 + 14);
    key[44] = 'f' ^ (3 * 16 + 5);
    key[49] = 'a' ^ (3 * 16 + 15);
    //

    rep(i, 0, ciphertext[1].size())
    {
        if (!key[i])
            cout << "?";
        else
            cout << char(key[i]);
    }
    cout << endl;
    sort(conflict_index.begin(), conflict_index.end());
    cout << "conflict:";
    rep(i, 0, conflict_index.size()) cout << conflict_index[i] << " ";
    cout << endl;

    cout << "plain text" << endl;

    rep(i, 0, N)
    {
        rep(kk, 0, ciphertext[i].size())
        {
            if (key[kk] == 0)
                cout << "?";
            else
                cout << char(key[kk] ^ ciphertext[i][kk]);
        }
        cout << endl;
    }
}