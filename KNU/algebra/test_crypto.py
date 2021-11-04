#!/usr/bin/python3

from bigint import BigInt, solve_congruence
from crypto import *

def test_rho_factorization():
    assert pollard_rho(10403) == 101
    assert pollard_rho(7477 * 5003) == 5003

def test_congruence_solver():
    solve_congruence([6, 5, 3], [8, 13, 15]) == 798

