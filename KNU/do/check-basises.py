#!/usr/bin/python3

import itertools as it
from sympy import Matrix

#####  Problem parameters #####

A = Matrix([
    [2,  3, 1, 0,  0],
    [3, -5, 0, 1,  0],
    [5,  3, 0, 0, -1],
])

b = Matrix([19, 17, 17])

L = lambda x: -5*x[0] - x[1]

###############################

m, n = A.shape
allowed = []
pseudo = []

for i, j, k in it.combinations(range(n), m):
    Ai, Aj, Ak = A[:, i], A[:, j], A[:, k]
    B = Ai.row_join(Aj).row_join(Ak)
    x = [0] * n
    x[i], x[j], x[k] = B.solve(b)[:, 0]
    if any([x[i] < 0, x[j] < 0, x[k] < 0]):
        pseudo.append(x)
    else:
        allowed.append(x)

allowed.sort(key=L)

print("\nPseudo basis set:")
for basis in pseudo:
    print("x =", basis)

print("\nAllowed basis set (sorted):")
for basis in allowed:
    print("x =", basis, " L(x) =", L(basis))

print("\nx* =", allowed[0])
print("L* =", L(allowed[0]))
