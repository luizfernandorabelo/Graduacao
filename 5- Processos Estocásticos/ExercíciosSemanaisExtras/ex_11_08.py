'''
Considere a cadeia de Markov com a  matriz de taxa
Lambda = [ -3 1 2 ; 10 -20 10 ; 1 7 -8 ] e distribuição
inicial pi0 = [ 1 0 0 ].
Simule 3 saltos e registre os valores randômicos utilizados
'''

import numpy as np
from math import log
import matplotlib.pyplot as plt


TOTAL_SALTOS = 3

M = [[-3,  +1,  +2],
     [+10, -20, +10],
     [+1,  +7,  -8]]


def obter_tempo_estado_atual(estado_atual):
    aleatorio = round(np.random.rand(), 5)
    tempo = round(log(1 - aleatorio) / M[estado_atual][estado_atual], 5)
    print('Aleatório = ' + str(aleatorio) + ' | Tempo no estado = ' + str(tempo))
    return tempo
    

def obter_proximo_estado(estado_atual):
    parametro = abs(M[estado_atual][estado_atual])
    aleatorio = round(np.random.rand(), 5)
    proximo = -1
    for i in range(len(M)):
        if i != estado_atual:
            proximo = i
            if M[estado_atual][i] / parametro >= aleatorio:
                break
    print('Aleatório = ' + str(aleatorio) + ' | Próximo estado = ' + str(proximo))
    return proximo


def main():
    tempos = [0]
    estado_atual = 0

    for _ in range(TOTAL_SALTOS + 1):
        print('\n-> Estado Atual = ' + str(estado_atual))
        tempo_atual = obter_tempo_estado_atual(estado_atual)
        tempo_acumulado = tempos[-1] + tempo_atual
        plt.hlines(estado_atual, tempos[-1], tempo_acumulado)
        tempos.append(tempo_acumulado)
        estado_atual = obter_proximo_estado(estado_atual)

    plt.xlabel('Tempo decorrido')
    plt.ylabel('Estado')
    plt.yticks([0, 1, 2])
    plt.show()


if __name__ == '__main__':
    main()
