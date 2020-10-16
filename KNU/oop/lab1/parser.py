#!/usr/bin/python3

import ply.lex as lex
import ply.yacc as yacc

TOKEN_LIST = (
    'NUMBER',
    'PLUS', 'MINUS', 'TIMES', 'DIVIDE', 'MODULO',
    'EQUALS', 'LESS', 'GREATER', 'LTEQ', 'GTEQ',
    'LPAREN', 'RPAREN',
)

class Lexer:
    tokens = TOKEN_LIST

    # Tokens
    t_PLUS    = r'\+'
    t_MINUS   = r'-'
    t_TIMES   = r'\*'
    t_DIVIDE  = r'/'
    t_MODULO  = r'%'
    t_LTEQ    = r'<='
    t_GTEQ    = r'>='
    t_LESS    = r'<'
    t_GREATER = r'>'
    t_EQUALS  = r'='
    t_LPAREN  = r'\('
    t_RPAREN  = r'\)'
    # Ignored characters
    t_ignore = " \t"

    @staticmethod
    def t_NUMBER(token):
        r'\d+'
        token.value = int(token.value)
        return token

    @staticmethod
    def t_error(token):
        raise SyntaxError('Illegal character')

    @classmethod
    def build(cls):
        return lex.lex(module=cls)



class Parser:
    tokens = TOKEN_LIST

    # Precedence rules for the arithmetic operators
    precedence = (
        ('left','EQUALS', 'LESS', 'GREATER', 'LTEQ', 'GTEQ'),
        ('left','PLUS','MINUS'),
        ('left','TIMES','DIVIDE', 'MODULO'),
        ('right','UMINUS', 'UPLUS'),
    )

    def p_expression_binop(self, p):
        '''
        expression : expression PLUS expression
                   | expression MINUS expression
                   | expression TIMES expression
                   | expression DIVIDE expression
                   | expression MODULO expression
                   | expression EQUALS expression
                   | expression LESS expression
                   | expression GREATER expression
                   | expression LTEQ expression
                   | expression GTEQ expression
        '''
        if p[2] == '+'  : p[0] = p[1] + p[3]
        elif p[2] == '-': p[0] = p[1] - p[3]
        elif p[2] == '*': p[0] = p[1] * p[3]
        elif p[2] == '/': p[0] = p[1] / p[3]
        elif p[2] == '%': p[0] = p[1] % p[3]
        elif p[2] == '=': p[0] = int(p[1] == p[3])
        elif p[2] == '<': p[0] = int(p[1] < p[3])
        elif p[2] == '>': p[0] = int(p[1] > p[3])
        elif p[2] == '<=': p[0] = int(p[1] <= p[3])
        elif p[2] == '>=': p[0] = int(p[1] >= p[3])

    def p_expression_uminus(self, p):
        'expression : MINUS expression %prec UMINUS'
        p[0] = -p[2]

    def p_expression_uplus(self, p):
        'expression : PLUS expression %prec UPLUS'
        p[0] = +p[2]

    def p_expression_group(self, p):
        'expression : LPAREN expression RPAREN'
        p[0] = p[2]

    def p_expression_number(self, p):
        'expression : NUMBER'
        p[0] = p[1]

    def p_error(self, p):
        raise SyntaxError('Invalid syntax')

    def __init__(self, lexer):
        self.parser = yacc.yacc(module=self)
        self.lexer = lexer

    def parse(self, text):
        if text.strip() == '':
            return 0
        return self.parser.parse(text, lexer=self.lexer)


if __name__ == '__main__':
    lexer = Lexer.build()
    parser = Parser(lexer)
    while True:
        try:
            text = input('> ')
        except EOFError:
            break
        print(parser.parse(text))

