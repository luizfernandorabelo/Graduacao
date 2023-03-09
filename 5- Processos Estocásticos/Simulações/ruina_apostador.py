import numpy as np
import matplotlib.pyplot as plt


def main():
    maximo_fichas = 100
    qtd_fichas_inicio = 95

    total_simulacoes = 100
    percentuais_derrota_simulados = []
    probabilidades_vitoria = np.arange(0.02, 1, 0.02)

    for p in probabilidades_vitoria:
        qtd_vitorias = 0
        for _ in range(total_simulacoes):
            qtd_fichas_atuais = qtd_fichas_inicio
            while 0 < qtd_fichas_atuais < maximo_fichas:
                if np.random.uniform() < p:
                    qtd_fichas_atuais += 1
                else:
                    qtd_fichas_atuais -= 1
            if qtd_fichas_atuais == maximo_fichas:
                qtd_vitorias += 1
        percentuais_derrota_simulados.append(1 - qtd_vitorias / total_simulacoes)

    percentuais_derrota_teoricos = []

    for p in probabilidades_vitoria:
        if p != 1/2:
            prob_vitoria_teorica = (1 - ((1 - p) / p) ** qtd_fichas_inicio) / (1 - ((1 - p) / p) ** maximo_fichas)
        else:
            prob_vitoria_teorica = qtd_fichas_inicio / maximo_fichas
        percentuais_derrota_teoricos.append(1 - prob_vitoria_teorica)


    plt.figure()
    plt.plot(probabilidades_vitoria, percentuais_derrota_simulados, '-o', color='b', markersize=5, label='Simulação')
    plt.plot(probabilidades_vitoria, percentuais_derrota_teoricos, '-o', color='r', markersize=5, label='Teórico')
    plt.xlabel("p (Probabilidade de Vitória por Aposta)")
    plt.ylabel(r'$P(X_T = 0 | X_0 = i)$ (Probabilidade de Ruína)')
    plt.legend()
    plt.grid(True)
    plt.show() 
    

if __name__ == '__main__':
    main()
    