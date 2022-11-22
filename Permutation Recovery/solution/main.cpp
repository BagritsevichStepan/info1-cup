#include <iostream>
#include <cmath>
#include <unordered_map>

using namespace std;

const long long MOD = 9999999999999937LL;
const long long P = 10;
const int MAX_N = 7e4 + 5;

long long modSum(long long x, long long y) {
    return (x + y) % MOD;
}

long long modSubtraction(long long x, long long y) {
    return (x - y + MOD) % MOD;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    long long lastH = 0;
    long long diff[MAX_N];
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;

        long long h = 0;
        for (int j = 0; j < (int)s.size(); j++) {
            h = modSum(h * P, s[j] - '0');
        }

        diff[i] = modSubtraction(h, lastH);
        lastH = h;
    }

    const int len = (int)sqrt(n) + 1;
    long long hSum = 1;
    long long need[MAX_N];
    unordered_map<long long, int> st[MAX_N];

    for (int i = 0; i < n; i++) {
        need[i] = modSubtraction(hSum, diff[i]);
        st[i / len][need[i]] = i;

        hSum = modSum(hSum, diff[i]);
    }

    bool stat[MAX_N];
    long long push[MAX_N];
    int result[MAX_N];
    fill(stat, stat + MAX_N, true);
    fill(push, push + MAX_N, 0LL);
    fill(result, result + MAX_N, 0);

    const int maxSegmIndex = (n - 1) / len;
    for (int j = n; j > 0; j--) {
        int pos = 0;
        for (int index = maxSegmIndex; index >= 0; index--) {
            if (st[index].find(push[index]) != st[index].end()) {
                pos = st[index][push[index]];
                break;
            }
        }

        result[pos] = j;
        stat[pos] = false;

        const int segmIndex = pos / len;
        const int l = segmIndex * len;
        const int r = min(n, l + len);
        st[segmIndex].clear();

        for (int i = l; i < r; i++) {
            if (!stat[i]) {
                continue;
            }
            if (i > pos) {
                need[i] = modSubtraction(need[i], diff[pos]);
            }
            st[segmIndex][need[i]] = i;
        }

        for (int ind = segmIndex + 1; ind <= maxSegmIndex; ind++) {
            push[ind] = modSum(push[ind], diff[pos]);
        }
    }

    for (int i = 0; i < n; i++) {
        cout << result[i] << ' ';
    }
    return 0;
}
