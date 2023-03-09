'''
Área do círculo: πr² 
Área do quadrado com círculo inscrito: (2r)²

Probabilidade(ponto aleatório dentro do círculo) = área círculo / área quadrado = π / 4

Gerando pontos aleatórios, é possível estimar o valor de π.
'''


import numpy as np
import matplotlib.pyplot as plt


def main():
    maximo_pontos = 1000
    repeticoes_por_esperimento = 100

    pis_finais = []
    desvios_padrao = []
    totais_iteracoes = []

    for total_iteracoes in range(1, maximo_pontos, 10):
        pis_parciais = []
        for repeticao in range(repeticoes_por_esperimento):
            qtd_pontos_internos = 0
            for _ in range(total_iteracoes):
                x = np.random.uniform()
                y = np.random.uniform()
                if x**2 + y**2 < 1:
                    qtd_pontos_internos += 1
            pi_estimado = qtd_pontos_internos / total_iteracoes * 4
            pis_parciais.append(pi_estimado)
        pis_finais.append(np.mean(pis_parciais))
        desvios_padrao.append(np.std(pis_parciais))
        totais_iteracoes.append(total_iteracoes)
    
    plt.figure()
    plt.errorbar(totais_iteracoes, pis_finais, yerr=desvios_padrao, fmt='.-b')
    plt.axhline(y=np.pi, color='red')
    plt.xlabel('Número de Simulações')
    plt.ylabel('π Estimado')
    plt.show()
    

if __name__ == '__main__':
    main()
    