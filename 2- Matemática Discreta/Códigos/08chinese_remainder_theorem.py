# Algoritmo que dá uma solução entre 0 e n1 * n2 para o seguinte sistema de equações, sendo n1 e n2 coprimos:
#       | n = r1 (mod n1)
#       | n = r2 (mod n2)

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


def chinese_remainder(n1, r1, n2, r2):

    if n2 > n1:
        n1, n2 = n2, n1
        r1, r2 = r2, r1

    gcd, x1, x2 = extended_gcd(n1, n2)

    assert gcd == 1

    n = (r1 * x2 * n2 + r2 * x1 * n1) % (n1 * n2)

    return n


def main():

    n1 = int(input('n1: '))
    r1 = int(input('r1: '))
    n2 = int(input('n2: '))
    r2 = int(input('r2: '))

    print(chinese_remainder(n1,r1,n2,r2))


if __name__ == '__main__':
    main()
