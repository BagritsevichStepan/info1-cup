#include <iostream>

using namespace std;

const int maxN = 1e6 + 5;

pair<int, int> sortArray[2][maxN];
pair<int, int> x[maxN];
int a[maxN];

bool GetBit(const int x, const int k) {
    return x & (1 << k);
}

void Sort(const int bit, const int n) {
    for (int i = 0; i < n; i++) {
        if (GetBit(a[x[i].second], bit)) {
            x[i].first |= 1 << bit;
        }
    }

    int size[] = {0, 0};
    for (int i = 0; i < n; i++) {
        int index = GetBit(x[i].first, bit);
        sortArray[index][size[index]++] = x[i];
    }

    int index = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < size[i]; j++) {
            x[index++] = sortArray[i][j];
        }
    }
}

void UpdateP(int& p, const int i, const int value) {
    p = max(p, i);
    while (i < p && x[i].first + x[p - 1].first >= value) {
        p--;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        x[i].second = i;
    }

    int result = 0;
    for (int bit = 0; bit < 30; bit++) {
        Sort(bit, n);

        int p1 = n;
        int p2 = n;
        int p3 = n;
        const int value = 1 << bit;

        for (int i = 0; i < n; i++) {
            UpdateP(p1, i, value);
            UpdateP(p2, i, 2 * value);
            UpdateP(p3, i, 3 * value);
            if ((p2 - p1 + n - p3) % 2) {
                result ^= value;
            }
        }
    }

    cout << result << '\n';
    return 0;
}