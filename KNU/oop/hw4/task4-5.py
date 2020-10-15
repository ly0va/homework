#!/usr/bin/python3

import math
import abc

PROMPT = '''
Create a figure:
1) Triangle
2) Equilateral Tringle
3) Circle
4) Rectangle
5) Square
6) Quit
> '''

class Figure(abc.ABC):

    @abc.abstractmethod
    def perimeter(self) -> float:
        pass

    @abc.abstractmethod
    def area(self) -> float:
        pass


class Triangle(Figure):

    def __init__(self, a: float, b: float, c: float):
        if a <= 0 or b <= 0 or c <= 0:
            raise Exception('Triangle has to have positive side lengths')
        largest = max(a, b, c)
        if largest >= a + b + c - largest:
            raise Exception("Can't form a triangle")

        self._a = a
        self._b = b
        self._c = c
        self._sides = [a, b, c]

    def perimeter(self) -> float:
        return self._a + self._b + self._c

    def angle(self, id: int) -> float:
        if not (1 <= id <= 3):
            raise Exception('Angle id should be from 1 to 3')
        a = self._sides[(id + 1) % 3]
        b = self._sides[(id + 2) % 3]
        c = self._sides[(id + 3) % 3]
        cos = (b**2 + c**2 - a**2)/(2*b*c)
        return math.acos(cos)

    def area(self) -> float:
        p = self.perimeter() / 2
        a, b, c = self._sides
        return math.sqrt((p - a)*(p - b)*(p - c)*p)


class EquilateralTringle(Triangle):

    def __init__(self, a: float):
        super().__init__(a, a, a)

    def area(self):
        # reimplementation
        return self._a**2 * 3**0.5 / 4


class Circle(Figure):

    def __init__(self, r: float):
        if r <= 0:
            raise Exception('Radius must be positive')
        self._r = r

    def area(self) -> float:
        return math.pi * self._r**2

    def perimeter(self) -> float:
        return 2 * math.pi * self._r


class Rectangle(Figure):

    def __init__(self, a: float, b: float):
        if a <= 0 or b <= 0:
            raise Exception('Sides must be positive')
        self._a = a
        self._b = b

    def perimeter(self) -> float:
        return 2*(self._a + self._b)

    def area(self) -> float:
        return self._a * self._b


class Square(Rectangle):

    def __init__(self, a: float):
        super().__init__(a, a)


def interact():
    option = input(PROMPT)
    figure: Figure
    if option == '1':
        a = float(input('a: '))
        b = float(input('b: '))
        c = float(input('c: '))
        figure = Triangle(a, b, c)
        alpha = figure.angle(1)
        beta = figure.angle(2)
        gamma = figure.angle(3)
        print(f'Triangle with angles: {alpha:.2f}, {beta:.2f}, {gamma:.2f}')
    elif option == '2':
        a = float(input('a: '))
        figure = EquilateralTringle(a)
    elif option == '3':
        r = float(input('radius: '))
        figure = Circle(r)
    elif option == '4':
        a = float(input('a: '))
        b = float(input('b: '))
        figure = Rectangle(a, b)
    elif option == '5':
        a = float(input('a: '))
        figure = Square(a)
    elif option == '6':
        return False
    else:
        print('Invalid option')
        return True

    print(f'Area: {figure.area():.2f}; Perimeter: {figure.perimeter():.2f}')
    return True

if __name__ == '__main__':
    interacting = True
    while interacting:
        try:
            interacting = interact()
        except Exception as e:
            print(e.args[0])
