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
        if other == 0:
            return self.copy()
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
        if other == 0:
            return self.copy()
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
        result.parts = [0] * len(self.parts)
        carry = 0
        for i in range(len(self.parts)-1, -1, -1):
            result.parts[i], carry = divmod(self.parts[i] + carry * BASE, short)

        # TODO: does not work for negative short
        if self.sign == '-' and short > 0 or \
           self.sign == '+' and short < 0:
            result.sign = '-'
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
        if self < 0:
            left, right = right, left

        while right-left > 1:
            middle = (left + right) // 2
            if middle*other > self:
                right = middle
            else:
                left = middle

        left.normalize()
        mod = self - left*other
        if mod < 0:
            mod += other
        return left, mod

    def __floordiv__(self, short):
        result, _ = divmod(self, short)
        return result

    def __mod__(self, short):
        _, result = divmod(self, short)
        return result

    def __pow__(self, power, mod = None):
        result, power = BigInt(1), BigInt(power)
        a = self.copy()
        while power != 0:
            if power % 2 == 1: result *= a
            a *= a
            if mod:
                result %= mod
                a %= mod
            power //= 2
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
        if a == 0:
            return (BigInt(0), BigInt(1), b)
        x1, y1, gcd = (b % a).gcd_extended(a)
        x = y1 - (b // a) * x1
        y = x1
        return x, y, gcd

    def lcm(self, other):
        return self // self.gcd(other) * other

    def __hash__(self):
        return hash((self.sign, tuple(self.parts)))


