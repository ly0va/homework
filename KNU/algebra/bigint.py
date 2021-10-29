#!/usr/bin/python3

import itertools as it
import functools as ft

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

    def __divmod__(self, short):
        result = BigInt()
        result.parts = [0] * len(self.parts)
        carry = 0
        for i in range(len(self.parts)-1, -1, -1):
            result.parts[i], carry = divmod(self.parts[i] + carry * BASE, short)

        result.normalize()
        return result, carry

    def __floordiv__(self, short):
        result, _ = divmod(self, short)
        return result

    def __mod__(self, short):
        _, result = divmod(self, short)
        return result

    def __pow__(self, short):
        result = BigInt(1)
        a = self.copy()
        while short:
            if short & 1: result *= a
            a *= a
            short >>= 1
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
