#!/usr/bin/python3

import abc
import math

PROMPT = '''
Create a triangle:
1) Isosceles triangle
2) Right triangle
3) Quit
> '''


class Triangle(abc.ABC):

    def __init__(self, a: float, b: float, gamma: float):
        if a <= 0 or b <= 0 or not (0 < gamma < math.pi):
            raise Exception('Invalid triangle parameters')
        self._a = a
        self._b = b
        self._gamma = gamma

    @abc.abstractmethod
    def perimeter(self) -> float:
        pass

    @abc.abstractmethod
    def area(self) -> float:
        pass


class IsoscelesTriangle(Triangle):

    def __init__(self, a: float, gamma: float):
        super().__init__(a, a, gamma)

    def perimeter(self) -> float:
        c = math.sin(self._gamma / 2) * 2 * self._a
        return self._a * 2 + c

    def area(self) -> float:
        return self._a**2 * math.sin(self._gamma) / 2


class RightTriangle(Triangle):

    def __init__(self, a: float, b: float):
        super().__init__(a, b, math.pi/2)

    def perimeter(self) -> float:
        c = math.hypot(self._a, self._b)
        return self._a + self._b + c

    def area(self) -> float:
        return self._a * self._b / 2


def interact():
    option = input(PROMPT)
    triangle: Triangle
    if option == '1':
        a = float(input('side: '))
        gamma = float(input('angle: '))
        triangle = IsoscelesTriangle(a, gamma)
    elif option == '2':
        a = float(input('first side: '))
        b = float(input('second side: '))
        triangle = RightTriangle(a, b)
    elif option == '3':
        return False
    else:
        print('Invalid option')
        return True

    print(f'Area: {triangle.area():.2f}; Perimeter: {triangle.perimeter():.2f}')
    return True

if __name__ == '__main__':
    interacting = True
    while interacting:
        try:
            interacting = interact()
        except Exception as e:
            print(e.args[0])
    

