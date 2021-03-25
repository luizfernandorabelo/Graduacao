# Aplicação do Algoritmo de Euclies para cálculo do mmc entre dois inteiros a e b

def lcm(a, b): # O(log_2(a) + log_2(b))

    assert a >= 0 and b >= 0 and a + b > 0

    product = a * b

    if product == 0:
        return 0

    while a > 0 and b > 0:
        if a >= b:
            a %= b
        else:
            b %= a
        
    return product // max(a, b)


def main():

    a = int(input('a: '))
    b = int(input('b: '))

    print(lcm(a,b))


if __name__ == '__main__':
    main()
