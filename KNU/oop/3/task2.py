#!/usr/bin/python3

from abc import ABC, abstractmethod

PROMPT = '''
Pick one:
1) Create group
2) Add a good student to a group
3) Add a bad student to a group
4) Get group info
5) Get full group info
6) Quit
> '''

# inheriting from ABC - abstract base class
class Student(ABC):

    def __init__(self, name: str):
        self.name = name
        self.state = ''

    def Relax(self):
        self.state += 'Relax'

    def Read(self):
        self.state += 'Read'

    def Write(self):
        self.state += 'Write'

    @abstractmethod
    def Study(self):
        pass


class GoodStudent(Student):

    def __init__(self, name: str):
        super().__init__(name)
        self.state += 'good'

    def Study(self):
        self.Read()
        self.Write()
        self.Read()
        self.Write()
        self.Relax()


class BadStudent(Student):

    def __init__(self, name: str):
        super().__init__(name)
        self.state += 'bad'

    def Study(self):
        self.Relax()
        self.Relax()
        self.Relax()
        self.Relax()
        self.Relax()


class Group:

    def __init__(self, name: str):
        self.name = name
        self.students = []

    def AddStudent(self, student: Student):
        self.students.append(student)

    def GetInfo(self) -> str:
        names = ', '.join(st.name for st in self.students)
        return f'Name: {self.name}; Students: {names}'

    def GetFullInfo(self) -> str:
        info = '\n'.join(f'Name: {st.name}; Status: {st.state}' 
                         for st in self.students)
        return f'Group name: {self.name}\nStudents:\n{info}'


if __name__ == '__main__':
    group = None
    while True:
        option = input(PROMPT)
        if option == '1':
            name = input('Group name: ')
            group = Group(name)
            print('Group created!')
        elif option == '6':
            print('Bye!')
            break
        else:
            if group is None:
                print('Create a group first!')
            elif option == '2' or option == '3':
                name = input('Student name: ')
                student = GoodStudent(name) \
                    if option == '2' else BadStudent(name)
                group.AddStudent(student)
                print('Student added!')
            elif option == '4':
                print(group.GetInfo())
            elif option == '5':
                print(group.GetFullInfo())
            else:
                print('Wrong option!')


