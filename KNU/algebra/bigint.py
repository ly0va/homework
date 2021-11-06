#!/usr/bin/python3

import itertools as it
import functools as ft
from random import randint

BASE = 10**9

def flip(sign):
    assert sign in '+-'
    return '-' if sign == '+' else '+'

@ft.total_ordering
class BigInt:
    # canonical representation:
    # sign is either '+' or '-', '+' if 0
    # parts is list of digits in base BASE, no trailing 0, empty if 0

    parts: list[int]
    sign: str

    def __init__(self, num = '0'):
        if type(num) == BigInt:
            self.parts = num.parts.copy()
            self.sign = num.sign
            return

        if type(num) in [int, str]:
            num = str(num)
        else:
            raise TypeError

        if num[0] == '-':
            num = num[1:]
            self.sign = '-'
        else:
            if num[0] == '+':
                num = num[1:]
            self.sign = '+'

        num = num.lstrip('0')
        self.parts = []
        i = len(num)

        while i > 0:
            j = max(0, i-9)
            part = int(num[j:i])
            assert part >= 0
            self.parts.append(part)
            i = j

        self.normalize()

    def normalize(self):
        while len(self.parts) > 0 and self.parts[-1] == 0:
            self.parts.pop()
        if len(self.parts) == 0:
            self.sign = '+'

    def __repr__(self):
        if self.parts == []:
            return '0'
        sign = '' if self.sign == '+' else '-'
        return sign + str(self.parts[-1]) + \
            ''.join(str(part).zfill(9) for part in reversed(self.parts[:-1]))

    def copy(self):
        return BigInt(self)

    def __int__(self):
        assert self < BASE
        number = self.parts[0]
        return number if self.sign == '+' else -number

    def __neg__(self):
        result = self.copy()
        result.sign = flip(self.sign)
        result.normalize()
        return result

    def __eq__(self, other):
        other = BigInt(other)
        return (self.sign, self.parts) == (other.sign, other.parts)

    def __lt__(self, other):
        other = BigInt(other)
        if self.sign != other.sign:
            return self.sign == '-'
        if len(self.parts) != len(other.parts):
            return len(self.parts) < len(other.parts)

        for a, b in zip(reversed(self.parts), reversed(other.parts)):
            if a < b: return True
            if a > b: return False

        return False

    def __add__(self, other):
        other = BigInt(other)
        if self.sign != other.sign:
            return self - (-other)

        result = BigInt()
        carry = 0

        for a, b in it.zip_longest(self.parts, other.parts, fillvalue=0):
            carry, c = divmod(a + b + carry, BASE)
            result.parts.append(c)

        if carry != 0:
            result.parts.append(carry)

        result.sign = self.sign
        result.normalize()
        return result

    def __radd__(self, other):
        return self + other

    def __abs__(self):
        result = self.copy()
        result.sign = '+'
        return result

    def __sub__(self, other):
        other = BigInt(other)
        if self.sign != other.sign:
            return self + (-other)

        result = BigInt()
        carry = 0
        if abs(self) < abs(other):
            self, other = other, self
            result.sign = flip(self.sign)
        else:
            result.sign = self.sign

        for a, b in it.zip_longest(self.parts, other.parts, fillvalue=0):
            c = a - b - carry
            if c < 0:
                c += BASE
                carry = 1
            else:
                carry = 0
            result.parts.append(c)

        result.normalize()
        return result

    def __rsub__(self, other):
        return - self + other

    def __mul__(self, other):
        other = BigInt(other)
        result = BigInt()
        if self.sign != other.sign:
            result.sign = '-'
        else:
            result.sign = '+'

        length = len(self.parts) + len(other.parts)
        result.parts = [0] * length

        for i, a in enumerate(self.parts):
            j = carry = 0
            while j < len(other.parts) or carry:
                b = other.parts[j] if j < len(other.parts) else 0
                c = result.parts[i+j] + a*b + carry
                carry, result.parts[i+j] = divmod(c, BASE)
                j += 1

        result.normalize()
        return result

    def __rmul__(self, other):
        return self * other

    def _divmod(self, short: int):
        result = BigInt()
        if self.sign == '-' and short > 0 or \
           self.sign == '+' and short < 0:
            result.sign = '-'
        result.parts = [0] * len(self.parts)
        carry = 0
        for i in range(len(self.parts)-1, -1, -1):
            result.parts[i], carry = divmod(self.parts[i] + carry * BASE, short)

        if result.sign == '-':
            carry = short - carry
        result.normalize()
        return result, BigInt(carry)

    def __divmod__(self, other):
        # TODO: handle signs
        other = BigInt(other)
        if abs(other) < BASE:
            return self._divmod(int(other))

        left = BigInt(0)
        right = self.copy()

        while right-left > 1:
            middle = (left + right) // 2
            if middle*other > self:
                right = middle
            else:
                left = middle

        left.normalize()
        return left, self - left*other

    def __floordiv__(self, short):
        result, _ = divmod(self, short)
        return result

    def __mod__(self, short):
        _, result = divmod(self, short)
        return result

    def __pow__(self, power, mod = None):
        result = BigInt(1)
        a = self.copy()
        while power:
            if power & 1: result *= a
            a *= a
            if mod:
                result %= mod
                a %= mod
            power >>= 1
        return result

    def sqrt(self):
        assert self.sign == '+'
        left = BigInt(0)
        right = self.copy()

        while right-left > 1:
            middle = (left + right) // 2
            if middle*middle > self:
                right = middle
            else:
                left = middle

        left.normalize()
        return left

    # Newton's method for finding sqrt(N)
    def isqrt(self):
        assert self.sign == '+'
        x = self.copy()
        y = (x + 1) // 2
        while y < x:
            x = y
            y = (x + n // x) // 2
        return x

    @staticmethod
    def rand(upper_bound):
        upper_bound = BigInt(upper_bound)
        assert upper_bound > 0
        num_parts = len(upper_bound.parts)
        result = BigInt()
        result.parts = [randint(0, BASE-1) for _ in range(num_parts-1)]
        result.parts.append(randint(0, upper_bound.parts[-1]))
        result.normalize()
        return result

    def gcd(self, other):
        a, b = self.copy(), BigInt(other)
        while b != 0:
            a, b = b, a % b
        return a

    def gcd_extended(self, other):
        a, b = self.copy(), BigInt(other)
        if b == 0:
            return (BigInt(1), BigInt(0), a)
        x1, y1, gcd = b.gcd_extended(a % b)
        x = y1 - (b // a) * x1
        y = x1
        return x, y, gcd

    def lcm(self, other):
        return self // self.gcd(other) * other


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
            if (c1 - c2) % gcd != 0:
                return None

    if not can_use_crt:
        raise NotImplementedError("There is a solution, but I only know how to use CRT")

    ns = [lcm // m for m in ms]
    ks = [n.gcd_extended(m)[0] for n, m in zip(ns, ms)]
    return sum(c*k*n % lcm for c, k, n in zip(cs, ks, ns)) % lcm

