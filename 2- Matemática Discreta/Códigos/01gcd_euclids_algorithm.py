# Algoritmo de Euclides para encontrar o mdc entre dois inteiros a e b

def gcd(a, b): # O(log_2(a) + log_2(b))

    assert a >= 0 and b >= 0 and a + b > 0

    if a == 0 or b == 0:
        return max(a, b)

    while a > 0 and b > 0:
        print(f'GCD({a},{b}) =', end=' ')
        if a >= b:
            a %= b
        else:
            b %= a
        
    return max(a, b)


def main():

    a = int(input('a: '))
    b = int(input('b: '))

    print(gcd(a,b))


if __name__ == '__main__':
    main()
