#include <iostream>

using namespace std;

const int MAX_N = 1e6 + 5;
pair<int, int> sortArray[2][MAX_N];
pair<int, int> x[MAX_N];
int a[MAX_N];

bool getBit(const int x, const int k) {
    return x & (1 << k);
}

void sort(const int bit, const int n) {
    for (int i = 0; i < n; i++) {
        if (getBit(a[x[i].second], bit)) {
            x[i].first |= 1 << bit;
        }
    }

    int size[] = {0, 0};
    for (int i = 0; i < n; i++) {
        int index = getBit(x[i].first, bit);
        sortArray[index][size[index]++] = x[i];
    }

    int index = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < size[i]; j++) {
            x[index++] = sortArray[i][j];
        }
    }
}

void updateP(int& p, const int i, const int value) {
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
        sort(bit, n);

        int p1 = n;
        int p2 = n;
        int p3 = n;
        const int value = 1 << bit;

        for (int i = 0; i < n; i++) {
            updateP(p1, i, value);
            updateP(p2, i, 2 * value);
            updateP(p3, i, 3 * value);
            if ((p2 - p1 + n - p3) % 2) {
                result ^= value;
            }
        }
    }

    cout << result << '\n';
    return 0;
}