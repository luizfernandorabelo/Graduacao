# Dados 3 inteiros a, b e c, de forma que ax + by = c, a função diophantine imprime uma fórmula geral de resolução da equação

def extended_gcd(a, b):

    if b > a:
        a, b = b, a

    assert b >= 0 and a + b > 0

    if b == 0:
        gcd, x1, x2 = a, 1, 0
    else:
        gcd, x2, x1 = extended_gcd(b, a % b)
        x2 -= x1 * (a // b)

    return gcd, x1, x2


def diophantine(a, b, c):

    gcd, x0, y0 = extended_gcd(a, b)

    assert c % gcd == 0

    a, b = max(a,b), min(a, b)

    p = b // gcd
    q = a // gcd
    k = c // gcd

    print(f'{a} * ({x0*k} + {p}t) + {b} * ({y0*k} - {q}t)  = {c}')


def main():

    a = int(input('a: '))
    b = int(input('b: '))
    c = int(input('c: '))

    diophantine(a, b, c)


if __name__ == '__main__':
    main()
