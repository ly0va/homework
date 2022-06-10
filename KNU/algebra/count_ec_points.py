#!/usr/bin/python3

from math import inf
from collections import defaultdict

# y^2 = x^3 + Ax + B over Fq
def count(A, B, q):
    points = [(inf, inf)]
    squares = defaultdict(list)

    for y in range(q):
        squares[y*y % q].append(y)

    for x in range(q):
        rhs = (x**3 + A*x + B) % q
        points.extend((x, y) for y in squares[rhs])

    return points

