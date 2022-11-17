#include <bits/stdc++.h>

using namespace std;

// -log2(0.01) = 6.643856189774724
// so, 7 hash functions are needed
const int M[] = { 
    1000000007,
    1000000009,
    1000000021,
    1000000033,
    1000000087,
    1000000093,
    1000000097
};
const int P = 100003;

struct BloomFilter {
    // vector<bool> is optimized to work with bits
    vector<bool> filter;

    static int hash(string s, int i) {
        long long h = 0;
        for (char c : s) {
            h = (h * P + c) % M[i];
        }
        return h;
    }

    BloomFilter(int size): filter(size) {}

    void add(string s) {
        for (int i = 0; i < 7; i++) {
            filter[hash(s, i) % filter.size()] = true;
        }
    }

    bool contains(string s) {
        for (int i = 0; i < 7; i++) {
            if (!filter[hash(s, i) % filter.size()]) {
                return false;
            }
        }
        return true;
    }
};

int main(int argc, char **argv) {
    ios_base::sync_with_stdio(false);
    
    // - 10**6 * log(0.01) / log(2)^2 = 9585058
    // so this is the number of bits needed (rounded up)
    const int N = 10000000;
    char op;
    string str;

    BloomFilter bloom(N);
    unordered_set<string> set;

    while (cin >> op) {
        if (op == '#') break;
        cin >> str;
        if (op == '+') {
            bloom.add(str);
            set.insert(str);
        } else if (op == '?') {
            cout << str << (bloom.contains(str) ? " YES " : " NO ");
            if (bloom.contains(str) != (set.find(str) != set.end())) {
                cout << "(WRONG)";
            }
            cout << '\n';
        } else {
            cout << "Invalid operation: " << op << '\n';
        }
    }
    return 0;
}

