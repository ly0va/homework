#!/usr/bin/python3

from bigint import BigInt

def pollard_rho(number, iters=10000):
    # TODO: fix this whole thing
    number = BigInt(number)
    x = BigInt(2)
    attempts = BigInt(1)

    for _ in range(iters):
        y = x
        attempts *= 2
        count = attempts
        while count > 0:
            x = (x * x + 1) % number
            factor = BigInt.gcd(abs(x - y), number)
            if factor > 1:
                return factor
            count -= 1

    return BigInt(1)


def legendre_symbol(a, p):
    assert p > 2
    # assert is_prime(p)
    if a % p == 0: return 0
    return pow(a, (p-1)//2, p)


def jacobi_symbol(a, p):
    assert p % 2 == 1
    assert p > 1

    result = 1
    for factor in factorize(p):
        result *= legendre_symbol(a, factor)

    return result


def euler_phi(a):
    result = a.copy()
    for p in factorize(a):
        result -= result / p
    return result

def mobius_mu(a):
    factors = []
    for factor in factorize(a):
        if factors == [] or factors[-1] != factor:
            factors.append(factor)
        else:
            return 0
    return 1 if len(factors) % 2 == 0 else -1


def miller_rabin(n, k=40):
    if n == 2:
        return True

    if n == 1 or n % 2 == 0:
        return False

    r, s = 0, n - 1
    while s % 2 == 0:
        r += 1
        s //= 2

    for _ in range(k):
        # TODO fix randrange
        a = random.randrange(2, n - 1)
        x = pow(a, s, n)
        if x == 1 or x == n - 1:
            continue
        for _ in range(r - 1):
            x = pow(x, 2, n)
            if x == n - 1:
                break
        else:
            return False

    return True
