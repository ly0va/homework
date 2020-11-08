#!/usr/bin/python3

from sympy import Matrix

#####     Promlem parameters     #####
##### (Already in standard form) #####

A = Matrix([
    [-1,  2, 1, 0,  0],
    [2,  -1, 0, 1,  0],
    [1,   1, 0, 0, -1],
])

b = Matrix([6, 8, 2])

c = Matrix([1, 4, 0, 0, 0])

######################################

def simplex_method(A, b, c, basis):
    print('step')
    print(A)
    print(b)
    print(c)
    print(basis)
    m, n = A.shape

    # compute delta_k
    deltas = [
        c[j] - sum(c[basis[i]]*A[i, j] for i in range(m))
        for j in range(n)
    ]

    print('deltas', deltas)

    # check if optimal vertex is reached
    if all(delta >= 0 for delta in deltas):
        xstar = [0] * n
        for i in range(m):
            xstar[basis[i]] = b[i]
        return xstar

    k = deltas.index(min(deltas))  # determine in_index

    # check if target function is unbounded
    if all(A[i, k] <= 0 for i in range(m)): return

    # compute theta_k
    thetas = [
        b[i]/A[i, k] if A[i, k] > 0 else float('inf')
        for i in range(m)
    ]

    print('thetas', thetas)

    l = thetas.index(min(thetas))  # determine out_index
    basis[l] = k                   # change basis

    # perform gauss transformations
    b[l] /= A[l, k]
    A[l, :] /= A[l, k]
    for i in range(m):
        if i == l: continue
        b[i] -= b[l] * A[i, k]
        A[i, :] -= A[l, :] * A[i, k]

    return simplex_method(A, b, c, basis)   # start over


# M-method
m, n = A.shape
M = max(max(abs(A)), max(abs(b)), max(abs(c))) + 1
basis = []
ys = 0

for i in range(m):
    if A[i, n-m+i] == 1:
        basis.append(n-m+i)
    else:
        col = [0] * m
        col[i] = 1
        A = A.row_join(Matrix(col))
        c = c.col_join(Matrix([M]))
        basis.append(n + ys)
        ys += 1

xstar = simplex_method(A, b, c, basis)

if xstar is None or any(x > 0 for x in xstar[n:]):
    print("No solution")

print('x* =', xstar[:n])
print('L* =', c.dot(xstar))

