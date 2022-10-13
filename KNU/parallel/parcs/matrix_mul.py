#!/usr/bin/python2

from __future__ import print_function
from Pyro4 import expose


class Solver:
    def __init__(self, workers=None, input_file=None, output_file=None):
        self.input_file = input_file
        self.output_file = output_file
        self.workers = workers
        print("Initialized")

    def solve(self):
        matrix_a, matrix_b = self.read_input()

        n = len(matrix_a)
        assert n == len(matrix_a[0]), "Matrix A is not square"
        assert n == len(matrix_b), "Matrix A and B are not compatible"
        assert n == len(matrix_b[0]), "Matrix B is not square"

        mapped = []
        p = len(self.workers)

        for i in xrange(p):
            mapped.append(self.workers[i].compute(matrix_a, matrix_b, i, p))

        # reduce
        max_element = self.reduce(mapped)
        self.write_output(max_element)

        print("Job Finished")

    @staticmethod
    @expose
    def compute(matrix_a, matrix_b, start, step):
        n = len(matrix_a)
        answer = float('-inf')

        for i in xrange(start, n, step):
            row = [0] * n
            for j in xrange(n):
                row[j] = sum(matrix_a[i][k] * matrix_b[k][j] for k in xrange(n))
            answer = max(answer, max(row))

        return answer

    @staticmethod
    @expose
    def reduce(mapped):
        print("reduce")
        return max(chunk.value for chunk in mapped)


    def read_input(self):
        with open(self.input_file, 'r') as f:
            n = int(f.readline())
            matrix_a = [[int(x) for x in f.readline().split()] for i in xrange(n)]
            matrix_b = [[int(x) for x in f.readline().split()] for i in xrange(n)]
        return matrix_a, matrix_b

    def write_output(self, output):
        with open(self.output_file, 'w') as f:
            f.write(str(output))
        print("output done")

