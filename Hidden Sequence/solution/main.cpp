#include <iostream>
#include <vector>
#include "grader.h"

using namespace std;

vector<int> findSequence(const int n) {
    const int maxLength = n / 2 + 1;
    int number = 1;
    vector<int> sequence;
    while (sequence.size() <= maxLength && isSubsequence(sequence)) {
        sequence.push_back(number);
    }
    sequence.pop_back();

    if (sequence.size() == maxLength) {
        number ^= 1;

        sequence.clear();
        while (isSubsequence(sequence)) {
            sequence.push_back(number);
        }
        sequence.pop_back();
    }

    const int countNumbers = (int)sequence.size();
    vector<int> result(n, number ^ 1);

    for (int i = 0; i < countNumbers; i++) {
        while (sequence.size() <= maxLength && isSubsequence(sequence)) {
            sequence.insert(sequence.begin(), number ^ 1);
        }
        sequence.erase(sequence.begin());

        vector<int> reversed_sequence(i + 1, number);
        while (reversed_sequence.size() <= maxLength && isSubsequence(reversed_sequence)) {
            reversed_sequence.push_back(number ^ 1);
        }
        reversed_sequence.pop_back();

        int index = (int)sequence.size() - (countNumbers - i);
        if (reversed_sequence.size() < maxLength) {
            index = n - countNumbers - (reversed_sequence.size() - (i + 1));
        }
        result[index + i] = number;
        sequence.pop_back();
    }

    return result;
}