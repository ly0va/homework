#!/usr/bin/python3

from random import randint

def generate_matrix(n):
    with open('input.txt', 'w') as f:
        f.write(str(n) + '\n')
        # matrix a
        for i in range(n):
            for j in range(n):
                f.write(str(randint(-100, 100)) + ' ')
            f.write('\n')
        # matrix b
        for i in range(n):
            for j in range(n):
                f.write(str(randint(-100, 100)) + ' ')
            f.write('\n')


if __name__ == '__main__':
    import os
    generate_matrix(int(os.environ['N']))
