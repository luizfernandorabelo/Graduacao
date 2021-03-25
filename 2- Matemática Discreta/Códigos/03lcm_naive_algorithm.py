# Algoritmo "ingênuo" para calcular o mmc entre 2 inteiros a e b

def lcm(a, b): # O(a * b)

    assert a > 0 and b > 0

    product = a * b
    m = max(a, b)

    for i in range(m, product):
        if i % a == 0 and i % b == 0:
            return i

    return a * b


def main():

    a = int(input('a: '))
    b = int(input('b: '))

    print(lcm(a,b))


if __name__ == '__main__':
    main()
