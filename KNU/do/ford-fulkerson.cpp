#include <bits/stdc++.h>

using namespace std;
const int INF = 1000000007;
const int N = 100;

vector<int> graph[N];
bool used[N];
int flows[N][N], V, parent[N];

bool bfs() {
    queue<int> Q;
    Q.push(0);
    while (!Q.empty() && Q.back() != V-1) {
        int u = Q.front(); Q.pop();
        for (int v: graph[u]) {
            if (!used[v] && flows[u][v] > 0) {
                Q.push(v);
                used[v] = true;
                parent[v] = u;
                if (v == V-1) break;
            }
        }
    }
    return !Q.empty();
}

int main() {
    int E, u, v, f;
    cin >> V >> E;
    while (E--) {
        cin >> u >> v >> f;
        u--, v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
        flows[u][v] = flows[v][u] = f;
    }

    int ans = 0;

    while (bfs()) {
        f = INF;
        for (int u = V-1; u != 0; u = parent[u]) {
            f = min(f, flows[parent[u]][u]);
        }
        for (int u = V-1; u != 0; u = parent[u]) {
            flows[parent[u]][u] -= f;
            flows[u][parent[u]] += f;
        }
        ans += f;
        fill(used, used+N, false);
    }

    cout << ans << '\n';

    return 0;
}

/* Task 5.3.3.9

10 18
1 2 15
1 3 3
1 4 4
1 6 24
1 8 17
2 3 1
2 4 20
3 4 13
4 6 17
5 7 4
5 9 9
5 10 15
6 7 20
6 8 11
7 8 3
7 9 7
8 9 2
9 10 18

*/
