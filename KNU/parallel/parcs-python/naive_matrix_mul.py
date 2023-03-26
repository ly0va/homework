#!/usr/bin/python3


def mul(A, B):
    C = [[0 for i in range(len(B[0]))] for j in range(len(A))]
    for i in range(len(A)):
        for j in range(len(B[0])):
            for k in range(len(B)):
                C[i][j] += A[i][k] * B[k][j]
    return C

def max_matrix_element(A):
    return max(max(row) for row in A)

if __name__ == '__main__':
    with open('input.txt') as f:
        n = int(f.readline())
        A = [[int(x) for x in f.readline().split()] for i in range(n)]
        B = [[int(x) for x in f.readline().split()] for i in range(n)]
    C = mul(A, B)
    print(max_matrix_element(C))
