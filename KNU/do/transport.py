#!/usr/bin/python3

import numpy as np

# problem parameters
a = np.array([30, 50, 20], dtype=int)
b = np.array([15, 15, 40, 30], dtype=int)
c = np.array([
    [1, 8, 2, 3],
    [4, 7, 5, 1],
    [5, 3, 4, 4]
], dtype=int)
N, M = c.shape

# solution matrix
x = np.zeros((N, M), dtype=int)

# North-West corner method
i = j = 0
basis = []
while i < N and j < M:
    basis.append((i, j))
    m = min(a[i], b[j])
    a[i] -= m
    b[j] -= m
    x[i, j] = m
    if a[i] < b[j]:
        i += 1
    else:
        j += 1


while True:
    u = [None] * N
    v = [None] * M
    u[0] = 0

    # method of potentials
    while any(i is None or j is None for i, j in zip(u, v)):
        for i, j in basis:
            if u[i] is not None:
                v[j] = c[i, j] + u[i]
            elif v[j] is not None:
                u[i] = v[j] - c[i, j]

    delta = np.zeros((N, M), dtype=int)

    for i in range(N):
        for j in range(M):
            delta[i, j] = c[i, j] - (v[j] - u[i])

    if np.min(delta) >= 0:
        break

    next_in = np.unravel_index(np.argmin(delta), delta.shape)
    basis.append(next_in)

    # remove lines and columns with a single basis element
    temp_removed = []
    ok = False
    while not ok:
        ok = True
        ii = [i for i, j in basis]
        jj = [j for i, j in basis]
        for i, j in basis:
            if ii.count(i) == 1 or jj.count(j) == 1:
                ok = False
                temp_removed.append((i, j))
                basis.remove((i, j))
                break

    # calculate positve and negative half-cycles
    signes = [None] * len(basis)
    signes[-1] = 1
    ck, (ci, cj) = -1, next_in
    theta = float('inf')

    while not all(signes):
        for k, (i, j) in enumerate(basis):
            if (i, j) == (ci, cj) or signes[k]:
                continue
            if i == ci or j == cj:
                signes[k] = -signes[ck]
                if signes[k] == -1:
                    theta = min(theta, x[i, j])
                if i == ci: cj = j
                if j == cj: ci = i
                ck = k

    # redistribute transportations
    for k, (i, j) in enumerate(basis):
        x[i, j] += signes[k] * theta

    # remove zero from the basis and readd temporarily removed elements
    for i, j in basis:
        if x[i, j] == 0:
            basis.remove((i, j))
            break
    basis.extend(temp_removed)

L = sum(c[i, j]*x[i, j] for i, j in basis)
print("L =", L)
print(x)
