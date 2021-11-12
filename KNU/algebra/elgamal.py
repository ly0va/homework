#!/usr/bin/python3
from random import randrange

# secp256k1
class Point:
    p = 2**256 - 2**32 - 977
    a = 0
    b = 7

    @classmethod
    def inv(cls, n):
        return pow(n, cls.p - 2, cls.p)

    def __init__(self, x, y):
        self.x = x % Point.p
        self.y = y % Point.p

    def __repr__(self):
        return f'Point({self.x}, {self.y})'

    def __neg__(self):
        return Point(self.x, -self.y)

    def __sub__(self, other):
        return self + (-other);

    def __add__(self, other):
        if self == Point.O:
            return other.copy()
        if other == Point.O:
            return self.copy()

        if self.x == other.x:
            if self.y == -other.y:
                return Point.O
            else:
                k = (3 * self.x**2 + Point.a) * Point.inv(2 * self.y)
        else:
            k = (other.y - self.y) * Point.inv(other.x - self.x)

        k %= Point.p
        x = k**2 - self.x - other.x
        y = k*(self.x - x) - self.y
        return Point(x, y)

    def __mul__(self, n):
        result = Point.O
        point = self.copy()
        while n > 0:
            if n & 1: result += point
            point += point
            n >>= 1
        return result

    def __rmul__(self, n):
        return self * n

    def __eq__(self, other):
        return (self.x, self.y) == (other.x, other.y)

    def copy(self):
        return Point(self.x, self.y)

Point.O = Point(0, 0)
Point.G = Point(
    int('79BE667E_F9DCBBAC_55A06295_CE870B07_029BFCDB_2DCE28D9_59F2815B_16F81798', 16),
    int('483ADA77_26A3C465_5DA4FBFC_0E1108A8_FD17B448_A6855419_9C47D08F_FB10D4B8', 16)
)


class ElGamal:
    @staticmethod
    def encrypt(pk, message: Point):
        y = randrange(1, Point.p)
        secret = pk * y
        c1 = Point.G * y
        c2 = message + secret
        return c1, c2

    @staticmethod
    def decrypt(sk, ciphertext) -> Point:
        c1, c2 = ciphertext
        secret = c1 * sk
        message = c2 - secret
        return message

    @staticmethod
    def generate_key():
        sk = randrange(1, Point.p)
        pk = Point.G * sk
        return sk, pk

    @staticmethod
    def encode(message: bytes) -> Point:
        pass

    @staticmethod
    def decode(message: Point) -> bytes:
        pass
