import gmpy2
import binascii
# import math
# import sys

from Crypto.PublicKey import RSA


'''
Hastad’s Broadcast Attack is a mathematical approach to recover the secret message that encrypted using RSA with multiple different moduli numbers known as n1, n2, n3,…, ni and a single small public exponent e. This attack is based on Chinese Remainder Theorem(CRT) that said if all the moduli are relatively prime, we can compute x such as x ≡ y1 (mod n1), x ≡ y2 (mod n2), x ≡ y3 (mod n3). 
'''


# the hastad attack

def hastadAttack(n1, n2, n3, c1, c2, c3):
    e = 3
    M = n1*n2*n3
    m1 = M//n1
    m2 = M//n2
    m3 = M//n3

    t1 = c1*(m1)*gmpy2.invert(m1, n1)

    t2 = c2*(m2)*gmpy2.invert(m2, n2)
    t3 = c3*(m3)*gmpy2.invert(m3, n3)
    x = (t1+t2+t3) % M  # chinese reminder theorem
    print("x = {}".format(x))
    print()
    m, exact = gmpy2.iroot(x, e)  # recover m

    print(m)

    # if exact:

    #     # convert int -> hex -> ascii
    #     print(binascii.unhexlify(gmpy2.digits(m, 16)))


e = 3

hastadAttack(n1, n2, n3, c1, c2, c3)
