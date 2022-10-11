#include <bits/stdc++.h>
 
std::vector<int> zfunc(std::string s) {
    int n = s.size();
    std::vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i <= r)
            z[i] = std::min(z[i-l], r-i+1);
        while (i + z[i] < n && s[i+z[i]] == s[z[i]])
            z[i]++;
        if (i + z[i] > r+1) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}
