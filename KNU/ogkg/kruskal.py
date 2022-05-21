class Kruskal:

    def __init__(self):
        self.parent = {}

    def find_root(self, v):
        if v not in self.parent:
            return v
        self.parent[v] = self.find_root(self.parent[v])
        return self.parent[v]

    def unite(self, u, v):
        u, v = self.find_root(u), self.find_root(v)
        if u != v:
            self.parent[u] = v

    def same_set(self, u, v):
        return self.find_root(u) == self.find_root(v)

    def run(self, edges):
        edges.sort(key = lambda e: (e[0][0] - e[1][0])**2 + (e[0][1] - e[1][1])**2)

        spanning_tree = []

        for edge in edges:
            u, v = edge[0], edge[1]
            if not self.same_set(u, v):
                spanning_tree.append(edge)
                self.unite(u, v)

        return spanning_tree



