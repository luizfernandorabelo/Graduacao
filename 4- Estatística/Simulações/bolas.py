'''
Suponha uma urna com 6 bolas brancas e 4 pretas.
Faça uma simulação que verifique quantas vezes
uma bola branca é retirada.
'''


import numpy as np
import matplotlib.pyplot as plt


def main():
    urna = ['B', 'B', 'B', 'B', 'B', 'B', 'P', 'P', 'P', 'P']

    percentuais_branca = []
    retiradas_executadas = []

    maximo_experimentos = 1000

    for total_retiradas in np.arange(1, maximo_experimentos, len(urna)):
        qtd_brancas_retiradas = 0
        for _ in range(total_retiradas):
            if urna[np.random.randint(len(urna))] == 'B':
                qtd_brancas_retiradas += 1
        percentuais_branca.append(qtd_brancas_retiradas / total_retiradas)
        retiradas_executadas.append(total_retiradas)
        
    qtd_brancas_existentes = urna.count('B')
    percentual_teorico = qtd_brancas_existentes / len(urna)
    
    plt.plot(retiradas_executadas, percentuais_branca, linestyle='-', color='b', label = 'Percentual Simulado')
    plt.axhline(y=percentual_teorico, color='r', linestyle='--', label = 'Probabilidade Teórica')
    plt.ylabel('Fração de bolas brancas retiradas')
    plt.xlabel('Numero de tentativas executadas')
    plt.xlim([0.0, maximo_experimentos])
    plt.ylim([0.0, 1.0])
    plt.legend()
    plt.show() 


if __name__ == '__main__':
    main()
    