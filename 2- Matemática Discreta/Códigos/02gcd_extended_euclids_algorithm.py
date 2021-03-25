# Algoritmo de Euclides Estendido (Calcula o MDC e fornece a combinação linear x1 * a + x2 * b)

def extended_gcd(a, b): # O(log_2(a) + log_2(b))

    if b > a:
        a, b = b, a

    assert b >= 0 and a + b > 0

    if b == 0:
        gcd, x1, x2 = a, 1, 0
    else:
        gcd, x2, x1 = extended_gcd(b, a % b)
        x2 -= x1 * (a // b)

    return gcd, x1, x2


def main():

    a = int(input('a: '))
    b = int(input('b: '))

    gcd, x1, x2 = extended_gcd(a, b)

    print(f'GCD({max(a,b)}, {min(a,b)}) = {gcd} = {x1} * {max(a,b)} + {x2} * {min(a,b)}')


if __name__ == '__main__':
    main()
