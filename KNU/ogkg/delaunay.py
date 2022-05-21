"""

The divide-and-conquer algorithm for computing Delaunay triangulation of a set of points.

"""

import numpy as np

class Delaunay:
    
    def __init__(self):
        self.edges = set()

    def make_edge(self, start, end):
        """Creates a new edge. Assumes start and end are points."""
        fwd  = Edge(start, end)
        back = Edge(end, start)
        fwd.rev, back.rev = back, fwd
        fwd.next, fwd.prev = fwd, fwd
        back.next, back.prev = back, back
        self.edges.add(fwd)
        return fwd


    def connect(self, a, b):
        """Adds a new edge e connecting the destination of a to the origin of b, in such a way that
        a Left = e Left = b Left after the connection is complete."""
        edge = self.make_edge(a.end, b.start)
        edge.splice(a.rev.prev)
        edge.rev.splice(b)
        return edge


    def delete_edge(self, edge):
        """Disconnects the edge e from the rest of the structure (this may cause the rest of the
        structure to fall apart in two separate components)."""
        edge.splice(edge.prev)
        edge.rev.splice(edge.rev.prev)
        self.edges.discard(edge)
        self.edges.discard(edge.rev)


    def run(self, points):
        """Assumes points is a list of points of form (x, y).
        Returns a list of edges that form a Delaunay triangulation of points."""

        if len(points) < 2:
            return set()
        
        points = np.array(points)
        dtype = points.dtype
        
        # Sort points by x coordinate, y is a tiebreaker.
        points.view(dtype=[('x', dtype), ('y', dtype)]).sort(order=['x', 'y'], axis=0)
        
        # Remove duplicates.
        points = np.unique(points, axis=0)

        self.triangulate(points)
        return [(tuple(edge.start), tuple(edge.end)) for edge in self.edges]


    def triangulate(self, points):
        """Computes the Delaunay triangulation of a point set points and returns two edges, le and re,
        which are the counterclockwise convex hull edge out of the leftmost vertex and the clockwise
        convex hull edge out of the rightmost vertex, respectively."""

        if len(points) == 2:
            edge = self.make_edge(points[0], points[1])
            return edge, edge.rev

        elif len(points) == 3:
            # Create edges a connecting p1 to p2 and b connecting p2 to p3.
            p1, p2, p3 = points[0], points[1], points[2]
            a = self.make_edge(p1, p2)
            b = self.make_edge(p2, p3)
            a.rev.splice(b)

            # Close the triangle.
            if right_of(p3, a):
                self.connect(b, a)
                return a, b.rev
            elif left_of(p3, a):
                c = self.connect(b, a)
                return c.rev, c
            else:  # the three points are collinear
                return a, b.rev

        else:
            # Recursively subdivide points.
            middle = (len(points) + 1) // 2
            left, right = points[:middle], points[middle:]
            left_outside, left_inside = self.triangulate(left)
            right_inside, right_outside = self.triangulate(right)

            # Compute the upper common tangent of L and R.
            while True:
                if right_of(right_inside.start, left_inside):
                    left_inside = left_inside.rev.next
                elif left_of(left_inside.start, right_inside):
                    right_inside = right_inside.rev.prev
                else:
                    break

            # Create a first cross edge base from rdi.start to ldi.start.
            base = self.connect(left_inside.rev, right_inside)

            # Adjust ldo and rdo
            if left_inside.start[0] == left_outside.start[0] and left_inside.start[1] == left_outside.start[1]:
                left_outside = base
            if right_inside.start[0] == right_outside.start[0] and right_inside.start[1] == right_outside.start[1]:
                right_outside = base.rev

            # Merge.
            while True:
                # Locate the first R and L points to be encountered by the diving bubble.
                right_candidate, left_candidate = base.rev.next, base.prev
                # If both lcand and rcand are invalid, then base is the lower common tangent.
                valid_right_candidate, valid_left_candidate = right_of(right_candidate.end, base), right_of(left_candidate.end, base)
                if not (valid_right_candidate or valid_left_candidate):
                    break
                # Delete R edges out of base.end that fail the circle test.
                if valid_right_candidate:
                    while right_of(right_candidate.next.end, base) and \
                          in_circle(base.end, base.start, right_candidate.end, right_candidate.next.end):
                        t = right_candidate.next
                        self.delete_edge(right_candidate)
                        right_candidate = t
                # Symmetrically, delete L edges.
                if valid_left_candidate:
                    while right_of(left_candidate.prev.end, base) and \
                          in_circle(base.end, base.start, left_candidate.end, left_candidate.prev.end):
                        t = left_candidate.prev
                        self.delete_edge(left_candidate)
                        left_candidate = t
                # The next cross edge is to be connected to either lcand.end or rcand.end.
                # If both are valid, then choose the appropriate one using the in_circle test.
                if not valid_right_candidate or \
                   (valid_left_candidate and in_circle(right_candidate.end, right_candidate.start, left_candidate.start, left_candidate.end)):
                    # Add cross edge base from rcand.end to base.end.
                    base = self.connect(left_candidate, base.rev)
                else:
                    # Add cross edge base from base.start to lcand.end
                    base = self.connect(base.rev, right_candidate.rev)

            return left_outside, right_outside


# Quad edge data structure.
class Edge:
    """A directed edge: start -> end.
    When traversing edge ring: Next is CCW, Prev is CW."""

    def __init__(self, start, end):
        self.start = start
        self.end   = end
        self.next  = None
        self.prev  = None
        self.rev   = None

    def splice(self, other):
        """Combines distinct edge rings / breaks the same ring in two pieces. Merging / tearing goes
        between a and a.next through a.start to between b and b.next."""

        if self == other:
            print("Splicing edge with itself, ignored: {}.".format(self))
            return

        self.next.prev, other.next.prev = other, self
        self.next, other.next = other.next, self.next


def in_circle(a, b, c, d):
    """Does d lie inside of circumcircle abc?"""
    a1, a2 = a[0]-d[0], a[1]-d[1]
    b1, b2 = b[0]-d[0], b[1]-d[1]
    c1, c2 = c[0]-d[0], c[1]-d[1]
    a3, b3, c3 = a1**2 + a2**2, b1**2 + b2**2, c1**2 + c2**2
    det = a1*b2*c3 + a2*b3*c1 + a3*b1*c2 - (a3*b2*c1 + a1*b3*c2 + a2*b1*c3)
    return det < 0


def right_of(p, edge):
    """Does point p lie to the right of the line of edge e?"""
    a, b = edge.start, edge.end
    det = (a[0]-p[0]) * (b[1]-p[1]) - (a[1]-p[1]) * (b[0]-p[0])
    return det > 0


def left_of(p, edge):
    """Does point p lie to the left of the line of edge e?"""
    a, b = edge.start, edge.end
    det = (a[0]-p[0]) * (b[1]-p[1]) - (a[1]-p[1]) * (b[0]-p[0])
    return det < 0

