'''
Método de geração de números pseudo-aleatórios: X_{n+1} = (aX_n + c) mod m,
onde X_0 é a semente, m, a e c são inteiros maiores que 0.

'''

import matplotlib.pyplot as plt


def get_random(x_i, a, c, m):
    return (a * x_i + c) % m


def main():
    a, c, m = 7**5, 0, 2**31-1
    x_0 = 1

    n = 500
    x_i = x_0

    aleatorios = [x_0]
    for _ in range(n):
        x_i = get_random(x_i, a, c, m)
        aleatorios.append(x_i)
    
    print(aleatorios)

    plt.hist(aleatorios, rwidth=0.95)
    plt.title('Números Aleatórios Gerados')
    plt.show()


if __name__ == '__main__':
    main()
