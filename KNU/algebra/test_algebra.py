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
    x = discrete_sqrt_cipolla(5, 11)
    assert x*x % 11 == 5

    x = discrete_sqrt_cipolla(23, 101)
    assert x*x % 101 == 23

def test_legendre():
    assert legendre_symbol(12345, 331) == -1
    assert legendre_symbol(35, 7) == 0
    assert legendre_symbol(4, 7) == 1

def test_jacobi():
    assert jacobi_symbol(29, 45) == 1
    assert jacobi_symbol(30, 39) == 0
    assert jacobi_symbol(28, 33) == -1

def test_euler():
    assert euler_phi(91) == 72
    assert euler_phi(1) == 1
    assert euler_phi(100) == 40
    assert euler_phi(101) == 100

def test_mobius():
    assert mobius_mu(100) == 0
    assert mobius_mu(10) == 1
    assert mobius_mu(11) == -1
