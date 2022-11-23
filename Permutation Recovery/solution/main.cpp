#include <iostream>
#include <cmath>
#include <unordered_map>

using namespace std;

const long long mod = 9999999999999937LL;
const long long p = 10;
const int maxN = 7e4 + 5;

long long ModSum(const long long x, const long long y) {
    return (x + y) % mod;
}

long long ModSubtraction(const long long x, const long long y) {
    return (x - y + mod) % mod;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    long long last_h = 0;
    long long diff[maxN];
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;

        long long h = 0;
        for (int j = 0; j < s.size(); j++) {
            h = ModSum(h * p, s[j] - '0');
        }

        diff[i] = ModSubtraction(h, last_h);
        last_h = h;
    }

    const int length = (int)sqrt(n) + 1;
    long long h_sum = 1;
    long long need[maxN];
    unordered_map<long long, int> st[maxN];

    for (int i = 0; i < n; i++) {
        need[i] = ModSubtraction(h_sum, diff[i]);
        st[i / length][need[i]] = i;

        h_sum = ModSum(h_sum, diff[i]);
    }

    bool stat[maxN];
    long long push[maxN];
    int result[maxN];
    fill(stat, stat + maxN, true);
    fill(push, push + maxN, 0LL);
    fill(result, result + maxN, 0);

    const int maxSegmIndex = (n - 1) / length;
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

        const int segmIndex = pos / length;
        const int l = segmIndex * length;
        const int r = min(n, l + length);
        st[segmIndex].clear();

        for (int i = l; i < r; i++) {
            if (!stat[i]) {
                continue;
            }
            if (i > pos) {
                need[i] = ModSubtraction(need[i], diff[pos]);
            }
            st[segmIndex][need[i]] = i;
        }

        for (int index = segmIndex + 1; index <= maxSegmIndex; index++) {
            push[index] = ModSum(push[index], diff[pos]);
        }
    }

    for (int i = 0; i < n; i++) {
        cout << result[i] << ' ';
    }
    return 0;
}
