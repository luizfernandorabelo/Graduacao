'''
Escreva um algoritmo que calcule P(T1 = 5)
com 1.000.000 de repetições dado p = 0.4
'''

import matplotlib.pyplot as plt
from random import random


TOTAL_REPETICOES = 1000000
P = 0.4


def main():
    total_sucessos = 0

    for _ in range(TOTAL_REPETICOES):
        for tentativa in range(5):
            if random() < P:
                if tentativa == 4:
                    total_sucessos += 1
                else:
                    break

    print('Probabilidade teórica: {:.5f}'.format((1-P) ** 4 * P))
    print('Percentual simulado:   {:.5f}'.format(total_sucessos / TOTAL_REPETICOES))


if __name__ == '__main__':
    main()
    