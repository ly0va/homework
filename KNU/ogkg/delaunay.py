from __future__ import division

class Delaunay:

    def __init__(self):
        self.edges = set()

    def make_edge(self, start, end):
        fwd  = Edge(start, end)
        back = Edge(end, start)
        fwd.rev, back.rev = back, fwd
        fwd.next, fwd.prev = fwd, fwd
        back.next, back.prev = back, back
        self.edges.add(fwd)
        return fwd

    def connect(self, a, b):
        edge = self.make_edge(a.end, b.start)
        edge.splice(a.rev.prev)
        edge.rev.splice(b)
        return edge

    def delete_edge(self, edge):
        edge.splice(edge.prev)
        edge.rev.splice(edge.rev.prev)
        self.edges.discard(edge)
        self.edges.discard(edge.rev)

    def run(self, points):
        if len(points) < 2:
            return []

        points = sorted(set(points))

        self.triangulate(points)
        return [(edge.start, edge.end) for edge in self.edges]


    def triangulate(self, points):
        if len(points) == 2:
            edge = self.make_edge(points[0], points[1])
            return edge, edge.rev

        if len(points) == 3:
            p1, p2, p3 = points[0], points[1], points[2]
            a = self.make_edge(p1, p2)
            b = self.make_edge(p2, p3)
            a.rev.splice(b)

            if right_of(p3, a):
                self.connect(b, a)
                return a, b.rev
            elif left_of(p3, a):
                c = self.connect(b, a)
                return c.rev, c
            else:
                return a, b.rev

        middle = len(points) // 2
        left, right = points[:middle], points[middle:]
        left_outside, left_inside = self.triangulate(left)
        right_inside, right_outside = self.triangulate(right)

        while True:
            if right_of(right_inside.start, left_inside):
                left_inside = left_inside.rev.next
            elif left_of(left_inside.start, right_inside):
                right_inside = right_inside.rev.prev
            else:
                break

        base = self.connect(left_inside.rev, right_inside)

        if left_inside.start == left_outside.start:
            left_outside = base
        if right_inside.start == right_outside.start:
            right_outside = base.rev

        # Merge
        while True:

            right_candidate, left_candidate = base.rev.next, base.prev

            valid_right_candidate, valid_left_candidate = right_of(right_candidate.end, base), right_of(left_candidate.end, base)
            if not (valid_right_candidate or valid_left_candidate):
                break

            if valid_right_candidate:
                while right_of(right_candidate.next.end, base) and \
                      in_circle(base.end, base.start, right_candidate.end, right_candidate.next.end):
                    temp = right_candidate.next
                    self.delete_edge(right_candidate)
                    right_candidate = temp

            if valid_left_candidate:
                while right_of(left_candidate.prev.end, base) and \
                      in_circle(base.end, base.start, left_candidate.end, left_candidate.prev.end):
                    temp = left_candidate.prev
                    self.delete_edge(left_candidate)
                    left_candidate = temp

            if not valid_right_candidate or \
               (valid_left_candidate and in_circle(right_candidate.end, right_candidate.start, left_candidate.start, left_candidate.end)):
                base = self.connect(left_candidate, base.rev)
            else:
                base = self.connect(base.rev, right_candidate.rev)

        return left_outside, right_outside


# Quad Edge data structure.
class Edge:
    def __init__(self, start, end):
        self.start = start
        self.end   = end
        self.next  = None
        self.prev  = None
        self.rev   = None

    def splice(self, other):
        if self == other:
            return

        self.next.prev, other.next.prev = other, self
        self.next, other.next = other.next, self.next

def in_circle(a, b, c, d):
    a1, a2 = a[0]-d[0], a[1]-d[1]
    b1, b2 = b[0]-d[0], b[1]-d[1]
    c1, c2 = c[0]-d[0], c[1]-d[1]
    a3, b3, c3 = a1**2 + a2**2, b1**2 + b2**2, c1**2 + c2**2
    det = a1*b2*c3 + a2*b3*c1 + a3*b1*c2 - (a3*b2*c1 + a1*b3*c2 + a2*b1*c3)
    return det < 0


def right_of(p, edge):
    a, b = edge.start, edge.end
    det = (a[0]-p[0]) * (b[1]-p[1]) - (a[1]-p[1]) * (b[0]-p[0])
    return det > 0


def left_of(p, edge):
    a, b = edge.start, edge.end
    det = (a[0]-p[0]) * (b[1]-p[1]) - (a[1]-p[1]) * (b[0]-p[0])
    return det < 0

