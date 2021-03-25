# Algoritmo que determina b^e (mod n) 

def to_binary(integer): # in reverse order

    assert integer >= 0

    binary = []
    index = 0
    total = integer

    if total == 0:
        binary.append(0)
        return binary

    while total > 0:
        remainder = int(total % 2)
        binary.append(remainder)
        total //= 2

    return binary


def get_remainder_list(b, len_binary_e, n):

    assert len_binary_e > 0

    remainders = []

    remainders.append(b % n)

    for i in range(1, len_binary_e):
        remainders.append((remainders[i-1] ** 2) % n)
    
    return remainders


def multiplicate_remainders(binary_e, remainder_list, n):

    len_binary_e = len(binary_e)

    assert len_binary_e > 0

    final_remainder = 1

    for i in range(len_binary_e):
        if binary_e[i] == 1:
            final_remainder = (final_remainder * remainder_list[i]) % n
    
    return final_remainder
    

def modular_exponentiation(b, e, n): # O(log_2(e))

    binary_e = to_binary(e)
    remainder_list = get_remainder_list(b, len(binary_e), n)

    return multiplicate_remainders(binary_e, remainder_list, n)


def main():

    b = int(input('b: '))
    e = int(input('e: '))
    n = int(input('n: '))

    print(f'{b}^{e} = {modular_exponentiation(b, e, n)} (mod {n})')


if __name__ == '__main__':
    main()
