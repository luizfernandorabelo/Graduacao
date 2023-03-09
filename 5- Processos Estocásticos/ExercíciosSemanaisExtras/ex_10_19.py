'''
Problema de estoque: Considere um estoque com capacidade
para 10 itens. O estado Xk = n é o número de itens no
estoque às 6pm, quando fecha a loja. A demanda diária é D,
com distribuição p = [.1, .1, .2, .3, .3] para os valores
d = [0, 1, 2, 3, 4]. 
Quando a loja abre às 8h, compramos 3 itens se o estoque
tiver 4 itens ou menos; ou compramos 2 itens, caso contrário.
Se comprarmos mais itens do que caiba no estoque, os itens em
excesso são devolvidos sem custo. 
Se compramos cada item por R$ 1,00 e vendemos por R$ 1,50,
qual o lucro diário esperado após 10 anos?
'''

import numpy as np


LIMITE = 1000
LUCRO_POR_ITEM = 0.5


def main():
    P = [[.6, .2, .1, .1, .0, .0, .0, .0, .0, .0, .0],
         [.3, .3, .2, .1, .1, .0, .0, .0, .0, .0, .0],
         [.0, .3, .3, .2, .1, .1, .0, .0, .0, .0, .0],
         [.0, .0, .3, .3, .2, .1, .1, .0, .0, .0, .0],
         [.0, .0, .0, .3, .3, .2, .1, .1, .0, .0, .0],
         [.0, .0, .0, .3, .3, .2, .1, .1, .0, .0, .0],
         [.0, .0, .0, .0, .3, .3, .2, .1, .1, .0, .0],
         [.0, .0, .0, .0, .0, .3, .3, .2, .1, .1, .0],
         [.0, .0, .0, .0, .0, .0, .3, .3, .2, .1, .1],
         [.0, .0, .0, .0, .0, .0, .3, .3, .2, .1, .1],
         [.0, .0, .0, .0, .0, .0, .3, .3, .2, .1, .1]]

    Pi_inf = np.linalg.matrix_power(P, LIMITE)[0]

    indicadores_3 = sum([i for i in Pi_inf[:5]])
    indicadores_2 = sum([i for i in Pi_inf[5:9]])
    indicadores_1 = Pi_inf[9]
    
    lucro_esperado = (3 * indicadores_3 + 2 * indicadores_2 + indicadores_1) * LUCRO_POR_ITEM
    
    print('Lucro Diário Esperado =', lucro_esperado)


if __name__ == '__main__':
    main()

