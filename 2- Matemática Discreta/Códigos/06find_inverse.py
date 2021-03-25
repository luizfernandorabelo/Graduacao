# Algoritmo que mostra o inverso de um inteiro a em (mod n), com mdc(a,n) = 1

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


def find_inverse(a, n):

    if a > n:
        a %= n

    gcd, x1, x2 = extended_gcd(n, a)

    assert gcd == 1

    if x2 < 0:
        x2 += n
    
    return x2


def main():

    a = int(input('a: '))
    n = int(input('n: '))

    inverse = find_inverse(a,n)

    print(f'{a}⁻¹ (mod {n}) ≡ {inverse} ⇒ {a} x {inverse} ≡ 1 (mod {n})')


if __name__ == '__main__':
    main()
