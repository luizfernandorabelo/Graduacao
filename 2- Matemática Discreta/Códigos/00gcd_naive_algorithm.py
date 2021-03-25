# Algoritmo "ingênuo" para calcular o mdc entre 2 inteiros a e b

def gcd(a, b): # O(|a-b|)

    assert a >= 0 and b >= 0 and a + b > 0

    if a == 0 or b == 0:
        return max(a, b)

    m = min(a, b)

    for i in range(m, 1, -1):
        if a % i == 0 and b % i == 0:
            return i

    return 1


def main():

    a = int(input('a: '))
    b = int(input('b: '))

    print(gcd(a,b))


if __name__ == '__main__':
    main()
