#!/usr/bin/python3

import random as rd

rd.seed(2017)

for i in range(100):
    s = rd.randint(1, rd.randint(10, rd.randint(100, 32768)))
    for j in range(s):
        print(rd.randint(0, 9), end='')
    if (rd.randint(0, 1) == 0):
        print('+', end='')
    else:
        print('*', end='')
    s = rd.randint(1, s)
    for j in range(s):
        print(rd.randint(0, 9), end='')
    print()

