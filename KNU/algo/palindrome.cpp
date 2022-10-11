#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
#define die(x) {cout << (x); exit(0);}
#define files(x) freopen(#x".in", "r", stdin); \
                 freopen(#x".out", "w", stdout)
 
using namespace std;
typedef long long lint;
typedef pair<int, int> pii;
const lint inf = 1000000007;
const int total = 2000001;
 
int forw[total], bck[total], powers[total];
int n;
 
bool pal(int i, int j) {
    lint h1 = (forw[j] - forw[i-1] + inf) % inf;
    lint h2 = (bck[n+1-i] - bck[n-j] + inf) % inf;
    h1 = h1 * powers[total - j] % inf;
    h2 = h2 * powers[total - (n+1-i)] % inf;
    return h1 == h2;
}
 
string s;

int check_palindrome(int center, int shift = 0) {
    int r = min(center-1, n - center + shift);
    int l = 0;
    while (r - l > 1) {
        int m = (r + l) / 2;
        if (pal(center - m, center + m - shift)) {
            l = m;
        } else {
            r = m;
        }
    }
    return pal(center-r, center+r-shift) ? r : l;
}

void print_palindromes() {
    for (int i = 1; i <= n; i++) {
        int r = check_palindrome(i, 0);
        if (r > 0) {
            cout << s.substr(i - 1 - r, 2 * r + 1) << endl;
        }
        r = check_palindrome(i, 1);
        if (r > 0) {
            cout << s.substr(i - 1 - r, 2 * r) << endl;
        }
    }
}
 
int main() {
 
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
 
    cin >> s;
 
    n = s.size();
 
    powers[0] = 1;
    for (int i = 1; i < total; i++)
        powers[i] = (lint)powers[i-1]*37 % inf;
 
    forw[0] = bck[0] = 0;
    for (int i = 0; i < n; i++) {
        forw[i+1] = ((lint)s[i]*powers[i] + forw[i]) % inf;
        bck[i+1] = ((lint)s[n-i-1]*powers[i] + bck[i]) % inf;
    }
 
    print_palindromes();
 
    return 0;
}
