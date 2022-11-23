#include <iostream>
#include <vector>

using namespace std;

const int inf = 1e8;
const int maxN = 2e5 + 5;

vector<int> result;
int dp[maxN][3];
int from[maxN][3];

void UpdateDp(int &value_to_update, int &from, const int i, const int flag, const int value) {
    const int newValue = dp[i][flag] + value;
    if (newValue < value_to_update) {
        value_to_update = newValue;
        from = flag;
    }
}

void UpdateResult(const int l, const int r, int count) {
    const int length = r - l + 1;
    if (l > r || length < 3) {
        return;
    }

    int i = l + 1;
    count = (length - count) / 2;
    while (count-- && i < r) {
        result.push_back(i);
        i += 2;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;

    int a[maxN];
    int count[maxN];

    while (t--) {
        int n, q;
        cin >> n >> q;

        a[q + 1] = n + 1;
        for (int i = 1; i <= q; i++) {
            cin >> a[i];
        }

        for (int i = 0; i <= q + 1; i++) {
            for (int flag = 0; flag < 3; flag++) {
                dp[i][flag] = inf;
                from[i][flag] = -1;
            }
        }

        dp[0][0] = 0;
        for (int i = 0; i <= q; i++) {
            const int length = a[i + 1] - (a[i] + 1);
            for (int flag = 0; flag < 3; flag++) {
                if (flag >= length) {
                    if (flag == length) {
                        UpdateDp(dp[i + 1][0], from[i + 1][0], i, flag, 0);
                    }
                    continue;
                }

                const int operCount = (length - flag) / 2;
                if ((length - flag) % 2) {
                    UpdateDp(dp[i + 1][1], from[i + 1][1], i, flag, operCount + 1);
                } else {
                    UpdateDp(dp[i + 1][2], from[i + 1][2], i, flag, operCount + 1);
                    if (flag) {
                        UpdateDp(dp[i + 1][0], from[i + 1][0], i, flag, operCount);
                    }
                }
            }
        }

        if (dp[q + 1][0] == inf) {
            cout << "-1\n";
            continue;
        }

        count[q + 1] = 0;
        int index = from[q + 1][0];
        for (int i = q; i >= 0; i--) {
            count[i] = index;
            index = from[i][index];
        }

        for (int i = 0; i <= q; i++) {
            UpdateResult(a[i] + 1, a[i + 1] - 1, count[i] + count[i + 1]);
        }

        for (int i = 1; i <= q; i++) {
            for (int j = 0; j < count[i]; j++) {
                result.push_back(a[i]);
            }
        }

        cout << result.size() << '\n';
        for (int i = 0; i < result.size(); i++) {
            cout << result[i] << ' ';
        }
        cout << '\n';

        result.clear();
    }
    return 0;
}
