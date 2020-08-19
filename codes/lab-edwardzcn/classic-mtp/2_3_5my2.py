#!#!/usr/bin/env python
# -*- coding: utf-8 -*-

# MTP 是本人修改过的题面
# 这里的文件都是草稿 如若不能理解请从题面出发自行解决

from hashlib import sha256
from Crypto.Util.strxor import strxor
from Crypto.Util.number import (
    long_to_bytes,
    bytes_to_long
)

salt_of_key = ''
salt_of_pt = ''
LINESIZE = 50


def gen_offset(student_id_str):
    hash = int(sha256(student_id_str+salt_of_pt).hexdigest(), 16)
    return hash % 60013


def gen_key(student_id_str, LINESIZE):
    return_key = ""
    h = int(sha256(student_id_str+salt_of_key).hexdigest(), 16)
    for i in range(LINESIZE//2):
        tmp = h % 89 + 33
        h //= 89
        return_key += chr(tmp)
    h = int(sha256(student_id_str+salt_of_key).hexdigest(), 16)
    for i in range(LINESIZE//2):
        tmp = h % 89 + 33
        h //= 89
        return_key += chr(tmp)
    return return_key


if __name__ == "__main__":
    id = raw_input("Input you student id:\n")
    start_index = gen_offset(id)

    plaintext = []
    with open('Book3.txt', 'r') as file:
        textall = file.read()
        for i in range(10):
            plaintext.append(textall[start_index: start_index+LINESIZE])
            start_index += LINESIZE

    key = gen_key(id, LINESIZE)
    print(key)
    print("""Here's sentences from a book encrypt with one key using XOR,
Find the key and complete this challenge~
Input key with""")
    ciphertext = []
    for i in range(10):
        ciphertext.append(strxor(key, plaintext[i]).encode("hex"))
        print(ciphertext[i])

    while True:
        ans = raw_input("Input key:\n")
        if ans == key:
            print("Congratulations!")
            exit(0)
        else:
            print("FAILED...")
