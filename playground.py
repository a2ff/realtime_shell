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

def countPeriod(f, x):
    c = 1
    a = f(x)
    while a!=x:
        a = f(a)
        c += 1
    return c

def metcalf(x):
    x = (x^(x>>7))&65535
    x = (x^(x<<9))&65535
    x = (x^(x>>13))&65535
    return x

def metcalf2(x):
    x = (x^(x>>7))&65535
    x = (x^(x<<9))&65535
    x = (x^(x>>8))&65535
    return x

def incdiv(x):
    return (x+1)%65535

def plusdiv(x):
    return (x+2872)%65535

def plusmul(x):
    return (x*12345+x*(65536-12345)+2872)%65535
#%%
def pegray_modinc(b, x):
    """modular-increment a b-bit parity-enhanced Gray number with wrap-around
    (unsigned integers; intermediate computations use b+1 bits)
    """
    if x==1<<b:     # wrap before overflow
        return 1
    msb = x&~(x-1)
    return x^((msb<<1)|1)

help(pegray_modinc)

g = 1   # 0 in parity-enhanced Gray code
for i in range(10):
    print(f"{i:5} {i:016b} PEG {g:5} {g:016b} G {g>>1:5} {g>>1:016b}")
    g = pegray_modinc(3, g)
print(f"                 final PEG {g:5} {g:016b} G {g>>1:5} {g>>1:016b}")

for i in range(13,18):
    print(f"{i}-bit parity-enhanced gray period is {countPeriod(lambda x: pegray_modinc(i, x), 1)} (needs {i+1}-bit words)")
#%%
print(f"metcalf period is {countPeriod(metcalf, 1)}")
print(f"metcalf2 period is {countPeriod(metcalf2, 1)}")
print(f"incdiv period is {countPeriod(incdiv, 0)}")
print(f"plusdiv period is {countPeriod(plusdiv, 0)}")
print(f"plusmul period is {countPeriod(plusmul, 0)}")
#%%
import math, sys
for i in range(65536):
    if math.gcd(i, 65535)==1:
        print(i, hex(i), bin(i))