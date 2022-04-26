#!/usr/bin/env python3

#%%
def showPeriod(f, a):
    s = set()
    for i in range(65536):
        t = plusmul(a)
        if t in s:
            break
        s.add(t)
        print(f"plusmul({a})={t}")
        a = t
    print(len(s), s)

def countPeriod(f, i):
    c = 1
    a = f(i)
    while a!=i:
        a = f(a)
        c += 1
    return c

def lfsr(i):
    i = (i^(i>>7))&65535
    i = (i^(i<<9))&65535
    i = (i^(i>>13))&65535
    return i

def lfsr2(i):
    i = (i^(i>>7))&65535
    i = (i^(i<<9))&65535
    i = (i^(i>>8))&65535
    return i

def incdiv(i):
    return (i+1)%65535

def plusdiv(i):
    return (i+2872)%65535

def plusmul(i):
    return (i*12345+i*(65536-12345)+2872)%65535

#%%
print(f"lfsr period is {countPeriod(lfsr, 1)}")
print(f"lfsr2 period is {countPeriod(lfsr2, 1)}")
print(f"incdiv period is {countPeriod(incdiv, 0)}")
print(f"plusdiv period is {countPeriod(plusdiv, 0)}")
print(f"plusmul period is {countPeriod(plusmul, 0)}")

#%%
import math, sys
for i in range(65536):
    if math.gcd(i, 65535)==1:
        print(i, hex(i), bin(i))
