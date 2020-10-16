#!/usr/bin/python3

import pytest
from parser import Lexer, Parser

parse = Parser(Lexer.build()).parse

class Tests:

    def test_trivial(self):
        assert parse('1+1') == 2
        assert parse('2*3') == 6
        assert parse('-2+3') == 1

    def test_spaces(self):
        assert parse(' 1   + 1  ') == 2
        assert parse('\t1\t+\t1 \t') == 2

    def test_precedence(self):
        assert parse('2 + 2*2') == 6
        assert parse('(2 + 2) * 2') == 8
        assert parse('2 + 1 = 3') == 1
        assert parse('2 + (1 = 3)') == 2

    def test_associative(self):
        assert parse('2 * 3 % 4') == 2
        assert parse('2 + 3 - 4') == 1

    def test_comparison(self):
        assert parse('1 + 3 <= 2 + 2')
        assert parse('123 = 100 + 20 + 3')
        assert parse('1 = 1 = 1') == 1 
        assert parse('2 = 2 = 2') == 0

    def test_fail(self):
        with pytest.raises(SyntaxError) as error:
            parse('!@#$%')
        assert 'Illegal character' in str(error.value)

        with pytest.raises(SyntaxError) as error:
            parse('() + 2 -')
        assert 'Invalid syntax' in str(error.value)
        

