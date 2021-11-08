#!/usr/bin/python3

from bigint import BigInt

def pollard_rho(number, iters=10):
    assert number % 2 == 1

    number = BigInt(number)
    sqrt = number.sqrt()
    if sqrt ** 2 == number:
        return sqrt

    x = BigInt(2)
    attempts = BigInt(1)

    for _ in range(iters):
        y = x
        attempts *= 2
        count = attempts
        while count > 0:
            x = (x * x + 1) % number
            factor = BigInt.gcd(abs(x - y), number)
            if factor > 1 and factor != number:
                return factor
            count -= 1

    return BigInt(1)


def factorize(number):
    number = BigInt(number)
    if number <= 3: return number

    while number % 2 == 0:
        yield BigInt(2)
        number //= 2

    while True:
        factor = pollard_rho(number)
        if factor != 1:
            yield factor
            number //= factor
        else:
            if number != 1:
                yield number
                return


def legendre_symbol(a, p):
    assert p > 2
    # assert is_prime(p)

    a, p = BigInt(a), BigInt(p)
    if a % p == 0: return 0
    result = pow(a, (p-1)//2, p)
    if result == p-1: result = -1
    return result

def jacobi_symbol(a, p):
    assert p > 1 and p % 2 == 1

    a, p = BigInt(a), BigInt(p)
    result = 1
    for factor in factorize(p):
        result *= legendre_symbol(a, factor)

    return result

def euler_phi(a):
    result = BigInt(a)
    factors = sorted(set(factorize(a)))
    print(factors)
    for p in factors:
        result -= result // p
    return result

def mobius_mu(a):
    factors = []
    for factor in sorted(factorize(a)):
        if factors == [] or factors[-1] != factor:
            factors.append(factor)
        else:
            return 0
    return 1 if len(factors) % 2 == 0 else -1


def miller_rabin(n, k=40):
    n = BigInt(n)
    if n == 2:
        return True

    if n == 1 or n % 2 == 0:
        return False

    r, s = 0, n - 1
    while s % 2 == 0:
        r += 1
        s //= 2

    for _ in range(k):
        a = 0
        while a <= 1: a = BigInt.rand(n - 2)
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

def discrete_log_shanks(a, b, m):
    # solves a^x == b (mod m)
    a, b, m = BigInt(a), BigInt(b), BigInt(m)
    n = m.sqrt() + 1
    values = {}

    i = 0
    while n >= i:
        values[pow(a, i*n, m)] = i
        i += 1
    
    i = 0
    while n >= i:
        cur = pow(a, i, m) * b % m;
        if cur in values:
            ans = values[cur] * n - i;
            if ans < m: return ans
        i += 1

    return None


def discrete_sqrt_cipolla(n, p):
    assert p > 2
    # assert is_prime(p)

    n, p, a = BigInt(n), BigInt(p), BigInt(1)
    while legendre_symbol(a*a - n, p) != -1:
        a += 1

    k = (a*a - n) % p
    power = (p + 1)//2
    u, v = a, BigInt(1)
    x, y = BigInt(1), BigInt(0)

    while power > 0:
        if power % 2 == 1:
            x, y = (x*u + y*v*k) % p, (x*v + y*u) % p
        u, v = (u*u + v*v*k) % p, 2*u*v % p
        power //= 2

    assert y == 0
    return x


def solve_congruence(cs, ms):
    assert len(cs) == len(ms), "Invalid vector lengths"
    can_use_crt = True
    lcm = BigInt(1)
    cs = list(map(BigInt, cs))
    ms = list(map(BigInt, ms))

    for c1, m1 in zip(cs, ms):
        lcm = BigInt.lcm(lcm, m1)
        for c2, m2 in zip(cs, ms):
            if m1 == m2:
                if c1 != c2: return None
                else: continue
            gcd = BigInt.gcd(m1, m2)
            can_use_crt = can_use_crt and gcd == 1
            if abs(c1 - c2) % gcd != 0:
                return None

    if not can_use_crt:
        raise NotImplementedError("There is a solution, but I only know how to use CRT")

    ns = [lcm // m for m in ms]
    ks = [n.gcd_extended(m)[0] for n, m in zip(ns, ms)]
    return sum(c*k*n % lcm for c, k, n in zip(cs, ks, ns)) % lcm

