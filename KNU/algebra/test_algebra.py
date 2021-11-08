#!/usr/bin/python3

from bigint import BigInt
from algebra import *

def test_rho_factorization():
    assert pollard_rho(10403) == 101
    assert pollard_rho(7477 * 5003) == 5003
    assert pollard_rho(4049) == 1

def test_congruence_solver():
    assert solve_congruence([6, 5, 3], [8, 13, 15]) == 798

def test_primality():
    assert miller_rabin(4049)
    assert not miller_rabin(4049*7477)

def test_discrete_log():
    x = discrete_log_shanks(56, 37, 101)
    assert pow(BigInt(56), x, 101) == 37
    
    x = discrete_log_shanks(18, 103, 4049)
    assert pow(BigInt(18), x, 4049) == 103

def test_discrete_sqrt():
    # TODO fix modulo of negative number ?
    # assert discrete_sqrt_cipolla(5, 11) == 4
    pass
