#!/usr/bin/python
import math

def decrypt(cipherText, privateKey):
    plainText = ""
    n = privateKey[0]
    d = privateKey[1]
    j = 0

    for i in cipherText:
        if j % 2 == 0:
            low = ord(i)
        elif j % 2 == 1:
            hi = ord(i)
            temp = low + hi * pow(2, 8)
            m = pow(temp, d, n)
            plainText += chr(m)
        j += 1

    print "+++++++++++BEGIN PLAINTEXT++++++++++++"
    print plainText
    print "++++++++++++END PLAINTEXT+++++++++++++"
    return plainText

def encrypt(plainText, publicKey):
    cipherText = ""
    n = publicKey[0]
    e = publicKey[1]
    j = 0

    for i in plainText:
        temp = pow(ord(i), e, n)
        M = divmod(temp, 0x100)
        cipherText += chr(M[1])
        cipherText += chr(M[0])

    print "++++++++++BEGIN CIPHERTEXT++++++++++++"
    print cipherText
    print "+++++++++++END CIPHERTEXT+++++++++++++"
    return cipherText
