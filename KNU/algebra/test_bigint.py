#!/usr/bin/python3

from bigint import BigInt

def test_create():
    a = BigInt()
    assert a.sign == '+'
    assert a.parts == []
    assert repr(a) == '0'

    b = BigInt('-123')
    assert b.sign == '-'
    assert b.parts == [123]
    assert repr(b) == '-123'

    c = BigInt('111000222222')
    assert c.sign == '+'
    assert c.parts == [222222, 111]
    assert repr(c) == '111000222222'

def test_compare():
    assert BigInt('-18') == -18
    assert BigInt('+0') == BigInt('-0')
    assert BigInt('123') < BigInt('124')
    assert BigInt('123') > BigInt('-1')
    assert BigInt('1000000000') > BigInt('999999999')

def test_add_sub():
    assert BigInt('0') + 1 == BigInt('1')
    assert BigInt('999999999') + 1 == BigInt('1000000000')
    assert BigInt('-123') + BigInt('123') == 0
    assert BigInt('123') - BigInt('124') == BigInt('-1')

def test_mul():
    assert BigInt('123456') * BigInt('-987654') == BigInt('-121931812224')
    assert BigInt('123') * 0 == 0

def test_div_mod():
    assert BigInt('1234512345') // 5 == 246902469
    assert BigInt('123123') % 5 == 3
    assert BigInt('111000222222') // BigInt('1000000000') == 111
    assert BigInt('111000222222') % BigInt('1000000000') == 222222

def test_sqrt():
    assert BigInt('0').sqrt() == 0
    assert BigInt('2').sqrt() == 1
    assert BigInt('123456').sqrt() == 351

