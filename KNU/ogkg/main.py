
import numpy as np
import matplotlib.pyplot as plt

def plot_lines(points, tree, edges):
    plt.axis('equal')
    plt.ylim((-5, 105))
    plt.xlim((-5, 105))

    data = []

    for line in set(edges) - set(tree):
        data.append((line[0][0], line[1][0]))
        data.append((line[0][1], line[1][1]))
        data.append('y:')

    for line in tree:
        data.append((line[0][0], line[1][0]))
        data.append((line[0][1], line[1][1]))
        data.append('black')

    plt.plot(*data)

    for x, y in points:
        plt.plot(x, y, marker="o", markersize=4, color="black")

    plt.show()


def gen_random(n):
    points_x = np.random.randint(0, 100, n, dtype=np.int64)
    points_y = np.random.randint(0, 100, n, dtype=np.int64)
    return [*zip(points_x, points_y)]

def gen_grid(n):
    points_x = np.linspace(0, 100, n+1)
    points_y = np.linspace(0, 100, n+1)
    return [(i, j) for i in points_x for j in points_y]

def gen_circle(n):
    rads = np.linspace(0, 2*np.pi, n+1, dtype=np.float64)
    cx = cy = r = 50
    return [(int(cx + r * np.cos(i)), int(cy + r * np.sin(i))) for i in rads][:-1]

from delaunay import Delaunay
from kruskal import Kruskal
points = gen_random(500)
edges = Delaunay().run(points)
tree = Kruskal().run(edges)
plot_lines(points, tree, edges)

