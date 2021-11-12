#!/usr/bin/python3

from elgamal import *

def test_encryption():
    message = Point.G * 18

    # alice generates a key pair and sends
    # her public key to bob
    sk, pk = ElGamal.generate_key()

    # bob encrypts a message using alice's public key
    ciphertext = ElGamal.encrypt(pk, message)

    # alice receives a message from bob
    # and decrypts it with her private key
    received_message = ElGamal.decrypt(sk, ciphertext)

    # it should be the same message
    assert message == received_message


