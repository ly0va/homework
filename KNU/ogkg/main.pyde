from delaunay import Delaunay
from kruskal import Kruskal

class Graph:
    def __init__(self):
        self.points = []
        self.triangulation = []
        self.spanning_tree = []

    def execute(self):
        self.triangulation = Delaunay().run(self.points[:])
        self.spanning_tree = Kruskal().run(self.triangulation[:])

    def render(self):
        stroke(230, 230, 0)
        for a, b in self.triangulation:
            line(a[0], a[1], b[0], b[1])

        stroke(0)
        for a, b in self.spanning_tree:
            line(a[0], a[1], b[0], b[1])

        for point in self.points:
            circle(point[0], point[1], 5)

    def reset(self):
        self.points = []
        self.triangulation = []
        self.spanning_tree = []
            
graph = Graph()

def setup():
    size(800, 800)
    stroke(0)
    fill(0)

def draw():
    background(255)
    graph.render()

def mousePressed():
    point = (long(mouseX), long(mouseY))
    graph.points.append(point)

def keyPressed():
    if key == '\n':
        graph.execute()
    elif key == ' ':
        graph.reset()
