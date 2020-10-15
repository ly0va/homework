#!/usr/bin/python3

tokens = (
    'CELL', 'NUMBER',
    'PLUS', 'MINUS', 'TIMES', 'DIVIDE', 'MODULO', 'EQUALS',
    'LPAREN', 'RPAREN',
)

# Tokens

t_PLUS    = r'\+'
t_MINUS   = r'-'
t_TIMES   = r'\*'
t_DIVIDE  = r'/'
t_MODULO  = r'%'
t_EQUALS  = r'='
t_LPAREN  = r'\('
t_RPAREN  = r'\)'
t_CELL    = r'[A-Z][0-9]+'

def t_NUMBER(t):
    r'\d+'
    t.value = int(t.value)
    return t

# Ignored characters
t_ignore = " \t"

def t_error(t):
    print(f"Illegal character {t.value[0]!r}")
    t.lexer.skip(1)

# Build the lexer
import ply.lex as lex
lex.lex()

# Precedence rules for the arithmetic operators
precedence = (
    ('left','EQUALS'),
    ('left','PLUS','MINUS'),
    ('left','TIMES','DIVIDE', 'MODULO'),
    ('right','UMINUS', 'UPLUS'),
)

# dictionary of names (for storing variables)
names = {
    'A1': 1,
    'A2': 2,
    'B4': 5
}

def p_statement_expr(p):
    'statement : expression'
    print(p[1])

def p_expression_binop(p):
    '''
    expression : expression PLUS expression
               | expression MINUS expression
               | expression TIMES expression
               | expression DIVIDE expression
               | expression MODULO expression
               | expression EQUALS expression
    '''
    if p[2] == '+'  : p[0] = p[1] + p[3]
    elif p[2] == '-': p[0] = p[1] - p[3]
    elif p[2] == '*': p[0] = p[1] * p[3]
    elif p[2] == '/': p[0] = p[1] / p[3]
    elif p[2] == '%': p[0] = p[1] % p[3]
    elif p[2] == '=': p[0] = int(p[1] == p[3])

def p_expression_uminus(p):
    'expression : MINUS expression %prec UMINUS'
    p[0] = -p[2]

def p_expression_uplus(p):
    'expression : PLUS expression %prec UPLUS'
    p[0] = +p[2]

def p_expression_group(p):
    'expression : LPAREN expression RPAREN'
    p[0] = p[2]

def p_expression_number(p):
    'expression : NUMBER'
    p[0] = p[1]

def p_expression_name(p):
    'expression : CELL'
    p[0] = names.get(p[1], 0)

def p_error(p):
    print(f"Syntax error at {p.value!r}")

import ply.yacc as yacc
yacc.yacc()

while True:
    try:
        s = input('> ')
    except EOFError:
        break
    yacc.parse(s)


